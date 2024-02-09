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
        self.epoch_loss_history = []

    def train(self, train_loader, epochs=10):
        N = len(train_loader)
        for epoch in range(1, epochs + 1):
            self.model.train()
            epoch_loss = 0
            with tqdm(enumerate(train_loader), 
                      total=N / train_loader.batch_size, 
                      desc=f'Epoch {self.starting_epoch + epoch}/{self.starting_epoch + epochs}', 
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

                    epoch_loss += loss.item()
                    pbar.set_postfix(loss = loss.item(), avg_loss=epoch_loss / (i + 1))
                    self.loss_history.append(loss.item())

            print(f'{self.starting_epoch +  epoch}/{self.starting_epoch + epochs} loss: {epoch_loss / N}')
            self.epoch_loss_history.append(epoch_loss / N)
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
        plt.plot(self.epoch_loss_history)
        plt.title("Training Loss")
        plt.xlabel("Epochs")
        plt.ylabel(self.criterion.__name__)

    def load_model(self, file_name):
        state_dict = torch.load(file_name)
        self.model.load_state_dict(state_dict)