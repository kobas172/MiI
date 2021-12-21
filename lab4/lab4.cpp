
#include <stdio.h>
using namespace std;

#include <iostream>

// OpenCV includes
#include <opencv2/opencv.hpp>
//B
#include "opencv2/core/types_c.h"
#include "opencv2/calib3d/calib3d_c.h"

using namespace cv;

//C
// checkerboards types and number
// The counterclockwise order is required to start searching from the biggest one !!!!
enum ReferenceRegionsTypes { TOP, LEFT, BOTTOM, RIGHT, CHECKERBOARD_NUM };

// checkerboards locations
const int CheckerboardInnerWidth[CHECKERBOARD_NUM] = { 13, 3, 11, 3 }; // number of inner horizontal corners 
const int CheckerboardInnerHeight[CHECKERBOARD_NUM] = { 3, 12, 3, 10 }; // number of inner vertical corners 

const float CHECKERBOARD_FIELD_SIZE = 0.8f; // size of all checkerboard fields
const float CheckerboardsMargin = 1.6f; // outer margin around checkerboard

const Point2f CheckerboardLTCoordinatesWithMargin[CHECKERBOARD_NUM] =
{ // Coordinates of outer left-top corner
    Point2f(4.4f, 0.5f), // TOP
    Point2f(0.5f, 4.8f), // LEFT
    Point2f(5.2f, 16.3f), // BOTTOM
    Point2f(16.3f, 5.6f) // RIGHT
};

// Coordinates of the output region of interest 
const Point2f TemplateLT = Point2f(0.0f, 0.0f); // left-top corner
const Point2f TemplateRB = Point2f(20.0f, 20.0f); // right-bottom corner

int main()
{
    //1
    //A
    Mat srcImage;
    srcImage = imread("E.jpg");
    if (!srcImage.data)
    {
        std::cout << "Blad";
        return 1;

    }

    //D
    Mat greyImage;
    cvtColor(srcImage, greyImage, COLOR_BGR2GRAY);

    //E
    Size patternSize(CheckerboardInnerWidth[TOP], CheckerboardInnerHeight[TOP]);

    //F
    vector<Point2f> srcCorners;

    //G
    bool corner = findChessboardCorners(greyImage, patternSize, srcCorners);

    //H
    if (!corner)
    {
        printf("Nie zaleziono szachownicy!\n");
        waitKey(0);
        return (-1);
    }
    else
    {
        //I
        cornerSubPix(greyImage, srcCorners, Size(5, 5), Size(-1, -1), TermCriteria(TermCriteria::EPS + TermCriteria::COUNT, 30, 0.01));

        //J
        drawChessboardCorners(greyImage, patternSize, srcCorners, true);

        //K
        //namedWindow("Piotr Gorkowski", WINDOW_AUTOSIZE);
        //moveWindow("Piotr Gorkowski", 0, 0);
        //imshow("Piotr Gorkowski", greyImage);

        //L
        //imwrite("184515_E_ChessboardFound.jpg", greyImage);

        //M
        float cx = srcCorners[1].x - srcCorners[0].x;
        float cy = srcCorners[1].y - srcCorners[0].y;
        float powcx = pow(cx, 2);
        float powcy = pow(cy, 2);
        float euklides = sqrt(powcx + powcy);
        printf("\n%f\n", euklides);

        //N
        stringstream numerek;
        for (int i = 0; i < srcCorners.size(); i++)
        {
            numerek << i;
            putText(greyImage, numerek.str(), srcCorners[i], 1, 3, Scalar(255, 0, 0), 1, 8, false);
            numerek.str("");
        }

        //O
        if (srcCorners.front().y > srcCorners.back().y)
            reverse(srcCorners.begin(), srcCorners.end());
        imwrite("184515_E_TopChessboardFound.jpg", greyImage);
    }

    //2
    //A
    float reverseScale = 100.0f;

    //B
    vector<Point2f> templateCorners;

    //C
    Point2f przesuniecie{ 40.0f, 40.0f };
    for (int y = 0; y < patternSize.height; y++)
    {
        for (int x = 0; x < patternSize.width; x++)
        {
            Point2f coord = CheckerboardLTCoordinatesWithMargin[TOP];
            coord.x += CHECKERBOARD_FIELD_SIZE * x;
            coord.y += CHECKERBOARD_FIELD_SIZE * y;
            coord.x *= reverseScale;
            coord.y *= reverseScale;
            coord.x += przesuniecie.x;
            coord.y += przesuniecie.y;
            templateCorners.push_back(coord);
        }
    }

    //D
    //for (int i = 0; i < srcCorners.size(); i++)
    //{
    //    printf("1:%d, 2:%d\n", srcCorners[i].x, templateCorners[i].x);
    //}

    //E
    Mat homography;

    //F
    homography = findHomography(srcCorners, templateCorners, CV_RANSAC);

    //G
    Mat dewarpedImage(srcImage.size(), srcImage.type());

    //H
    warpPerspective(srcImage, dewarpedImage, homography, srcImage.size());

    //I
    imwrite("184515_E_Dewarped.jpg", dewarpedImage);

    //K
    Mat dewarpedROI = dewarpedImage(Rect(reverseScale * TemplateLT, reverseScale * TemplateRB));

    //L
    vector<Point2f> dewarpedCorners;

    //M
    perspectiveTransform(srcCorners, dewarpedCorners, homography);

    //N
    for (int i = 0; i < dewarpedCorners.size(); i++)
        circle(dewarpedROI, dewarpedCorners[i], 5, Scalar(0, 255, 0), 2);

    //O
    imwrite("184515_E_DewarpedROI.jpg", dewarpedROI);

    waitKey();
}