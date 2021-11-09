// lab1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <opencv2/opencv.hpp>
#include <fstream>
#include <string>

using namespace cv;
using namespace std;


int main()
{
    Mat srcImage;
    string line;
    string lines[9];
    int i = 0;

    //Rysowanie kwadratu na kazdym zdjeciu
    //char letter = 'A';

    //for (int i = 0; i < 10; i++)
    //{
    //    std::string dir = "Images\\";
    //    std::string dirOut = dir;
    //    dir += letter;
    //    dir += ".jpg";
    //    dirOut += letter;
    //    dirOut += "_OUT.jpg";
    //    srcImage = imread(dir);
    //    if (!srcImage.data) {
    //        std::cout << "Nie mozna wczytac obrazu!" << std::endl;
    //        return 1;
    //    }
    //    rectangle(srcImage, Rect(100, 100, 100, 100), Scalar(0, 0, 0), -1, 1, 0);
    //    imwrite(dirOut, srcImage);
    //    letter = (int)letter + 1;
    //    srcImage.release();
    //}

    ifstream myfile("184515.csv");
    if (myfile.is_open())
    {
        while (getline(myfile, line))
        {
            if (i > 0 && i < 10)
            {
                lines[i - 1] = line;
            }
            i++;
        }
        myfile.close();
    }

    char letter = 'A';
    char* first = NULL;
    char* second = NULL;
    for (int i = 0; i < 9; i++)
    {
        string dir = "Images\\";
        string dirOut = dir;
        dir += letter;
        dir += ".jpg";
        dirOut += letter;
        dirOut += "_OUT.jpg";

        srcImage = imread(dir);
        if (!srcImage.data) {
            std::cout << "Nie mozna wczytac obrazu!" << std::endl;
            return 1;
        }

        int n = lines[i].length();
        char linesChar[1000];
        strcpy(linesChar, lines[i].c_str());

        first = strtok(linesChar, ";");
        while (true) {
            first = strtok(NULL, ";");
            second = strtok(NULL, ";");
            if (first == NULL && second == NULL)
            {
                break;
            }
            circle(srcImage, Point(atof(first), atof(second)), 10, Scalar(0, 255, 255), -1);
        }

        imwrite(dirOut, srcImage);
        letter++;
        srcImage.release();
    }

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
