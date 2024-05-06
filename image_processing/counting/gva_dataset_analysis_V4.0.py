# File: gva_dataset_analysis_V4.0.py
# Author: Andrew Chang (achang02@bu.edu), 5/2/2024
# Description: Counting CFU's and calculating the CFU/mL

from skimage import morphology, measure, filters, util
from skimage.morphology import remove_small_objects
import matplotlib.patches as patches
import matplotlib.pyplot as plt
import numpy as np
import random
import time
import torch


### Functions ###

def load_and_binarize_original_mask(file_path, h):
    """ Load and display the original binary mask from a .pt file. 
    """
    mask_tensor = torch.load(file_path)
    mask = mask_tensor.numpy()
    
    if mask.ndim > 2:
        mask = mask.squeeze()
    
    if mask.shape[0] > 1000:  # Ensure the image is tall enough to be cropped
        mask = mask[500:-600, :]
    else:
        raise ValueError("Image height is less than 1000 pixels; cannot crop 500 pixels from both top and bottom.")
    
    fig, ax = plt.subplots()
    ax.imshow(mask, cmap='gray')
    rect = patches.Rectangle((0, 0), mask.shape[1], mask.shape[0], linewidth=1, edgecolor='black', facecolor='none')
    ax.add_patch(rect)
    plt.show()

    mask = np.flipud(mask)
    image_height_in_pixels = mask.shape[0]
    pixel_to_mm_ratio = h / image_height_in_pixels
    
    # Binarize the mask using Otsu's threshold if it's not already binary
    if not np.array_equal(mask, mask.astype(bool)):
        thresh = filters.threshold_otsu(mask)
        mask = mask > thresh

    return mask, pixel_to_mm_ratio


def adaptive_morphological_operation(binary_mask):
    """ Apply morphological closing with an adaptive disk size based on object sizes. 
    """
    labeled_mask = measure.label(binary_mask)
    regions = measure.regionprops(labeled_mask)
    if regions:
        # Calculate average object size
        average_size = np.mean([region.area for region in regions])
        # Determine disk size as a function of average size (e.g., sqrt of area gives approx. diameter)
        disk_size = int(np.sqrt(average_size) / 2)
    else:
        disk_size = 10  # Default to a minimal disk size if no objects

    # Ensure the disk size is within reasonable bounds
    disk_size = 25 - max(1, min(disk_size, 20))
    print(disk_size)
    # Applying the morphological closing operation
    closed_mask = morphology.closing(binary_mask, morphology.disk(disk_size))
    return closed_mask


def preprocess_count_and_annotate_objects(binary_mask, min_size=10):
    """ Process the binary mask, count objects, and annotate them.
    """
    # Invert mask if necessary to ensure foreground is white
    if np.mean(binary_mask) > 0.5:
        binary_mask = util.invert(binary_mask)

    # Apply adaptive morphological operation to refine binary mask
    closed_mask = adaptive_morphological_operation(binary_mask)

    # Ensure the mask is binary before removing small objects
    binary_mask = closed_mask > 0  # Convert any positive labels to True, everything else to False

    # Remove small objects to reduce noise and loose pixels around colonies
    refined_mask = remove_small_objects(binary_mask, min_size=min_size)

    # Label the objects in the refined mask
    labeled_mask = measure.label(refined_mask)
    num_objects = np.max(labeled_mask)

    return num_objects, labeled_mask


def calculate_overall_cfuml(binary_mask, pixel_to_mm_ratio, h, volume_in_ml):
    """ Calculate and print the overall number of objects in the image and CFU/mL count.
    """
    num_objects, _ = preprocess_count_and_annotate_objects(binary_mask)
    image_height = binary_mask.shape[0]
    scaled_y1 = 0 * pixel_to_mm_ratio  # Start of the image
    scaled_y2 = image_height * pixel_to_mm_ratio  # End of the image
    integral_value = (scaled_y2**3 - scaled_y1**3) / h**3
    cfus_per_ml = num_objects / (integral_value * volume_in_ml)
    print(f"Overall Number of Objects: {num_objects}")
    print(f"Overall CFU/mL: {cfus_per_ml:.2f}")


def generate_random_crop_ranges(image_height, num_crops=200, min_range_fraction=0.15):
    min_range = int(image_height * min_range_fraction)
    ranges = []
    for _ in range(num_crops):
        y1 = random.randint(0, image_height - min_range)
        y2 = random.randint(y1 + min_range, image_height)
        ranges.append((y1, y2))
    return ranges


def crop_image(binary_mask, pixel_to_mm_ratio, h, volume_in_ml, crop_ranges):
    results = []
    for y1, y2 in crop_ranges:
        cropped_image = binary_mask[y1:y2, :]
        num_objects, _ = preprocess_count_and_annotate_objects(cropped_image)
        if num_objects < 40:
            continue  # Skip this crop if fewer than 25 colonies are counted
        scaled_y1 = y1 * pixel_to_mm_ratio
        scaled_y2 = y2 * pixel_to_mm_ratio
        integral_value = (scaled_y2**3 - scaled_y1**3) / h**3
        cfus_per_ml = num_objects / (integral_value * volume_in_ml)
        results.append((cfus_per_ml, num_objects, scaled_y1, scaled_y2))
    return results


def main():
    binary_mask, pixel_to_mm_ratio = load_and_binarize_original_mask(file_path, h)
    image_height = binary_mask.shape[0]
    random_ranges = generate_random_crop_ranges(image_height)
    start_time = time.time()
    results = crop_image(binary_mask, pixel_to_mm_ratio, h, volume_in_ml, random_ranges)
    end_time = time.time()

    if not results:
        print("No crops with more than 10 colonies were found.")
        return
    
    # Calculate overall CFU/mL for the entire image for reference
    calculate_overall_cfuml(binary_mask, pixel_to_mm_ratio, h, volume_in_ml)

    # Unpacking results for plotting and analysis
    cfu_values, object_counts, y1s, y2s = zip(*results)

    # Calculating the average CFU/mL from valid crops
    average_cfu_ml = sum(cfu_values) / len(cfu_values)
    print(f"Average CFU/mL for valid crops: {average_cfu_ml:.2f}")
    print(f"Execution time for processing 200 crops: {end_time - start_time:.2f} seconds")

    # Calculating percent error for each crop compared to the expected CFU/mL
    percent_errors = [((cfu - expected_cfu_ml) / expected_cfu_ml) * 100 for cfu in cfu_values]
    average_percent_error = sum(percent_errors) / len(percent_errors)
    print(f"Average Percent Error: {average_percent_error:.2f}%")

    # Plotting the histogram of CFU/mL results
    plt.figure(figsize=(15, 5))
    plt.subplot(1, 3, 1)
    plt.hist(cfu_values, bins=20, color='blue', alpha=0.7)
    plt.title('Histogram of CFU/mL Results')
    plt.xlabel('CFU/mL')
    plt.ylabel('Frequency')
    plt.axvline(expected_cfu_ml, color='red', linestyle='dashed', linewidth=1)
    plt.text(expected_cfu_ml, plt.ylim()[1]*0.9, '  Hand Counted\n  CFU/mL', color='red', ha='left')

    # Plotting the histogram of percent errors
    plt.subplot(1, 3, 2)
    plt.hist(percent_errors, bins=40, range=(-100, 100), color='red', alpha=0.7)
    plt.title('Histogram of Percent Errors')
    plt.xlabel('Percent Error (%)')
    plt.ylabel('Frequency')
    plt.xlim(-100, 100)

    # Scatter plot showing the relationship between percent error and number of objects
    plt.subplot(1, 3, 3)
    plt.scatter(object_counts, percent_errors, color='green', alpha=0.5)
    plt.title('Scatter Plot of Percent Error vs. Number of Objects')
    plt.xlabel('Number of Objects')
    plt.ylabel('Percent Error (%)')
    plt.grid(True)
    plt.tight_layout()
    plt.show()





### Inputs ###

if __name__ == "__main__":
    
    # file_path = r"C:\Users\headh\MATLAB Drive\BU\Senior Design\Segmented Images\_Masks\YH_3.pt"
    # file_path = r"C:\Users\headh\MATLAB Drive\BU\Senior Design\Segmented Images\_Masks\ACC_mask6.pt"
    # file_path = r"C:\Users\headh\MATLAB Drive\BU\Senior Design\Segmented Images\_Masks\ACC_mask7.pt"
    file_path = r"C:\Users\headh\MATLAB Drive\BU\Senior Design\Segmented Images\_Masks\ACC_mask11.pt"
    
    h = 50.8  # Height of pipette tip
    volume_in_ml = 1  # Volume of liquid in tip (mL's)
    expected_cfu_ml = 161
    main()

    



### Changelog ###

"""
Version 1
- 1.0: Upload tensor and count connected components
- 1.1: Streamline code
- 1.2: Added Otsu method of object labeling
- 1.3: Improved visualization of image segmentation
Version 2
- 2.0: Added binarization of masks
- 2.1: Streamline code
- 2.2: Added morphological closing
- 2.3: Added initial CFU/mL calculation
Version 3
- 3.0: Added cropping code
- 3.1: Added Chaterjee method of CFU/mL calculation
- 3.2: Imrpoved upon Chaterjee method 
    - a: Renamed labels and revised the final table
    - b: Changed input file from h5 to pt
- 3.3: Implement random y-range analysis
Version 4
- 4.0: Final Version

"""