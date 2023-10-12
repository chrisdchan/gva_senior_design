function extract_pipet_function_parallel_with_manual_for_errors_fast(activeDir,nImgsPerFOV,wellsPerRow,channelL,assayVol,pathDir,toRotate,colorIm,pixSz,wellsPerFOV)
% Code for extracting pipette "wells" from images.

% Move to active directory where the original jpegs are located
cd(activeDir)
addpath(pathDir);

% Setup the locations where everything will e saved
matDir     = [activeDir filesep 'SavedMat_' datestr(now,29)];
if exist(matDir,'dir')~=7
    mkdir(matDir)
end

%% Load in all the files and combine to single images
% Find all of the .jpeg images
fList = dir('*.jpg');
nFiles = length(fList);

% Find the total number of FOVs in the directory
nFOV = nFiles/nImgsPerFOV;

%Set up matrices to hold images
tmpImg = imread(fList(1).name);
[ysize,xsize,~] = size(tmpImg);
if colorIm 
    nColors = 3;
else
    nColors = 1;
end
dat = zeros(ysize,xsize,nColors,nFOV,'uint8');
tmpDat = zeros(ysize,xsize,nColors,nImgsPerFOV,'uint8');

%Loop through and read in all the images
iIndx = 0;
for nn = 1:nFOV
    for ff = 1:nImgsPerFOV
        iIndx = iIndx + 1;
        tmpImg = imread(fList(iIndx).name);
        if colorIm
            tmpDat(:,:,:,ff) = tmpImg;
        elseif size(tmpImg,3)>1
            tmpDat(:,:,:,ff) = rgb2gray(tmpImg);
        else
            tmpDat(:,:,:,ff) = tmpImg;
        end
    end
    % This is the variable that will hold all the combined images
    dat(:,:,:,nn) = uint8(mean(tmpDat,4));
end

%Arrange so that the tips are pointing up!
if toRotate
    if xsize>ysize
        dat = permute(dat,[2,1,3,4]);
        [xsize,ysize] = deal(ysize,xsize);
    end
    dat = flip(dat,1);
    dat = flip(dat,2);
end

%% Now segment the tips. To segment in parallel must preallocate matrices
wIndx = 0;          % This is a running index for the columns
currRowChar = 'A';  % Running index of the rows
currRow = currRowChar - 64;
fovIndx = cell(nFOV,1);
%Find the number of wells
imgResize = 0.1;
crossOver = cell(nFOV,1);
yresize = ceil(ysize*imgResize); xresize = ceil(xsize*imgResize);
imgFB = zeros(yresize,xresize,nFOV);
for nn = 1:nFOV
    % Call out the current FOV
    if colorIm
        imgR = imresize(squeeze(rgb2gray(dat(:,:,:,nn))),imgResize);
    else
        imgR = imresize(squeeze(dat(:,:,1,nn)),imgResize);
    end
    % Median filter and fiber the image
    imgR = double(fibermetric(imgR,30*imgResize,...
                                'ObjectPolarity','dark',...
                                'StructureSensitivity',0.06*maxhessiannorm(imgR)));
    imgR = imadjust(imgR);
    imgFB(:,:,nn) = imgR;
    %remove the bottom 5% of image
    imgR(round(yresize*.95):end,:)=0;
    
    % Take the max of the image to smooth out the well outlines
    %l1 = smooth(max(imgR,[],1),35);
    l1 = smooth(quantile(imgR,.99,1),35);
    l1(1:40) = 0;
    l1(end-40:end) = 0;
    l1 = diff([0; round(smooth(l1>0.25,10)); 0]);
    upBnd = find(l1==1);
    dnBnd = find(l1==-1);
    
    if length(upBnd)~=length(dnBnd)
        disp('Initial preallocation failed')
        error('BREAK')
    end
    if length(upBnd)>wellsPerFOV        
        disp('Initial preallocation failed')
        error('BREAK')
    end
        
    nWells = length(upBnd);
    crossOver{nn} = zeros(nWells+1,1);
    crossOver{nn}(1) = 1;
    crossOver{nn}(end) = size(imgR,2);
    if nWells == 1
        crossOver{nn}(1) = max([1,round(upBnd*.75)]);
        crossOver{nn}(2) = min([xresize,round(dnBnd+(xresize-dnBnd)*.25)]);
    else
        for ww = 1:nWells-1
            crossOver{nn}(ww+1) = dnBnd(ww) + abs(dnBnd(ww)-upBnd(ww+1))/2;
        end
    end

    
    for ww = 1:nWells
        wIndx = wIndx+1;
        if wIndx > wellsPerRow
            wIndx = 1;
            currRowChar = char(double(currRowChar) + 1);
            currRow = currRowChar - 64;
        end
        collList{currRow,wIndx} = [currRowChar num2str(wIndx)];
        fovIndx{nn} = [fovIndx{nn};[currRow,wIndx]];
    end
end
%Preallocate cell arrays for holding the images
nWell = max(cellfun(@(x) size(x,1),fovIndx));
tmp_collImgs = cell(nFOV,nWell);
tmp_collStart = cell(nFOV,nWell);
tmp_tipAngle = cell(nFOV,nWell);
tmp_tipBtm = cell(nFOV,nWell);

segFail = ones(nFOV,1);
%% Identify angle to square images
parfor nn = 1:nFOV
    disp(['FOV: ' num2str(nn)])
    % Call out the current FOV
    try
        % Use the pipet tip angles to define the global rotation angle
        [wellImgs, startPixEst, tipAngle,tipBtm] = pipette_tip_rotation_segmentation_fast(nn,imgFB,dat,fovIndx,crossOver,ysize,imgResize,pixSz,colorIm);
    catch
        disp(['Did not find the correct number of wells in FOV ' num2str(nn) ' will revert to manual segmentation']);
        wellImgs = 0;
        segFail(nn) = 1;
    end
    % Find them manually if something didn't work
    if length(wellImgs)~=size(fovIndx{nn},1)
        disp(['Did not find the correct number of wells in FOV ' num2str(nn) ' will revert to manual segmentation']);
        segFail(nn) = 1;  %Will use manual segmentation for this one
    else
        segFail(nn) = 0;
        % Save the results in the cell arrays within the parfor loop
        for ww = 1:nWell
            if ww>length(wellImgs)
                continue
            end
            tmp_collImgs{nn,ww} = wellImgs{ww};
            tmp_collStart{nn,ww} = startPixEst(ww);
            tmp_tipAngle{nn,ww} = tipAngle(ww);
            tmp_tipBtm{nn,ww} = tipBtm{ww};
        end
    end
end

fail_indx = find(segFail==1);
for vv = 1:length(fail_indx)
    disp(['Redoing FOV: ' num2str(fail_indx(vv))])
    % Call out the current FOV
    nn = fail_indx(vv);
    currImg = dat(:,:,:,nn);
    % Allow the user to define the crossOver before trying to segment again
    fig = figure();
    imshow(currImg,[])
    title('From left to right, left click the edges of the pipette at the bottom.  Press enter to finish')
    succeed = 1;
    while succeed==1
        x = [];button = 1;cnt = 1; 
        while ~isempty(button)
            try
                [x(cnt),~,button] = ginput(1);
                xline(x(cnt),'r')
                cnt = cnt  +1 ;
            catch
                button = [];
            end
        end
        succeed = rem(length(x),2);
        if succeed==1
            title('Number of selections must be even!')
        end
    end
    crossOver{nn} = floor(x'*imgResize);
    try
        % Use the pipet tip angles to define the global rotation angle
        [wellImgs, startPixEst, tipAngle,tipBtm] = pipette_tip_rotation_segmentation_fast(nn,imgFB,dat,fovIndx,crossOver,ysize,imgResize,pixSz,colorIm);
    catch
        disp(['Manual segmentation failed for FOV ' num2str(nn)]);
        error('BREAK')
    end
    segFail(nn) = 0;
    % Save the results in the cell arrays
    for ww = 1:nWell
        if ww>length(wellImgs)
            continue
        end
        tmp_collImgs{nn,ww} = wellImgs{ww};
        tmp_collStart{nn,ww} = startPixEst(ww);
        tmp_tipAngle{nn,ww} = tipAngle(ww);
        tmp_tipBtm{nn,ww} = tipBtm{ww};
    end
    close(fig)
end

%Reorganize the variables
for nn=1:nFOV
    for ww = 1:size(fovIndx{nn},1)
        currRow = fovIndx{nn}(ww,1);
        wIndx = fovIndx{nn}(ww,2);
        collImgs{currRow,wIndx} = tmp_collImgs{nn,ww};
        collStart{currRow,wIndx} = tmp_collStart{nn,ww};
        collAngle{currRow,wIndx} = tmp_tipAngle{nn,ww};
        collBtm{currRow,wIndx} = tmp_tipBtm{nn,ww};
    end
end 

% Save the combined well images and identities
save([matDir filesep 'Combined_extracted_wells.mat'],...
    'collImgs','collList','collBtm','collAngle','collStart','activeDir','channelL','assayVol','collStart','fovIndx','-v7.3','-nocompression');
end
