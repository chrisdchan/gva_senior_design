import h5py
import torch

def get_h5_tensor(file_path):
    with h5py.File(file_path, 'r') as f:
        data = f['exported_data'][()]
    tensor = torch.tensor(data)
    tensor = tensor.permute(2, 0, 1)
    return tensor