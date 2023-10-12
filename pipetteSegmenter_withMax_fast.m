function [apY,apX,CFUs,clicked_points,app,radiiOut,bound_mask] = pipetteSegmenter_withMax_fast(im,activeDir,CFUs,clicked_points,...
                                                                                                currZoom,modelNum,ax,fig,channelL,assayVol,...
                                                                                                dilutionFactor,collList,rr,nn,wll,nWells,nRows,...
                                                                                                collStart,collBtm,collAngle,app,pixSz,bound_mask,maxCol,fudgeFactor)

%save('tmp_seg.mat','im','activeDir','CFUs','clicked_points','currZoom','modelNum','ax','channelL','assayVol','dilutionFactor','collList','rr','nn','wll','nWells','nRows','collStart','collBtm','collAngle','app','pixSz','bound_mask','maxCol','fudgeFactor');
%error('BREAK')
%% Zoom in on the image according to the segementation model
startPix = collStart{rr,nn};
tipAngle = collAngle{rr,nn};
tipLen = size(im,2) - startPix;
[x1, x2, y1, y2] = zoomPipetteTip(im,tipAngle,startPix,currZoom,ax,fig);

%Crop the image based on the zoom
subIm = imcrop(im,[x1 y1 x2-x1 y2-y1]);

%Delete the previous plot overlays if showing images
if ~isempty(ax) 
    if exist('clicked_points','var'); delete(clicked_points); end
    if exist('bound_mask','var'); delete(bound_mask); end
end

%% Load segmentation model parameters
load([activeDir filesep 'segmentation_parameters.mat'])
%Segmentation parameters
tipEdge = table2array(segT(segT.model==modelNum,'tipMask'));
maxRadii = table2array(segT(segT.model==modelNum,'maxRadii'));
minRadii = table2array(segT(segT.model==modelNum,'minRadii'));
colonyEdge = table2array(segT(segT.model==modelNum,'colonyEdge'));
colonySensitivity = table2array(segT(segT.model==modelNum,'colonySensitivity'));

%Optionally update app values.  When the values are changed in the app, it saves it to
%the segmentation_parameters.mat file which is reloaded before rerunning
%segmentation
if ~isempty(ax)
    app.SegmenterModelSpinner.Value = modelNum;
    app.MaxColonyRadiuspixelsSpinner.Value = maxRadii;
    app.EstimatedColonyDiameterpixelsSpinner.Value = minRadii;
    app.TipMaskSpinner.Value = tipEdge;
    app.ColonyEdgeThresholdSlider.Value = colonyEdge;
    app.SensitivitySlider.Value = colonySensitivity;
end

%% Define the segmentation based on the location of the pipette tip walls.
%Should be 4 corners.
[~,xsize] = size(im);
bwx1 = xsize;             bwy1 = collBtm{rr,nn}(1);
bwx2 = xsize;             bwy2 = collBtm{rr,nn}(2);
bwx3 = collStart{rr,nn};  bwy3 = collBtm{rr,nn}(2)-tand(collAngle{rr,nn})*(xsize-collStart{rr,nn});
bwx4 = collStart{rr,nn};  bwy4 = collBtm{rr,nn}(1)+tand(collAngle{rr,nn})*(xsize-collStart{rr,nn});
bw = roipoly(im,[bwx1 bwx2 bwx3 bwx4],[bwy1 bwy2 bwy3 bwy4]);
bw = imdilate(bw,strel('disk',tipEdge));
%figure;imshow(imfuse(im,bw,'blend'))
bw_sub = imcrop(bw,[x1 y1 x2-x1 y2-y1]);
%If displaying plot boundary mask
if ~isempty(ax)
    [B,~] = bwboundaries(bw_sub);
    hold on
    bound_mask = [];
    for k = 1:length(B)
       boundary = B{k};
       bound_mask(k) = plot(boundary(:,2)+x1, boundary(:,1)+y1, 'b', 'LineWidth', 2);
    end
else
    bound_mask = [];
end
    
% %If you want to speed up segmentation for 5, resize image.  Reduces accuracy slightly.
% if modelNum == 5
%     bw_sub = imresize(bw_sub,.25);
%     subIm = imresize(subIm,.25);
%     tipLen = tipLen/4;
%     minRadii = minRadii/4;
% end

%% Set which how much from the end to exclude for the different model levels
switch modelNum
    case 5
        tipExclude = round(1/5*tipLen);
    case 6
        tipExclude = round(1/6*tipLen);
    case 7
        tipExclude = round(1/20*tipLen);
    case 8
        tipExclude = round(1/50*tipLen);
    case 9
        tipExclude = 0;
end

%% Segmentation using multithresh of difference of gaussians
k = minRadii;
sigma1 = 1;
sigma2 = sigma1*k;
gauss1 = imgaussfilt(subIm,sigma1);
gauss2 = imgaussfilt(subIm,sigma2);
dogsubIm = gauss2 - gauss1;
dogsubIm(bw_sub==0) = 0;
%figure;imshow(dogsubIm,[])
%Remove the tip from calculation
dogsubIm(:,1:(collStart{rr,nn}-x1+tipExclude))=0;
segSensitivity =  floor((colonySensitivity-.8)*100);
if segSensitivity>20
    segSensitivity = 20;
elseif segSensitivity < 2
    segSensitivity =2;
end
thresh = multithresh(dogsubIm,segSensitivity);
bwseg = dogsubIm>thresh(2);

% %Then resize back!    
% if modelNum == 5
%     bw_sub = imresize(bw_sub,4);
%     subIm = imresize(subIm,4);
%     tipLen = tipLen*4;
%     minRadii = minRadii*4;
%     bwseg = imresize(bwseg,4);
% end

%% Calculate the region properties and select based on size and elongation
props = regionprops(bwseg,'Centroid','Area','MinorAxisLength','MajorAxisLength','EquivDiameter');%,'Circularity','Eccentricity','Image','Solidity','BoundingBox','EquivDiameter');
% Remove spurious results
props(([props(:).Area]< (minRadii/3)^2*3.14) | ([props(:).MajorAxisLength]./[props(:).MinorAxisLength]>5) | ([props(:).Area]> (minRadii*4)^2*3.14) ) = [];
centers =reshape([props(:).Centroid],[2,size(props)])';
radiiOut = [props(:).EquivDiameter]/2;
  
try
    apY_1 = []; apX_1 = [];  %Remove the previous clicked points. 
    rad_1 = [];
    [xx,yy] = meshgrid(1:size(bw_sub,2),1:size(bw_sub,1));
    for cc=1:length(centers)
        %if bw(round(centers(cc,2)),round(centers(cc,1))) 
        %If the whole segmented part is within the boundaries
        if all(bw_sub((xx-centers(cc,1)).^2 + (yy-centers(cc,2)).^2 <= radiiOut(cc).^2))
            apX_1 = [apX_1;centers(cc,2)+y1];
            apY_1 = [apY_1;centers(cc,1)+x1];
            rad_1 = [rad_1;radiiOut(cc)];
        end
    end

    %Keep a certain number of segmentation results
    if maxCol
        ccMax = min(length(apY_1),maxCol);
    else
        ccMax = length(apY_1);
    end

    [~,aIndx] = sort(apY_1);

    apY = apY_1(aIndx(1:ccMax));
    apX = apX_1(aIndx(1:ccMax));
    radiiOut = rad_1(aIndx(1:ccMax));

    oldCFU = CFUs(rr,nn);
    CFUs = CFUcalculator(CFUs,apX,apY,rr,nn,assayVol,dilutionFactor,fudgeFactor,pixSz,channelL,collStart);
    %clicked_points = scatter(ax,apY,apX,'r');
    if ~isempty(ax)
        clicked_points = viscircles([apY,apX],radiiOut,'Linewidth',0.8);
        fldChg = (CFUs(rr,nn)-oldCFU)/oldCFU*100;
        title(ax,[collList{rr,nn} ': ' num2str(wll) ' of ' num2str(nWells*nRows) ' wells.  Est. CFU=' num2str(CFUs(rr,nn),'%.2e'), '; Percent change from last point=' num2str(fldChg,'%.0f') '%']);
    end
catch ME
    if ~isempty(ax)
        title(ax,[collList{rr,nn} ': ' num2str(wll) ' of ' num2str(nWells*nRows) ' wells.  Segmenter Failed.']);
    end
end

