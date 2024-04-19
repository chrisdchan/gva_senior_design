# File gva.py
# Author: Chris Chan
# Description: Entry point for running pipeline for gva analysis

import yaml
from deployedModel import DeployedModel
from counting.gva_dataset_analysis_V3 import crop_and_display_image, preprocess_count_and_annotate_objects, calculate_cfu_ml 
from PIL import Image

import os
from dotenv import load_dotenv
load_dotenv()

with open('../config.yaml', 'rt') as config_file:
    CONFIG = list(yaml.safe_load_all(config_file.read()))[0]

class GVA:

    def __init__(self):
        model_path = os.path.join(os.getenv('PROJECT_DIR'), CONFIG['segmentation']['model-path'])
        self.model_path = model_path
        self.dilution_factor = CONFIG['counting']['dilution-factor']
        self.volumne_platted_ml = CONFIG['counting']['volume-platted-ml']

    def crop_image(self, image):
        # TODO
        return [image]

    def segment_image(self, cropped_img):
        deployed_model = DeployedModel(self.model_path, CONFIG['device'])
        return deployed_model.predict(cropped_img)

    def count_cfus(self, segmented_img):
        cropped_binary_mask = crop_and_display_image(segmented_img)
        num_objects = preprocess_count_and_annotate_objects(cropped_binary_mask)
        cfu_ml = calculate_cfu_ml(num_objects, self.dilution_factor, self.volume_plated_ml)
        return cfu_ml, num_objects

    def run(self, image_file):
        image = Image.open(image_file)
        cropped_imgs = self.crop_image(image)
        segmented_imgs = [self.segment_image(img) for img in cropped_imgs]
        cfu_counts = [self.count_cfus(img) for img in segmented_imgs]

        print(cfu_counts)

def main():
    test_image = os.path.join(os.getenv('PROJECT_DIR'), "image_processing/data/images/test/YH_3.png")
    gva = GVA()
    gva.run(test_image)

if __name__ == '__main__':
    main()
