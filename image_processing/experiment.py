import sys
import os
from dotenv import load_dotenv
load_dotenv()

sys.path.append(os.getenv("PROJECT_DIR"))

import torch
import pickle
import matplotlib.pyplot as plt
from tqdm import tqdm
import os
import torch

import numpy as np

from deploy.deviceUnpickler import DeviceUnpickler

VERSION = 1

class Experiment:
    def __init__(self, model=None, criterion=None, optimizer=None, name=None, bench=100, device='cuda'):
        self.model = model
        self.criterion = criterion
        self.optimizer = optimizer
        self.device = device
        self.current_epoch = 0
        self.name = name
        self.bench = bench

        self.train_loss_history = []
        self.val_loss_history = []

    def assert_model_init(self):
        assert self.model != None
        assert self.criterion != None
        assert self.optimizer != None

    def train(self, train_loader, validation_loader, epochs=10, should_bench=True, bench=None):
        self.assert_model_init()
        
        N = len(train_loader)
        end_epoch = self.current_epoch + epochs

        if bench == None:
            bench = self.bench
        
        for epoch in range(1, epochs + 1):
            self.model.train()
            epoch_tot_train_loss = 0
            with tqdm(enumerate(train_loader), 
                      total=N, 
                      desc=f'Epoch {self.current_epoch}/{end_epoch}', 
                      unit='batch') as pbar:
                for i, data in pbar:
                    images, labels, _ = data

                    images = images.to(self.device)
                    labels = labels.to(self.device)

                    self.optimizer.zero_grad()

                    pred = self.model(images)

                    loss = self.criterion(pred, labels)
                    loss.backward()
                    self.optimizer.step()

                    epoch_tot_train_loss += loss.item()
                    pbar.set_postfix(loss = loss.item(), avg_loss=epoch_tot_train_loss / (i + 1))

            self.model.eval()
            with torch.no_grad():
                epoch_tot_val_loss = 0
                for images, labels, _ in validation_loader:
                    images = images.to(self.device)
                    labels = labels.to(self.device)
                    pred = self.model(images)
                    val_loss = self.criterion(pred, labels)
                    epoch_tot_val_loss += val_loss.item()
                    
            self.current_epoch += 1
            
            epoch_train_loss = epoch_tot_train_loss / N
            epoch_val_loss = epoch_tot_val_loss / len(validation_loader)
            print(f'{self.current_epoch}/{end_epoch} train_loss: {epoch_train_loss} val loss: {epoch_val_loss}')
            self.train_loss_history.append(epoch_train_loss)
            self.val_loss_history.append(epoch_val_loss)

            if self.current_epoch % bench == 0:
                self.save_experiment()
        
        print("Training Complete")
        
    def save_experiment(self, path=None):

        self.assert_model_init()

        if path == None:
            exp_file_name = f"{self.current_epoch}.pkl"
            weights_file_name = f"{self.current_epoch}.pt"
            weights_dir = "/projectnb/dunlop/chrisdc/gva_senior_design/image_processing/weights/"
            model_dir = os.path.join(weights_dir, self.name)
            os.makedirs(model_dir, exist_ok = True)
            exp_path = os.path.join(model_dir, exp_file_name)
            weights_path = os.path.join(model_dir, weights_file_name)
        
        assert path.endswith(".pkl")

        exp_dict = dict(
            version = VERSION,
            name = self.name,
            model = self.model,
            criterion = self.criterion,
            optimizer = self.optimizer,
            weights = self.model.state_dict(),
            current_epoch = self.current_epoch,
            train_loss_history = self.train_loss_history, 
            val_loss_history = self.val_loss_history
        )

        with open(exp_path, 'wb') as f:
            pickle.dump(exp_dict, f)

        torch.save(self.model.state_dict(), weights_path)


    def load_experiment(self, path):
        
        assert path.endswith(".pkl")

        with open(path, 'rb') as f:
            exp_dict = DeviceUnpickler(f).load()

        self.name = exp_dict['name']
        self.model = exp_dict['model']
        self.criterion = exp_dict['criterion']
        self.optimizer = exp_dict['optimizer']

        state_dict = exp_dict['weights']
        self.model.load_state_dict(state_dict)

        self.current_epoch = exp_dict["current_epoch"]
        self.train_loss_history = exp_dict["train_loss_history"]
        self.val_loss_history = exp_dict["val_loss_history"]

    def plot_loss(self, title="Training Loss", xlabel="Epochs", ylabel="Dice Loss", k=1):

        train_loss = np.array(self.train_loss_history)
        avg_train_loss = np.average(train_loss.reshape(-1, k), axis=1)

        val_loss = np.array(self.val_loss_history)
        avg_val_loss = np.average(val_loss.reshape(-1, k), axis=1)

        epochs = [i * k for i in range(len(avg_train_loss))]

        plt.plot(epochs, avg_train_loss, color='blue', label='Training Loss')
        plt.plot(epochs, avg_val_loss, color='green', label='Validation Loss')
        plt.title(title)
        plt.legend()
        plt.xlabel(xlabel)
        plt.ylabel(ylabel)

    def qualitative_eval(self, data, suptitle=None):
        fig, ax = plt.subplots(len(data), 3, figsize=(10, len(data)*3))
        if suptitle == None:
            suptitle = f"Model trained for {self.current_epoch} Epochs"
        fig.suptitle(suptitle)
        self.model.eval()
        with torch.no_grad():
            for i, sample in enumerate(data):
                img, lab, file = sample
                if len(img.shape) == 3:
                    img = img.unsqueeze(0)
                    
                img = img.to(self.device)
                lab = lab.to(self.device)
                
                pred = self.model(img)
                fuzzy_loss = self.criterion(pred, lab)
                pred = pred > 0.5
                pred_loss = self.criterion(pred, lab)
                
                img = img.to('cpu')
                img = img.squeeze()
                img = img.permute(1, 2, 0)

                lab = lab.to('cpu')
                lab = lab.squeeze()
                    
                pred = pred.to('cpu')
                pred = pred.squeeze()

                pred_title = f"{self.criterion.__name__}: {pred_loss.item():.4f} (fuzzy: {fuzzy_loss.item():.4f})"
        
                ax[i, 0].imshow(img)
                ax[i, 0].axis('off')
                ax[i, 0].set_title(file)
                ax[i, 1].imshow(lab, cmap='gray')
                ax[i, 1].axis('off')
                ax[i, 1].set_title("ground truth")
                ax[i, 2].imshow(pred, cmap='gray')
                ax[i, 2].axis('off')
                ax[i, 2].set_title(pred_title)