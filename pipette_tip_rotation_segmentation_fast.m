function [wellImgs, startPixEst, tipAngle,tipBtm] = pipette_tip_rotation_segmentation_fast(nn,imgFB,dat,fovIndx,crossOver,ysize,imgResize,pixSz,colorIm)
%Code to find the pipette tip rotation and segmentation

%Current fibermetric image and current full image
currFB = imgFB(:,:,nn);
currImg = dat(:,:,:,nn);

% Define the potential angles to scan for the pipet edges
nAngleT = 100;
tAngle = linspace(-10,10,nAngleT);

%Arrays to hold variables of importance
wellImgs = cell(size(fovIndx{nn},1),1);
startPixEst = zeros(size(fovIndx{nn},1),1);
tipAngle = zeros(size(fovIndx{nn},1),1);
tipBtm = cell(size(fovIndx{nn},1),1);

%Loop through the number of wells found
for kk = 1:size(fovIndx{nn},1)
    %Re-use the Fiber segmented pipette tips to find the angle for
    %rotating each pipette tip individually.
    %Cut the image based on the crossOver variable.  Should contain a
    %single pipette tip!
    subFB = currFB(:,round(crossOver{nn}(kk)):round(crossOver{nn}(kk)+floor(diff(crossOver{nn}(kk:kk+1))*imgResize)/imgResize));
    [tmp_height,~] = size(subFB);
    subFB(round(tmp_height*.9):end,:) = 0; %Get rid of the bottom of the pipette which can throw off the alignment
    %% Use convolution filters to find the angles of rotation resulting in vertical alignment
    nCol = 3;  %Number of columns for the convolution
    %Create matrices for convolution results
    pixMax = size(subFB,2)-nCol*3;
    conv_subIm = zeros(nAngleT,pixMax);
    smth_conv_subIm = zeros(size(conv_subIm));
    % Create the straight line for convolution filter
    C = zeros(size(subFB,1),nCol*3,'single');
    C(:,nCol+1:2*nCol,:) = 1;
    C2 = C - mean(C(:));
    %For each angle rotate the image and convolve.
    for dd = 1:nAngleT
        % Rotate the fibermetric image
        Btest = imrotate(subFB,tAngle(dd),'crop');
        for rr = nCol*3:pixMax
            % Cut out just the same size image and convolve
            Btmp = Btest(:,rr + (1:nCol*3));
            conv_subIm(dd,rr) = sum(Btmp(:).*C2(:));
        end
        % Smooth the convolution
        smth_conv_subIm(dd,:) = abs(smooth(conv_subIm(dd,:)));
    end
    fnd_angle = mat2gray(sum(smth_conv_subIm'));
    %Find the angles that maximized the convolution
    [~,angleFit] = findpeaks(fnd_angle,tAngle,'NPeaks',2,'SortStr','descend','MinPeakDistance',5);
%     %Alternatively use a gaussian fit
%     gFit = fit(tAngle',fnd_angle','gauss2');
%     angleFit(1) = gFit.b1;
%     angleFit(2) = gFit.b2;
    angleFit = sort(angleFit,'descend');
    %This is the angle to rotate the image by
    imgAngle = mean(angleFit);
    %This is the angle of the pipette tip walls
    tipAngle(kk) = mean(abs(angleFit-imgAngle));

    %% Apply rotation to the current image
    subIm = currImg;
    subIm = subIm(:,crossOver{nn}(kk)/imgResize:(crossOver{nn}(kk)+floor(diff(crossOver{nn}(kk:kk+1))*imgResize)/imgResize)/imgResize,:);
    subIm = imrotate(subIm,imgAngle);
    %Trim based on rotation
    c1 = sin(deg2rad(imgAngle));
    c2 = sin(deg2rad(90-imgAngle));   
    toTrim = 1+ceil(abs(ceil(ysize*(c1/c2))));
    subIm = subIm(1+toTrim:end-toTrim,1+toTrim:end-toTrim,:);
    
    %% Now find the x position by recomputing the Fibermetric image
    if colorIm
        imgR = imresize(squeeze(rgb2gray(subIm)),imgResize);
    else
        imgR = imresize(squeeze(subIm),imgResize);
    end
    % Median filter and fiber the image
    imgR = double(fibermetric(imgR,30*imgResize,...
                                'ObjectPolarity','dark',...
                                'StructureSensitivity',0.06*maxhessiannorm(imgR)));
    imgR = imadjust(imgR);
    
    % Variables to hold the x position
    xPosFit = zeros(2,1);xPosFitFull=zeros(2,1);
    %Rotate the image by the tip angle
    Btest = imrotate(imgR,tipAngle(kk),'crop');
    pixMax = size(imgR,2)-nCol*3;
    % Create the straight line for convolution filter
    C = zeros(size(imgR,1),nCol*3,'single');
    C(:,nCol+1:2*nCol,:) = 1;
    C2 = C - mean(C(:));
    %Run the convolution using the conv2 function
    CC = conv2(Btest,C,'same');
    conv_subIm = abs(smooth(mean(CC,1)));
    %Find position of convolution filter which maximized the convolution
    [~,xPosFit(1)] = findpeaks(conv_subIm,'NPeaks',1,'SortStr','descend');
    %Inorder to account for the tip wall base position in the unrotated
    %image must subtract tan(A)*(img size/2)*cos(A) according to trig rules
    xPosFit(1) = xPosFit(1)-tand(tipAngle(kk))*size(imgR,1)/2*cosd(tipAngle(kk));
    %X position of the full image
    xPosFitFull(1) = xPosFit(1)/imgResize;
    %Repeat for other pipette wall
    Btest = imrotate(imgR,-tipAngle(kk),'crop');
    CC = conv2(Btest,C,'same');
    conv_subIm = abs(smooth(mean(CC,1)));
    [~,xPosFit(2)] = findpeaks(conv_subIm,'NPeaks',1,'SortStr','descend');
    %Again correct the position based on trig
    xPosFit(2) = xPosFit(2) + tand(tipAngle(kk))*size(imgR,1)/2*cosd(tipAngle(kk));
    %X position in the full image
    xPosFitFull(2) = xPosFit(2)/imgResize;
    
    %% Find the tip end using a convolution filter
    %Define the convolution filter to look for the tip.
    C = zeros(12,14);
    C(3:9,3:12) = 1;
    C(6:end,6:9) = 0;
    % Estimate where to look based on the fiber metric segmentation
    [ysize_sub,xsize_sub] = size(imgR);
    %tmp = smooth(max(imgR,[],2));
    tmp = smooth(quantile(imgR,.99,2));
    tmp(1:ysize_sub-diff(xPosFit)/2*tand(90-tipAngle(kk))) = 0;
    %tmp(1:50) = 0;
    tmp(400:end) = 1;
    estStrt = length(tmp)-find(flip(tmp)<.2,1,'first');
    imgR_sub = imgR(round(max([1,estStrt-100])):round(min([ysize_sub,estStrt+100])),round(max(1,xsize_sub/2-.5/pixSz)):round(min(xsize_sub,xsize_sub/2+.5/pixSz)));
    %Run convolution and find y location of tip 
    Csame = conv2(imgR_sub,C,'same');
    %figure; imshow(Csame,[]);
    %figure;plot(max(Csame,[],2))
    %[~,loc]=findpeaks(smooth(max(Csame,[],2)),'NPeaks',1,'SortStr','none','MinPeakHeight',10);
    [~,loc]=findpeaks(smooth(quantile(Csame,.98,2)),'NPeaks',1,'SortStr','none','MinPeakHeight',10);
    if isempty(loc)
        [~,loc]=findpeaks(smooth(max(Csame,[],2)),'NPeaks',1,'SortStr','none','MinPeakHeight',5);
    end    
    startPixEst(kk) = (loc+max([1,estStrt-100]))/imgResize;  %Tip end
    
    %% Center the pipette tip in the image
    [ysize,xsize,~] = size(subIm);
    if xPosFitFull(1) > xsize-xPosFitFull(2)
        subIm = imcrop(subIm,[round(xPosFitFull(1)-(xsize-xPosFitFull(2))) 1 xsize-round(xPosFitFull(1)-(xsize-xPosFitFull(2))) ysize]);
        xPosFitFull = xPosFitFull - round(xPosFitFull(1)-(xsize-xPosFitFull(2)));
    else
        subIm = imcrop(subIm,[1 1 sum(xPosFitFull) ysize]);
    end
    tipBtm{kk} = xPosFitFull;
    
    wellImgs{kk} = subIm;
    
%     %Show segmentation results
%     figure;
%     imshow(subIm,[])
%     hold on
%     angleTmp = [tipAngle(kk),-tipAngle(kk)];
%     for vv = 1:2
%         L = cosd(angleTmp(vv))*size(subIm,1);
%         if angleTmp(vv) > 0
%             x2=xPosFitFull(vv)+(L*sind(angleTmp(vv)));
%             plot([xPosFitFull(vv) x2],[size(subIm,1) 1],'r')
%         else
%             x2=xPosFitFull(vv)+(L*sind(angleTmp(vv)));
%             plot([x2 xPosFitFull(vv)],[1, size(subIm,1)],'r')
%         end
%     end
%     yline(startPixEst(kk),'r')
%     scatter(mean(xPosFitFull),L-diff(xPosFitFull)/2*tand(90-tipAngle(kk)))
%     drawnow
%     pause(1);
end

    