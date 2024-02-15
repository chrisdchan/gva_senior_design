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
