import cv2
import numpy as np
import matplotlib.pyplot as plt
from skimage.measure import label, regionprops
from skimage.morphology import rectangle, closing, binary_fill_holes

def processImageToROI(image):
    # Convert to grayscale if the image is in color
    if len(image.shape) == 3:
        grayImage = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)
    else:
        grayImage = image

    # Apply a Gaussian blur to reduce noise
    smoothedImg = cv2.GaussianBlur(grayImage, (5, 5), 2)
    
    # Use edge detection to highlight structures
    edgeImg = cv2.Canny(smoothedImg, 100, 200)
  
    # Use morphological closing to connect components that are pipette-like
    seClose = cv2.getStructuringElement(cv2.MORPH_RECT, (40, 100))
    closedImg = cv2.morphologyEx(edgeImg, cv2.MORPH_CLOSE, seClose)

    # Fill holes to solidify candidate pipette structures
    filledImg = binary_fill_holes(closedImg)

    # Label connected components
    labeledImg, _ = label(filledImg, return_num=True, connectivity=2)
    stats = regionprops(labeledImg)

    # Filter based on properties to eliminate non-pipette shaped objects
    roiCleanedBinary = np.zeros_like(filledImg, dtype=bool)
    for prop in stats:
        if prop.eccentricity > 0.6 and (prop.major_axis_length / prop.minor_axis_length) > 1.5 and prop.area > 1000000:
            roiCleanedBinary |= (labeledImg == prop.label)

    roiCleanedBinary = binary_fill_holes(roiCleanedBinary)

    return roiCleanedBinary.astype(np.uint8) * 255  # Convert boolean to uint8 for OpenCV compatibility

def adjustBoundingBox(bbox, margin, maxWidth, maxHeight):
    x, y, w, h = bbox
    adjustedBbox = [max(x - margin, 0),
                    max(y - margin, 0),
                    min(w + 2 * margin, maxWidth - x),
                    min(h + 2 * margin, maxHeight - y)]
    return adjustedBbox

def segmentAndStandardizePipettes(roiCleanedBinary, originalImg):
    labeledImg = label(roiCleanedBinary)
    stats = regionprops(labeledImg)
    
    croppedImgList = []
    standardizedImgList = []

    for prop in stats:
        aspectRatio = prop.major_axis_length / prop.minor_axis_length
        if aspectRatio >= 6:
            bbox = prop.bbox
            adjustedBbox = adjustBoundingBox(bbox, 50, originalImg.shape[1], originalImg.shape[0])
            croppedImg = originalImg[adjustedBbox[1]:adjustedBbox[1]+adjustedBbox[3], adjustedBbox[0]:adjustedBbox[0]+adjustedBbox[2]]
            croppedImgList.append(croppedImg)
            standardizedImg = cv2.resize(croppedImg, (6240, 1386))
            standardizedImgList.append(standardizedImg)

    return croppedImgList, standardizedImgList

# Load and display the original image
originalImg = cv2.imread('data/Testing_Image_1.jpg')
plt.figure(figsize=(6,6))
plt.imshow(cv2.cvtColor(originalImg, cv2.COLOR_BGR2RGB))
plt.title('Original Image')
plt.show()

# Process the image to obtain ROI cleaned binary image
roiCleaned = processImageToROI(originalImg)
plt.figure(figsize=(6,6))
plt.imshow(roiCleaned, cmap='gray')
plt.title('Cleaned Image')
plt.show()

# Segment and standardize pipettes
croppedImgList, standardizedImgList = segmentAndStandardizePipettes(roiCleaned, originalImg)

# Display or process standardized images as needed
for i, img in enumerate(standardizedImgList, 1):
    plt.figure(figsize=(6,6))
    plt.imshow(cv2.cvtColor(img, cv2.COLOR_BGR2RGB))
    plt.title(f'Pipette Tip {i}')
    plt.show()
    # Optionally, save the outputted image
    # cv2.imwrite(f'standardized_image_{i}.jpg', img)
