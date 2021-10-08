// lab1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;


int main()
{
    Mat srcImage;

    srcImage = imread("Images/MojeZdjecie.jpg");
    if (!srcImage.data) {
        std::cout << "Nie mozna wczytac obrazu!" << std::endl;
        return 1;
    }

    rectangle(srcImage, Rect(100, 100, 100, 100), Scalar(0, 0, 0), -1, 1, 0);
    imwrite("Images/Nowy.jpg", srcImage);

    namedWindow("Piotr Gorkowski", WINDOW_AUTOSIZE);
    moveWindow("Piotr Gorkowski", 0, 0);

    imshow("Piotr Gorkowski", srcImage);
    waitKey(0);


}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
