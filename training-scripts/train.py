
from GvaDataset import GvaDataset
from torch.utils.data import random_split, DataLoader
import torchvision.transforms as transforms 
from models.unet import UNet
from experiment import Experiment
import torch.optim as optim
import torch.nn as nn
import torch



def run():
    transform = transforms.Compose([
        transforms.Resize((1024, 512))
    ])

    labels_path = "data/masks/_Masks"
    images_path = "data/original/_Original"
    dataset = GvaDataset(images_path, labels_path, transform=transform)
    train_loader = DataLoader(dataset, batch_size=2, shuffle=True)

    device = 'cuda' if torch.cuda.is_available() else 'cpu'
    model = UNet(in_channels=3, out_channels=1).to(device)
    optimizer = optim.Adam(model.parameters())
    criterion = nn.BCELoss()
    experiment = Experiment(model, criterion, optimizer, device)

if __name__ == '__main__':
    run()