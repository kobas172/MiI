
#include <stdio.h>
using namespace std;

#include <iostream>

// OpenCV includes
#include <opencv2/opencv.hpp>
using namespace cv;

Mat grayImage;

int threshold_value = 100;
const int max_value = 255;
Mat binarizedImage;

void Threshold(int pos, void* uderdata)
{
    threshold(grayImage, binarizedImage, threshold_value, max_value, THRESH_BINARY);
    imshow("Binarization", binarizedImage);
}

int main()
{
    Mat srcImage;


    srcImage = imread("Samples/ryba.jpg");
    if (!srcImage.data)
    {
        std::cout << "Blad";
        return 1;

    }
    namedWindow("Piotr Gorkowski", WINDOW_AUTOSIZE);
    moveWindow("Piotr Gorkowski", 0, 0);
    imshow("Piotr Gorkowski", srcImage);

    cvtColor(srcImage, grayImage, COLOR_BGR2GRAY);
    namedWindow("Gray image", WINDOW_AUTOSIZE);
    moveWindow("Gray image", 300, 0);
    imshow("Gray image", grayImage);
    imwrite("Samples\\Gray.jpg", grayImage);

    Mat resizedImage(Size(100, 100), srcImage.type());
    resize(srcImage, resizedImage, Size(100, 100));
    namedWindow("Resized image", WINDOW_AUTOSIZE);
    moveWindow("Resized image", 600, 0);
    imshow("Resized image", resizedImage);

    Mat blurImage;
    blur(srcImage, blurImage, Size(5, 5));
    namedWindow("Blured image", WINDOW_AUTOSIZE);
    moveWindow("Blured image", 900, 0);
    imshow("Blured image", blurImage);

    Mat cannyImage;
    Canny(srcImage, cannyImage, 15, 85);
    namedWindow("Canny edges", WINDOW_AUTOSIZE);
    moveWindow("Canny edges", 1200, 0);
    imshow("Canny edges", cannyImage);

    Mat LaplacianImage;
    Laplacian(grayImage, LaplacianImage, CV_16S, 3);
    Mat scaledLaplacianImage;
    convertScaleAbs(LaplacianImage, scaledLaplacianImage);
    namedWindow("Laplacian image", WINDOW_AUTOSIZE);
    moveWindow("Laplacian image", 1500, 0);
    imshow("Laplacian image", scaledLaplacianImage);

    Mat brightImage;
    srcImage.copyTo(brightImage);
    for (int i = 0; i < brightImage.cols; i++)
    {
        for (int j = 0; j < brightImage.rows; j++)
        {
            Vec3b pixelColor;
            pixelColor = brightImage.at<Vec3b>(i, j);
            if (pixelColor[0] > 155)
                pixelColor[0] = 50;
            else
                pixelColor[0] += 100;
            if (pixelColor[1] > 155)
                pixelColor[1] = 50;
            else
                pixelColor[1] += 100;
            if (pixelColor[2] > 155)
                pixelColor[2] = 50;
            else
                pixelColor[2] += 100;
            brightImage.at<Vec3b>(i, j) = pixelColor;
        }
    }
    namedWindow("Bright Image", WINDOW_AUTOSIZE);
    moveWindow("Bright Image", 900, 300);
    imshow("Bright Image", brightImage);

    namedWindow("Binarization", WINDOW_AUTOSIZE);
    moveWindow("Binarization", 0, 600);
    createTrackbar("Threshold value", "Binarization", &threshold_value, max_value, Threshold);

    const int histSize = 256;
    const int hist_w = 256;
    const int hist_h = 256;
    float range[2] = { 0, 256 };
    const float* histRange = range;
    Mat histImageGray(Size(hist_w, hist_h), CV_8UC3, Scalar(0, 0, 0));
    Mat histogramGray;
    calcHist(&grayImage, 1, 0, Mat(), histogramGray, 1, &histSize, &histRange);
    normalize(histogramGray, histogramGray, range[0], range[1], NORM_MINMAX);
    for (int i = 0; i < 256; i++)
        line(histImageGray, Point(i, hist_h), Point(i, hist_h - histogramGray.at<float>(i)), Scalar(255, 0, 0), 2);
    namedWindow("Histogram Gray");
    moveWindow("Histogram Gray", 0, 300);
    imshow("Histogram Gray", histImageGray);
    Mat equalizedHistImage;
    equalizeHist(grayImage, equalizedHistImage);
    namedWindow("Equalized Histogram");
    moveWindow("Equalized Histogram", 300, 300);
    imshow("Equalized Histogram", equalizedHistImage);
    Mat hist2(Size(hist_w, hist_h), CV_8UC3, Scalar(0, 0, 0));
    Mat histogram2;
    calcHist(&equalizedHistImage, 1, 0, Mat(), histogram2, 1, &histSize, &histRange);
    normalize(histogram2, histogram2, range[0], range[1], NORM_MINMAX);
    for (int i = 0; i < 256; i++)
        line(hist2, Point(i, hist_h), Point(i, hist_h - histogram2.at<float>(i)), Scalar(255, 0, 0), 1);
    namedWindow("Histogram Equalized");
    moveWindow("Histogram Equalized", 600, 300);
    imshow("Histogram Equalized", hist2);

    waitKey(0);
    
    namedWindow("Src video");
    namedWindow("Dst video");
    moveWindow("Src video", 300, 600);
    moveWindow("Dst video", 900, 600);
    Mat srcFrame, dstFrame;
    VideoCapture capture("Samples\\Dino.avi");
    capture >> srcFrame;
    VideoWriter writer("Samples\\Dino2.avi", -1, 25, srcFrame.size());
    while (waitKey(25) != 27 && !srcFrame.empty())
    {
        blur(srcFrame, dstFrame, Size(5, 5));
        writer << dstFrame;
        imshow("Src video", srcFrame);
        capture >> srcFrame;
        imshow("Dst video", dstFrame);
    }
}
