#include <opencv2/opencv.hpp>
#include <stdio.h>
#include <iostream>

using namespace cv;
using namespace std;

int find(vector<vector<Point> >);
void sixornine(Mat &, vector<Point2f>);
int main(int argc, char *argv[])
{
    Mat img, gray, edge, contour;
    if(argc!= 2)
    {
        cout<<"\nUsage ./closed <Your Image>";
        return -1;
    }
    img = imread(argv[1]);
    /*if(!img.data)
    {
        cout<<"\nInvalid Image";
            return -1;
            }*/

    //edge
    Mat blur;
    cvtColor(img, gray, CV_BGR2GRAY);
    GaussianBlur(gray, blur, Size(3,3), 0);
    Canny(blur, edge, 120, 360, 3);

    //contours
    Mat bw;
    vector<vector<Point> > contours;
    vector<Vec4i> h;
    findContours(edge, contours, h, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0,0));

    vector<vector<Point> > poly(contours.size());
    vector<Point2f> center (contours.size());
    vector<float> radius (contours.size());

    int s= find(contours);

    int count=0;
    Point previous = center.back();
    for(int i=0; i<contours.size(); i++)
    {
        if(s!=i)
        {
            approxPolyDP(Mat(contours[i]), poly[i] ,3, true);
            minEnclosingCircle((Mat)poly[i], center[i], radius[i]);
            circle(img, center[i], radius[i], Scalar(255,0,0), 1, 8, 0);
            count++;
            int dist = sqrt((previous.x-center[i].x)*(previous.x-center[i].x)+(previous.y-center[i].y)*(previous.y-center[i].y));
            if(dist < 10)
            {
                count--;
                center.pop_back();
            }
            previous = center[i];
            center.pop_back();
        }
    }
    printf("%d\n", count);
    if(count == 3)
    {
        printf("Possible digit is 8\n");
    }
    if(count == 2)
    {
        printf("Possible digits are 6 or 9\n");
        sixornine(img, center);
    }
    namedWindow("Your Digit", CV_WINDOW_NORMAL);
    imshow("Your Digit", img);
    waitKey();
}
void sixornine(Mat &img, vector<Point2f> centers)
{
    printf("Computing..... ");

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
