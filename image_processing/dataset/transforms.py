import torchvision.transforms.functional as TF
import torch
import random

class Resize:
    def __init__(self, size=(1024, 512)) -> None:
        self.size = size

    def __call__(self, img: torch.Tensor, lab: torch.Tensor):
        img = TF.resize(img, self.size)
        lab = TF.resize(lab, self.size)
        return img, lab

class HorizontalFlip:
    def __init__(self, p=0.5) -> None:
        self.p = p

    def __call__(self, img: torch.Tensor, lab: torch.Tensor):
        if random.random() > self.p:
            img = TF.hflip(img)
            lab = TF.hflip(lab)
        return img, lab

class VerticalFlip:
    def __init__(self, p=0.5) -> None:
        self.p = p

    def __call__(self, img: torch.Tensor, lab: torch.Tensor):
        if random.random() > self.p:
            img = TF.vflip(img)
            lab = TF.vflip(lab)
        return img, lab

class Invert:
    def __init__(self, p=0.5) -> None:
        self.p = p

    def __call__(self, img: torch.Tensor, lab: torch.Tensor):
        if random.random() > self.p:
            img = TF.invert(img)
        return img, lab

class Jitter:

    def __init__(self, brightness=None, contrast=None, hue=None, saturation=None) -> None:
        if brightness is None:
            brightness = [0.5, 1.5]
        if contrast is None:
            contrast = [0.5, 1.5]
        if hue is None:
            hue = [-0.5, 0.5]
        if saturation is None:
            saturation = [0.5, 1.5]

        self.brightness_min, self.brightness_max = brightness
        self.contrast_min, self.contrast_max = contrast
        self.hue_min, self.hue_max = hue
        self.saturation_min, self.saturation_max = saturation


    def __call__(self, img: torch.Tensor, lab: torch.Tensor):

        brightness = self.brightness_min + random.random() * (self.brightness_max - self.brightness_min)
        contrast = self.contrast_min + random.random() * (self.contrast_max - self.contrast_min)
        hue = self.hue_min + random.random() * (self.hue_max - self.hue_min)
        saturation = self.saturation_min + random.random() * (self.saturation_max - self.saturation_min)


        img = TF.adjust_brightness(img, brightness)
        img = TF.adjust_hue(img, hue)
        img = TF.adjust_contrast(img, contrast)
        img = TF.adjust_saturation(img, saturation)
        return img, lab

class Rotate:
    def __init__(self, range) -> None:
        assert len(range) == 2
        self.left, self.right = range

    def __call__(self, img: torch.Tensor, lab: torch.Tensor):
        degrees = self.left + random.random() * (self.right - self.left)
        img = TF.rotate(img, degrees)
        lab = TF.rotate(lab, degrees)
        return img, lab

class Affine:
    def __init__(self, translate_x, translate_y, rotate_range) -> None:
        self.translate_x = translate_x
        self.translate_y = translate_y
        assert len(rotate_range) == 2
        self.rot_left, self.rot_right = rotate_range

    def __call__(self, img: torch.Tensor, lab: torch.Tensor):
        dx = -self.translate_x + 2 * random.random() * self.translate_x
        dy = -self.translate_y + 2 * random.random() * self.translate_y

        degrees = self.rot_left + random.random() * (self.rot_right - self.rot_left)

        img = TF.affine(img, angle=degrees, translate=[dx, dy], scale=1, shear=[0])
        lab = TF.affine(lab, angle=degrees, translate=[dx, dy], scale=1, shear=[0])
        return img, lab