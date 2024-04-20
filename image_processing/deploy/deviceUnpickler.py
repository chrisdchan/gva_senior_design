import pickle
import torch
import io

class DeviceUnpickler(pickle.Unpickler):
    device = 'cuda' if torch.cuda.is_available() else 'cpu'

    def find_class(self, module, name):
        if module == 'torch.storage' and name == '_load_from_bytes':
            return lambda b: torch.load(io.BytesIO(b), map_location=self.device)
        else:
            return super().find_class(module, name)