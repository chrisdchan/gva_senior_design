import torch
import pickle
import matplotlib.pyplot as plt
from tqdm import tqdm


class Experiment:
    def __init__(self, model, criterion, optimizer, device='cpu', starting_epoch=0):
        self.model = model
        self.criterion = criterion
        self.optimizer = optimizer
        self.device = device
        self.starting_epoch = starting_epoch

        self.loss_history = []
        self.validation_loss_history = []
        self.epoch_loss_history = []

    def train(self, train_loader, validation_loader, epochs=10):
        N = len(train_loader)
        for epoch in range(1, epochs + 1):
            self.model.train()
            epoch_loss = 0
            with tqdm(enumerate(train_loader), 
                      total=N, 
                      desc=f'Epoch {self.starting_epoch + epoch}/{self.starting_epoch + epochs}', 
                      unit='batch') as pbar:
                for i, data in pbar:
                    images, labels, _ = data

                    images = images.to(self.device)
                    labels = labels.to(self.device)

                    self.optimizer.zero_grad()

                    pred = self.model(images)
                    print(pred.shape)
                    loss = self.criterion(pred, labels)
                    loss.backward()
                    self.optimizer.step()

                    epoch_loss += loss.item()
                    pbar.set_postfix(loss = loss.item(), avg_loss=epoch_loss / (i + 1))
                    self.loss_history.append(loss.item())

            with torch.no_grad():
                epoch_val_loss = 0
                for images, labels, _ in validation_loader:
                    images = images.to(self.device)
                    labels = labels.to(self.device)
                    pred = self.model(images)
                    val_loss = self.criterion(pred, labels)
                    epoch_val_loss += val_loss.item()
            val_loss = 4

            print(f'{self.starting_epoch +  epoch}/{self.starting_epoch + epochs} loss: {epoch_loss / N} val loss: {val_loss / len(validation_loader)}')
            self.epoch_loss_history.append(epoch_loss / N)
            self.validation_loss_history.append(val_loss / len(validation_loader))
            epoch_loss = 0
        
        print("Training Complete")

    def save_weights(self, file_name):
        assert file_name.ends_with(".pth")

        torch.save(self.model.state_dict(), file_name)

    def save_loss(self, file_name):
        assert file_name.ends_with(".pkl")

        loss_dict = dict(loss=self.loss, epoch_loss=self.epoch_loss)

        with open(file_name, 'wb') as f:
            pickle.dump(loss_dict, f)

    def plot_loss(self):
        plt.plot(self.epoch_loss_history, color='blue', label='Training Loss')
        plt.plot(self.validation_loss_history, color='green', label='Validation Loss')
        plt.title("Training Loss")
        plt.legend()
        plt.xlabel("Epochs")
        plt.ylabel(self.criterion.__name__)

    def load_model(self, file_name):
        state_dict = torch.load(file_name)
        self.model.load_state_dict(state_dict)