function  [collImgs,collAngle,collBtm,collStart] = extract_pipet_function_while_aquiring(fList,nImgsPerFOV,wellsPerRow,toRotate,colorIm,pixSz)
% Code for extracting pipette "wells" from images.

%% Load in all the files and combine to single images
% Find all of the .jpeg images
nFiles = length(fList);

%Set up matrices to hold images
try
    tmpImg = imread(fList{1});
catch
    tmpImg = [];
    while isempty(tmpImg)
        try
            tmpImg = imread(fList{1});
        end
    end
end

[ysize,xsize,~] = size(tmpImg);
if colorIm 
    nColors = 3;
else
    nColors = 1;
end
dat = zeros(ysize,xsize,nColors,nImgsPerFOV,'uint8');
%Loop through and read in all the images
for ff = 1:nImgsPerFOV
    tmpImg = imread(fList{ff});
    if colorIm
        dat(:,:,:,ff) = tmpImg;
    else
        dat(:,:,:,ff) = rgb2gray(tmpImg);
    end
end
dat = uint8(mean(dat,4));

%Arrange so that the tips are pointing up!
if xsize>ysize
    dat = permute(dat,[2,1,3,4]);
    [xsize,ysize] = deal(ysize,xsize);
end
if toRotate
    dat = flip(dat,1);
    dat = flip(dat,2);
end

%% Now segment the tips. 
%Find the number of wells
imgResize = 0.1;
crossOver = cell(1,1);
% Call out the current FOV
if colorIm
    imgR = imresize(squeeze(rgb2gray(dat)),imgResize);
else
    imgR = imresize(squeeze(dat(:,:,1)),imgResize);
end
% Median filter and fiber the image
imgR = double(fibermetric(imgR,30*imgResize,...
                            'ObjectPolarity','dark',...
                            'StructureSensitivity',0.06*maxhessiannorm(imgR)));
imgR = imadjust(imgR);
imgFB = imgR;

% Take the max of the image to smooth out the well outlines
l1 = smooth(max(imgR,[],1),30);
l1(1:40) = 0;
l1(end-40:end) = 0;
l1 = diff([0; l1 > 0.5; 0]);
upBnd = find(l1==1);
dnBnd = find(l1==-1);

if length(upBnd)~=length(dnBnd)
    disp('Initial preallocation failed')
    error('BREAK')
end
nWells = length(upBnd);
crossOver{1} = zeros(nWells+1,1);
crossOver{1}(1) = 1;
crossOver{1}(end) = size(imgR,2);
for ww = 1:nWells-1
    crossOver{1}(ww+1) = dnBnd(ww) + abs(dnBnd(ww)-upBnd(ww+1))/2;
end
    
fovIndx = cell(1,1);
fovIndx{1} = zeros(3,1);
%Preallocate cell arrays for holding the images
collImgs = cell(1,nWells);
collStart = cell(1,nWells);
collAngle = cell(1,nWells);
collBtm = cell(1,nWells);

%% Identify angle to square images
try
    % Use the pipet tip angles to define the global rotation angle
    [wellImgs, startPixEst, tipAngle,tipBtm] = pipette_tip_rotation_segmentation_fast(1,imgFB,dat,fovIndx,crossOver,ysize,imgResize,pixSz,colorIm);
catch
    disp(['Did not find the correct number of wells.  Reverting to manual segmentation']);
    wellImgs = 0;
    segFail = 1;
end
% Find them manually if something didn't work
if length(wellImgs)~=size(fovIndx{1},1)
    disp(['Did not find the correct number of wells.  Reverting to manual segmentation']);
    segFail = 1;  %Will use manual segmentation for this one
else
    segFail = 0;
    % Save the results in the cell arrays within the parfor loop
    for ww = 1:nWells
        if ww>length(wellImgs)
            continue
        end
        collImgs{1,ww} = wellImgs{ww};
        collStart{1,ww} = startPixEst(ww);
        collAngle{1,ww} = tipAngle(ww);
        collBtm{1,ww} = tipBtm{ww};
    end
end


if segFail
    % Call out the current FOV
    currImg = dat;
    % Allow the user to define the crossOver before trying to segment again
    fig = figure();
    imshow(currImg,[])
    title('From left to right, left click the edges of the pipette at the bottom.  Press enter to finish')
    succeed = 0;
    while succeed==0
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
        if succeed==0
            title('Number of selections must be odd!')
        end
    end
    crossOver{nn} = floor(x'*imgResize);
    try
        % Use the pipet tip angles to define the global rotation angle
        [wellImgs, startPixEst, tipAngle,tipBtm] = pipette_tip_rotation_segmentation_fast(1,imgFB,dat,fovIndx,crossOver,ysize,imgResize,pixSz,colorIm);
    catch
        disp(['Manual segmentation failed for FOV']);
        error('BREAK')
    end
    segFail = 0;
    % Save the results in the cell arrays
    for ww = 1:nWells
        if ww>length(wellImgs)
            continue
        end
        collImgs{1,ww} = wellImgs{ww};
        collStart{1,ww} = startPixEst(ww);
        collAngle{1,ww} = tipAngle(ww);
        collBtm{1,ww} = tipBtm{ww};
    end
    close(fig)
end

end
