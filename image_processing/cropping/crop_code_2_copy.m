clear all; clc;
%% Script
% Load and display the original image
originalImage = imread('Testing_Image_14.jpg');
figure(1), imshow(originalImage), title('Original Image');
rect = [0, 2200, 2500, 1500];
originalImg = imcrop(originalImage, rect);
figure(2), imshow(originalImg), title('Cropped Image');
%%
% Process the image to obtain ROI cleaned binary image
roiCleaned = processImageToROI(originalImg);
figure(3), imshow(roiCleaned), title('Cleaned Image');
[croppedImgList, standardizedImgList] = segmentAndStandardizePipettes(roiCleaned, originalImg);

% Display or process standardized images as needed
for i = 1:length(standardizedImgList)
    figure(i+3), imshow(standardizedImgList{i}), title(sprintf('Pipette Tip %d', i));
    % Optionally, save the outputted image
    % imwrite(standardizedImgList{i}, sprintf('standardized_image_%d.jpg', i));
end
%% Functions
function roiCleanedBinary = processImageToROI(image)
    % Convert to grayscale if the image is in color
    if size(image, 3) == 3
        grayImage = rgb2gray(image);
    else
        grayImage = image;
    end

    % Apply a Gaussian blur to reduce noise
    smoothedImg = imgaussfilt(grayImage, 3);
    
    % Use edge detection or other gradient-based methods to highlight structures
    edgeImg = edge(smoothedImg, 'Canny');
  
    % Use morphological closing to connect components that are pipette-like
    seClose = strel('rectangle', [5, 100]); % This may need adjustment based on pipette dimensions
    closedImg = imclose(edgeImg, seClose);

    % Fill holes to solidify candidate pipette structures
    filledImg = imfill(closedImg, 'holes');

    % Filter based on properties to eliminate non-pipette shaped objects
    cc = bwconncomp(filledImg);
    stats = regionprops(cc, 'Area', 'MajorAxisLength', 'MinorAxisLength', 'Eccentricity');
    
    % Define criteria for pipette tips based on expected shape properties
    % Adjust these criteria based on your specific needs and pipette tip characteristics
    criteria = ([stats.Eccentricity] > 0.6) & ... % High eccentricity for elongated shapes
               ([stats.MajorAxisLength] ./ [stats.MinorAxisLength] > 1.5) & ... % High aspect ratio
               ([stats.Area] > 1000000); % Minimum size to exclude small artifacts

    % Create a new binary image based on the filtering criteria
    roiCleanedBinary = ismember(labelmatrix(cc), find(criteria));
    roiCleanedBinary = imfill(roiCleanedBinary, 'holes'); % Fill holes again if necessary
end

function [croppedImgList, standardizedImgList] = segmentAndStandardizePipettes(roiCleanedBinary, originalImg)
    cc = bwconncomp(roiCleanedBinary);
    stats = regionprops(cc, 'BoundingBox', 'MajorAxisLength', 'MinorAxisLength');

    croppedImgList = {};
    standardizedImgList = {};

    for k = 1:length(stats)
        bbox = stats(k).BoundingBox;
        aspectRatio = stats(k).MajorAxisLength / stats(k).MinorAxisLength;
        if aspectRatio >= 6 && bbox(3) * bbox(4) >= 150000
            [imgHeight, imgWidth, ~] = size(originalImg);
            bboxAdjusted = adjustBoundingBox(bbox, 50, imgWidth, imgHeight);
            croppedImg = imcrop(originalImg, bboxAdjusted);
            croppedImgList{end+1} = croppedImg;
            standardizedImg = imresize(croppedImg, [512, 1024]);
            standardizedImgList{end+1} = standardizedImg;
        end
    end
end

function bboxAdjusted = adjustBoundingBox(bbox, margin, maxWidth, maxHeight)
    bboxAdjusted(1) = max(bbox(1) - margin, 1);
    bboxAdjusted(2) = max(bbox(2) - margin, 1);
    bboxAdjusted(3) = min(bbox(3) + 2 * margin, maxWidth - bbox(1));
    bboxAdjusted(4) = min(bbox(4) + 2 * margin, maxHeight - bbox(2));
end
