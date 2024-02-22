from enum import Enum

class LossType(Enum):
    THRESHOLD = 1,
    PROBABILITY = 2

def iou_loss(y_true, y_pred, loss_type=LossType.PROBABILITY):
    """ Returns the iou loss given ground truth and a prediction
        inputs:
            y_true: Ground truth labels with values {0, 1} and of size (B, N_x , N_y)
            y_pred: Prediction with values [0, 1] and of size (B, N_x, N_y)
            loss_type: Enum specifying the type of loss
    """
    match loss_type:
        case LossType.PROBABILITY:
            return iou_loss_with_probabilities(y_true, y_pred)
        case LossType.THRESHOLD:
            return iou_loss_with_threshold(y_true, y_pred)

def iou_loss_with_threshold(y_true, y_pred):
    """ Returns the iou loss by thresholding probabilities
    """
    pass

def iou_loss_with_probabilities(y_true, y_pred):
    """ Returns the iou loss treating both inputs as probability distributions
    """
    pass

def dice_loss(y_true, y_pred):
    """ Returns the dice loss
        Inputs:
            y_true: Tensor<long> of size (B, Nx, Ny) with range {0, 1}
            y_pred: Tensor<float> of size (B, Nx, Nz) with range [0, 1]
    """
    return 1 - dice_coef(y_true, y_pred)

def dice_coef(y_true, y_pred):
    """ Returns the dice loss
        Inputs:
            y_true: Tensor<long> of size (B, Nx, Ny) with range {0, 1}
            y_pred: Tensor<float> of size (B, Nx, Nz) with range [0, 1]
    """
    epsilon = 1e-8
    numerator = 2 * (y_true * y_pred).sum()
    demominator = y_true.sum() + y_pred.sum()
    return (numerator + epsilon) / (demominator + epsilon)


import torch

def test_dice_loss():
    # Arrange
    y_true = torch.tensor([
        [[0, 1], [1, 0]],
        [[1, 1], [0, 0]]
    ])

    y_pred = torch.tensor([
        [[0.25, 0.6], [0.9, 0.2]],
        [[0.8, 0.6], [0.2, 0.2]],
    ])

    # Act
    actual = dice_loss(y_true, y_pred)
    expected = 0.2516129

    # Assert
    assert abs(actual - expected) < 1e-3
