from torch.utils.data import Dataset
from PIL import Image
from torchvision import transforms

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
        self.image_files = [os.path.join(image_dir, img_file) for img_file in os.listdir(image_dir) if img_file.endswith(('.jpg', '.jpeg', '.png'))]
        self.label_files = [os.path.join(label_dir, lab_file) for lab_file in os.listdir(label_dir) if lab_file.endswith(('.h5'))]

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

        image = Image.open(image_path)
        label = self._get_h5_tensor(label_path)

        if self.transform:
            image = self.transform(image)
            label = self.transform(label)

        image = transforms.ToTensor()(image)
        label = label.float()
        label[label == 2] = 0

        return image, label

def test_dataset():
    img_dir = "data/images/"
    lab_dir = "data/labels/"
    dataset = GvaDataset(img_dir, lab_dir)

    img, lab = dataset[2]

    print(img.shape)
    print(lab.shape)

    assert img.shape[1:] == lab.shape[1:]
    assert lab.dtype == torch.float
    assert torch.max(lab) == 1
    assert torch.min(lab) == 0
