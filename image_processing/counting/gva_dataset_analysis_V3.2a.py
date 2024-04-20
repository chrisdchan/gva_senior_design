# File: gva_dataset_analysis_V3.1.py
# Author: Andrew Chang (achang02@bu.edu), 4/12/2024
# Description: Counting CFU's and calculating the CFU/mL

from skimage import morphology, measure, filters, util, io
from skimage.color import label2rgb
from skimage.measure import regionprops
import matplotlib.patches as mpatches
import matplotlib.patches as patches
import matplotlib.pyplot as plt
import numpy as np
import h5py


### Functions ###

def load_and_binarize_original_mask(file_path, h):
    """ Load and display the original binary mask from an H5 file.
    """
    with h5py.File(file_path, 'r') as f:
        dataset_name = list(f.keys())[0]
        mask = np.array(f[dataset_name])

    if mask.ndim > 2:
        mask = mask.squeeze()
        if mask.ndim > 2:
            mask = mask[:, :, 0]

    if mask.shape[0] > 1000:  # Ensure the image is tall enough to be cropped
        mask = mask[550:-550, :]
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

    # Check if the mask is already binary (0s and 1s only)
    if not np.array_equal(mask, mask.astype(bool)):
        # The mask is greyscale, apply Otsu's method to binarize
        thresh = filters.threshold_otsu(mask)
        mask = mask > thresh
    return mask, pixel_to_mm_ratio


def preprocess_count_and_annotate_objects(binary_mask):
    """ Process the binary mask, count objects, and annotate them.
    """
    # Invert mask if necessary to ensure foreground is white
    if np.mean(binary_mask) > 0.5:
        binary_mask = util.invert(binary_mask)

    # Apply morphological closing
    closed_mask = morphology.closing(binary_mask, morphology.disk(2))

    # Label the objects in the closed mask
    labeled_mask = measure.label(closed_mask)
    num_objects = np.max(labeled_mask)

    # # Display processed and labeled mask with annotations
    # plt.figure(figsize=(10, 6))
    # labeled_overlay = label2rgb(labeled_mask, image=binary_mask, bg_label=0, alpha=0.4)
    # plt.imshow(labeled_overlay)

    # # # Annotate each labeled region with its corresponding number
    # # if num_objects < 50:
    # #     for region in measure.regionprops(labeled_mask):
    # #         # Draw a rectangle around the region and label it
    # #         y, x = region.centroid
    # #         plt.text(x, y, str(region.label), color='red', ha='center', va='center')
            
    # plt.title(f'Processed Mask with {num_objects} Objects Labeled')
    # plt.axis('off')
    # plt.show()
    return num_objects, labeled_mask


def extract_colony_positions(labeled_image):
    """ Extract the x and y positions of colonies from a labeled image.
    """
    regions = regionprops(labeled_image)
    x_positions = [region.centroid[1] for region in regions]  # Assuming the second coordinate is the x-position
    y_positions = [region.centroid[0] for region in regions]  # Assuming the first coordinate is the y-position
    return x_positions, y_positions


def estimate_cfus(x_positions, y_positions, h, max_radius, volume_in_ml):
    """ Estimate the CFU/mL given the positions of simulated colonies within a conical geometry.
    """
    y1, y2 = np.min(y_positions), np.max(y_positions)  # Getting the positions of the first and last colonies
    integral_value = (y2**3 - y1**3) / h**3  # Computing the integral of the PDF between y1 and y2
    # Estimating the CFUs/mL
    cfus_per_ml = len(x_positions) / (integral_value * volume_in_ml)
    return cfus_per_ml, y1, y2, len(x_positions)


def crop_image(binary_mask, pixel_to_mm_ratio, h, max_radius, volume_in_ml):
    """ Automatically crop the image into specified sections and process each.
    """
    image_height = binary_mask.shape[0]
    results = []

    # Define crop sections
    crop_sections = {
        "Whole image": binary_mask,
        "Bottom 20%": binary_mask[:image_height // 5, :],
        "Second 20%": binary_mask[image_height // 5: 2 * image_height // 5, :],
        "Third 20%": binary_mask[2 * image_height // 5: 3 * image_height // 5, :],
        "Fourth 20%": binary_mask[3 * image_height // 5: 4 * image_height // 5, :],
        "Top 20%": binary_mask[4 * image_height // 5:, :],
        "Bottom third": binary_mask[:image_height // 3, :],
        "Middle third": binary_mask[image_height // 3: 2 * image_height // 3, :],
        "Top third": binary_mask[2 * image_height // 3:, :],
        "Bottom half": binary_mask[:image_height // 2, :],
        "Top half": binary_mask[image_height // 2:, :]
    }

    # Process each crop section
    for label, cropped_image in crop_sections.items():
        y_offset = {
            "Whole image": 0,
            "Bottom 20%": 0,
            "Second 20%": image_height // 5,
            "Third 20%": 2 * image_height // 5,
            "Fourth 20%": 3 * image_height // 5,
            "Top 20%": 4 * image_height // 5,
            "Bottom third": 0,
            "Middle third": image_height // 3,
            "Top third": 2 * image_height // 3,
            "Bottom half": 0,
            "Top half": image_height // 2
        }[label]

        num_objects, labeled_mask = preprocess_count_and_annotate_objects(cropped_image)
        x_positions, y_positions = extract_colony_positions(labeled_mask)
        y_positions = [(y + y_offset) * pixel_to_mm_ratio for y in y_positions]
        cfus_per_ml, y1, y2, x = estimate_cfus(x_positions, y_positions, h, max_radius, volume_in_ml)
        results.append((label, cfus_per_ml, num_objects, x, y1, y2))
    return results


def main():
    binary_mask, pixel_to_mm_ratio = load_and_binarize_original_mask(file_path, h)
    results = crop_image(binary_mask, pixel_to_mm_ratio, h, max_radius, volume_in_ml)
    
    # Printing results in a formatted table
    print("-" * 60)  # Print a separator line for better visibility
    print(f"{'Crop':<15}{'Y1 (Min)':>10}{'Y2 (Max)':>10}{'Total Objects':>15}{'CFU/mL':>10}")
    print("-" * 60)  # Print a separator line for better visibility
    for result in results:
        label, cfus_per_ml, num_objects, x_count, y1, y2 = result
        print(f"{label:<15}{y1:>10.2f}{y2:>10.2f}{num_objects:>15}{cfus_per_ml:>10.2f}")
    print("-" * 60)  # Print a separator line for better visibility





### Inputs ###

if __name__ == "__main__":
    file_path = r"C:\Users\headh\MATLAB Drive\BU\Senior Design\Segmented Images\Youssef1\YH7.h5"
    h = 50.8  # Height of pipette tip
    max_radius = 4.35  # Radius of pipette tip
    volume_in_ml = 1  # Volume of liquid in tip (mL's)
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
    - a: Renamed labels and revised the final table. Addid 500 pixel crop.

"""










