import sys
import os
from dotenv import load_dotenv
load_dotenv()

sys.path.append(os.getenv("PROJECT_DIR"))

import pickle
import torch

from experiment import Experiment

class CustomUnpickler(pickle.Unpickler):
    def find_class(self, module, name):
        print(module, name)
        if module == "models":
            module = "segmentation/models"
        return super().find_class(module, name)

class DeployedModel:

    def __init__(self, experiment_path, device):
        assert experiment_path.endswith('.pkl')
        self.experiment_path = experiment_path
        self.load_model()

    def load_model(self):

        with open(self.experiment_path, 'rb') as f:
            exp_dict = pickle.load(f)

        model = exp_dict['model']
        self.name = exp_dict['name']
        weights = exp_dict['weights']

        weights = weights.to('cpu')
        model = self.model.to('cpu')

        self.model.load_state_dict(weights)
        self.model = model

    def predict(self, image):
        self.model.eval()

        with torch.no_grad():

            if len(image.shape) == 3:
                image = image.unsqueeze(0)

            pred = self.model(image)
            pred = pred > 0.5

        return pred