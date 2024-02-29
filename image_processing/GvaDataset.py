from torch.utils.data import Dataset
from PIL import Image
from torchvision import transforms
from utils import get_h5_tensor

import os
import h5py
import torch

class GvaDataset(Dataset):
    '''
    Assume images and labels that correspond to each other have the same name
    '''
    def __init__(self, image_dir, label_dir, transform=None):
        self.image_dir = image_dir
        self.label_dir = label_dir
        self.transform = transform
        self.names = [".".join(img_file.split('.')[:-1]) for img_file in os.listdir(image_dir) if img_file.endswith(('.jpg', '.jpeg', '.png'))]
        print(self.names)
        self.image_files = [os.path.join(image_dir, img_file) for img_file in os.listdir(image_dir) if img_file.endswith(('.jpg', '.jpeg', '.png'))]
        self.label_files = [os.path.join(label_dir, name + '.h5') for name in self.names]
        print(self.label_files)

    def __len__(self):
        return len(self.image_files)

    def _get_h5_tensor(self, file_path):
        with h5py.File(file_path, 'r') as f:
            data = f['exported_data'][()]
        tensor = torch.tensor(data)
        tensor = tensor.permute(2, 0, 1)
        return tensor

    def __getitem__(self, idx):
        image_path = self.image_files[idx]
        label_path = self.label_files[idx]
        name = self.names[idx]

        image = Image.open(image_path)
        label = get_h5_tensor(label_path)

        if self.transform:
            image = self.transform(image)
            label = self.transform(label)

        image = transforms.ToTensor()(image)
        label = label.float()
        label[label == 2] = 0

        return image, label, name

def test_dataset():
    lab_dir = "image_processing/data/masks/_Masks"
    img_dir = "image_processing/data/original/_Original"
    dataset = GvaDataset(img_dir, lab_dir)

    assert len(os.listdir(img_dir)) == len(dataset)

    for img, lab, name in dataset:
        assert img.shape[1:] == lab.shape[1:]
        assert lab.dtype == torch.float
        assert torch.max(lab) == 1
        assert torch.min(lab) == 0
