import sys
import os
from torchvision.transforms import v2
from dotenv import load_dotenv
load_dotenv()

sys.path.append(os.getenv("PROJECT_DIR"))

import torch

from deviceUnpickler import DeviceUnpickler


class DeployedModel:

    def __init__(self, experiment_path, device):
        assert experiment_path.endswith('.pkl')
        self.experiment_path = experiment_path
        self.load_model()

    def load_model(self):

        with open(self.experiment_path, 'rb') as f:
            exp_dict = DeviceUnpickler(f).load()

        self.model = exp_dict['model']
        self.name = exp_dict['name']
        weights = exp_dict['weights']
        self.model = self.model.to('cpu')
        self.model.load_state_dict(weights)

    def predict(self, image):
        self.model.eval()

        with torch.no_grad():
            image = v2.Resize((1024, 512))(image)
            image = v2.ToTensor()(image)
            image = image.unsqueeze(0)
            pred = self.model(image)
            pred = pred > 0.5

        return pred