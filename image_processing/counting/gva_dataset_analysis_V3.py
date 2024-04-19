# File: gva_dataset_analysis_V3.0.py
# Author: Andrew Chang (achang02@bu.edu), 4/5/2024
# Description: Counting CFU's and calculating the CFU/mL

from skimage import morphology, measure, filters, util, io
from skimage.color import label2rgb
import matplotlib.pyplot as plt
import matplotlib.patches as patches
import matplotlib.patches as mpatches
import h5py
import numpy as np


def load_and_binarize_original_mask(file_path):
    """ Load and display the original binary mask from an H5 file.
    """
    with h5py.File(file_path, 'r') as f:
        dataset_name = list(f.keys())[0]
        mask = np.array(f[dataset_name])

    if mask.ndim > 2:
        mask = mask.squeeze()
        if mask.ndim > 2:
            mask = mask[:, :, 0]

    # Check if the mask is already binary (0s and 1s only)
    if not np.array_equal(mask, mask.astype(bool)):
        # The mask is greyscale, apply Otsu's method to binarize
        thresh = filters.threshold_otsu(mask)
        mask = mask > thresh
    return mask


def crop_and_display_image(binary_mask):
    """ Display the binary mask with a red border line
    """
    fig, ax = plt.subplots()
    ax.imshow(binary_mask, cmap='gray')
    rect = patches.Rectangle((0, 0), binary_mask.shape[1], binary_mask.shape[0], linewidth=1, edgecolor='r', facecolor='none')
    ax.add_patch(rect)
    plt.show()

    # Ask user for input on how to crop the image
    print("Select cropping option:")
    print("1 - Top third of the image")
    print("2 - Middle third of the image")
    print("3 - Bottom third of the image")
    print("4 - Top half of the image")
    print("5 - Bottom half of the image")
    print("6 - Keep the whole image")
    option = input("Enter your choice (1-6): ")
    
    # Perform the cropping based on user input
    half = binary_mask.shape[0] // 2
    third = binary_mask.shape[0] // 3
    if option == '1':
        cropped_image = binary_mask[:third, :]
    elif option == '2':
        cropped_image = binary_mask[third:2*third, :]
    elif option == '3':
        cropped_image = binary_mask[2*third:, :]
    elif option == '4':
        cropped_image = binary_mask[:half, :]
    elif option == '5':
        cropped_image = binary_mask[half:, :]
    elif option == '6':
        cropped_image = binary_mask
    else:
        print("Invalid choice. Keeping the whole image.")
        cropped_image = binary_mask
    return cropped_image


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

    # Display processed and labeled mask with annotations
    plt.figure(figsize=(10, 6))
    labeled_overlay = label2rgb(labeled_mask, image=binary_mask, bg_label=0, alpha=0.4)
    plt.imshow(labeled_overlay)

    # Annotate each labeled region with its corresponding number
    if num_objects < 50:
        for region in measure.regionprops(labeled_mask):
            # Draw a rectangle around the region and label it
            y, x = region.centroid
            plt.text(x, y, str(region.label), color='red', ha='center', va='center')
            
    plt.title(f'Processed Mask with {num_objects} Objects Labeled')
    plt.axis('off')
    plt.show()
    return num_objects


def calculate_cfu_ml(num_objects, dilution_factor, volume_plated_ml):
    """ Calculate the CFU/mL of the contents.
    """
    return num_objects / (dilution_factor * volume_plated_ml)


def main():
    binary_mask = load_and_binarize_original_mask(file_path)
    cropped_binary_mask = crop_and_display_image(binary_mask)
    num_objects = preprocess_count_and_annotate_objects(cropped_binary_mask)
    cfu_ml = calculate_cfu_ml(num_objects, dilution_factor, volume_plated_ml)
    print(f"Number of objects: {num_objects}")
    print(f"CFU/mL: {cfu_ml}")





if __name__ == "__main__":
    file_path = r"C:\Users\headh\MATLAB Drive\BU\Senior Design\Segmented Images\Youssef1\YH_7.h5"
    dilution_factor = 10  # Update based on your experiment
    volume_plated_ml = 0.1  # Update based on your experiment
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

"""










