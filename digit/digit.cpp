#include <opencv2/opencv.hpp>
#include <stdio.h>
#include <iostream>

using namespace cv;
using namespace std;

Mat edge(Mat &);
Mat contour(Mat &);
void corners(Mat &, Mat &);
void filterCorners(Mat &, int);

int main(int argc, char *argv[])
{
//Variable Declaration
    Mat img, canny, bw;
    char ch;

//Read Image
    if(argc!=2)
    {
        cout<<"\nUsage: ./digit.cpp <Your Image>\n";
        return -1;
    }

    img = imread(argv[1]);
    if(!img.data)
    {
        cout<<"\n Not a Valid Image\n";
        return -1;
    }

//edge
    canny = edge(img);


//contour
    bw = contour(canny);


//corners
    corners(bw, img);

    return 0;
}

Mat edge(Mat &img)
{
    Mat gray, blur, canny;
    cvtColor(img, gray, CV_BGR2GRAY);
    GaussianBlur(gray, blur, Size(3,3), 0);
    Canny(blur, canny, 120, 360, 3);

    return canny;
}

Mat contour(Mat &canny)
{
    Mat bw;
    canny.copyTo(bw);
    vector<vector<Point> > contours;
    vector<Vec4i> h;
    findContours(canny, contours, h, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0,0));
    for(int i=0; i<contours.size(); i++)
    {
        drawContours(bw, contours, i, Scalar(255,255,255), 2, 8, h, 0, Point());
    }

    return bw;
}

void corners(Mat &bw, Mat &img)
{
    Mat dst, dst_norm, dst_norm_scaled;
    dst = Mat::zeros(bw.size(), CV_32FC1);

    int blockSize = 2;
    int apertureSize = 3, thresh=100;
    double k = 0.04;

    cornerHarris(bw, dst, blockSize, apertureSize, k, BORDER_DEFAULT);

    normalize(dst, dst_norm, 0, 255, NORM_MINMAX, CV_32FC1, Mat());
    convertScaleAbs(dst_norm, dst_norm_scaled);

    filterCorners(dst_norm_scaled, thresh);
    namedWindow("Corners", 0);
    imshow("Corners", dst_norm_scaled);
    waitKey();
}

//Function to reduce the number of corners
void filterCorners(Mat &corners, int thresh)
{
    vector<Point> corner;
    for(int i=0; i<corners.rows; i++)
    {
        for(int j=0; j<corners.cols; j++)
        {
            if( (int)corners.at<uchar>(i,j) > 100)
            {
                //circle(corners, Point(j,i), 5, Scalar(0), 1, 8, 0);
                corner.push_back(Point(j,i));
            }
        }
    }

    float dist;
    Point previous = corner.back();
    for(int i=0; i<corner.size(); i++)
    {
        Point current = corner.back();
        dist=sqrt((current.x-previous.x)*(current.x-previous.x)+(current.y-previous.y)*(current.y-previous.y));
        if(dist > 6)
        {
            circle(corners, current, 5, Scalar(255), 1, 8, 0);
        }
        previous = current;
        corner.pop_back();
    }


}
