import torch
import pickle
import tqdm

class Experiment:
    """ Every instance of this class should represent one training run with a unique set of hyper parameters.
    """
    def __init__(self, model, criterion, optimizer, device='cpu'):
        self.model = model
        self.criterion = criterion
        self.optimizer = optimizer
        self.device = device

        self.loss = []
        self.epoch_loss = []


    def train(self, train_loader, epochs=10):
        """ Main Training Loop, takes in a DataLoader and the number of epochs
        """
        N = len(train_loader)
        for epoch in range(1, epochs + 1):
            self.model.train()
            epoch_loss = 0
            with tqdm(enumerate(train_loader), total=N / train_loader.batch_size, desc=f'Epoch {epoch}/{epochs}', unit='batch') as pbar:
                for i, data in pbar:
                    images, labels = data

                    images = images.to(self.device)
                    labels = labels.to(self.device)

                    pred = self.model(images)

                    loss = self.criterion(pred, labels)

                    self.optimizer.zero_grad()
                    loss.backward()
                    torch.nn.utils.clip_grad_norm_(self.model.parameters(), 1.0)

                    epoch_loss += loss
                    pbar.set_postfix(loss = loss)

            print(f'{epoch}/{epochs} loss: {epoch_loss / N}')
            self.epoch_loss.append(epoch_loss / N)
            epoch_loss = 0
        
        print("Training Complete")

    def save_weights(self, file_name):
        """ Saves weights as a .pth file
        """
        assert file_name.ends_with(".pth")
        torch.save(self.model.state_dict(), file_name)

    def save_loss(self, file_name):
        assert file_name.ends_with(".pkl")

        loss_dict = dict(loss=self.loss, epoch_loss=self.epoch_loss)

        with open(file_name, 'wb') as f:
            pickle.dump(loss_dict, f)

    def plot_loss():
        pass

    def load_model(self, file_name):
        pass