from torch.utils.data import Dataset
from PIL import Image
import os

class GvaDataset(Dataset):
    def __init__(self, image_dir, transform=None):
        self.image_dir = image_dir
        self.transform = transform
        self.image_files = [os.path.join(image_dir, img_file) for img_file in os.listdir(image_dir) if img_file.endswith(('.jpg', '.jpeg', '.png'))]

    def __len__(self):
        return len(self.image_files)

    def __getitem__(self, idx):
        image_path = self.image_files[idx]
        image = Image.open(image_path)
        if self.transform:
            image = self.transform(image)
        return image