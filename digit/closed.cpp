#include <opencv2/opencv.hpp>
#include <stdio.h>
#include <iostream>
#include <stdlib.h>

using namespace cv;
using namespace std;

int find(vector<vector<Point> >);

int main(int argc, char *argv[])
{
    Mat img, gray, edge, contour;
    if(argc!= 2)
    {
        cout<<"\nUsage ./closed <Your Image>";
        return -1;
    }
    img = imread(argv[1]);
    if(!img.data)
    {
        cout<<"\nInvalid Image";
            return -1;
    }

    //edge (Canny edge detection)
    Mat blur;
    cvtColor(img, gray, CV_BGR2GRAY);
    GaussianBlur(gray, blur, Size(3,3), 0);
    Canny(blur, edge, 120, 360, 3);

    //contours
    vector<vector<Point> > contours;
    vector<Vec4i> h;
    findContours(edge, contours, h, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0,0));
    vector<Point> c;

    vector<vector<Point> > poly(contours.size());
    vector<Point2f> center (contours.size());
    vector<float> radius (contours.size());

    int s= find(contours);   //finds the biggest contour in the image

//Part that calculates the number of closed curves
    int count=0;
    Point previous = center.back();
    int i=0;
    for(i=0; i<contours.size(); i++)
    {
        if(s!=i)
        {
         approxPolyDP(Mat(contours[i]), poly[i] ,3, true);
         minEnclosingCircle((Mat)poly[i], center[i], radius[i]);
         count++;//increases contour count by one
         int dist = sqrt((previous.x-center[i].x)*(previous.x-center[i].x)+(previous.y-center[i].y)*(previous.y-center[i].y));
         if(dist < 10)
         {
             count--;   //if two contours are very close to each other, the contour count is reduced by 1
             center.pop_back();
         }
         {
             circle(img, center[i], radius[i], Scalar(255,255,0), 3, 8, 0);
             c.push_back(center[i]);   //contains the center of the contours, used to distinguish between 6/9
         }
         previous = center[i];
         center.pop_back();
        }
    }

    //predicts the result by comparing the number of closed curves
    if(count == 3)
    {
        printf("Number of closed curves = %d\n",count);
        printf("The digit detected is 8\n");
    }
    if(count == 2)
    {
        printf("Number of closed curves = %d\n",count);

        if(c[0].y > c[1].y)
            printf("The digit detected is 9.\n");
        else if(c[0].y < c[1].y)
            printf("The digit detected is 6.\n");
    }
    if(count==1)
    {
        printf("Number of closed curves = %d\n",count);
        printf("The digit detected is 0.\n");
    }
    namedWindow("Your Digit", CV_WINDOW_NORMAL);
    imshow("Your Digit", img);
    waitKey();
}

int find(vector<vector<Point> > contours)
{
    int index=-1, size=0;
    for(int i=0 ;i<contours.size(); i++)
    {
        if(size < contours[i].size())
        {
            size = contours[i].size();
            index = i;
        }
    }
    return index;
}
