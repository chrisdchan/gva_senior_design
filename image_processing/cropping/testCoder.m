function newImg = testCoder(inputImage)
    img = imread(inputImage);
    img = rgb2gray(img);
    img = imgaussfilt(img, 3);
    newImg = img;
end