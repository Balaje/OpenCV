#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <stdio.h>

using namespace cv;
using namespace std;

const static int THRESH_VALUE=20;
const static int KERNEL_SIZE=10;
const static int MAX_VAL=255;

Mat debugImage(Mat frame1, Mat frame2)
{
    Mat diffImage, threshImage, dstImage, processImage;

    //Find the absolute difference between the two frames
    absdiff(frame1, frame2, diffImage);

    //Threshold the resulting difference for processing, higher values reduce noises
    threshold(diffImage, threshImage, THRESH_VALUE, MAX_VAL, THRESH_BINARY);

    //Compute the absolute difference, store it in dstImage
    blur(threshImage, dstImage, Size(KERNEL_SIZE, KERNEL_SIZE));
    return dstImage;
}

Mat trackObject(Mat img, Mat src)
{
    //eroding the image to reduce noises
    erode(img, img, Mat());
    erode(img, img, Mat());

    //Find Contours in image
    vector<vector<Point> > contours;
    findContours(img, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);

    //Loop to find the biggest contour; If no contour is found index=-1
    int index=-1, size=0;
    for(int i=0; i<contours.size(); i++)
    {
        if(contours[i].size() > size)
        {
            size = contours[i].size();
            index = i;
        }
    }

    //If contours exist ....
    if(index != -1)
    {
        //Drawing the bounding Rectangle;
        vector<vector<Point> > poly(contours.size());
        vector<Rect> boundRect(contours.size());

        approxPolyDP(Mat(contours[index]), poly[index], 3, true);
        boundRect[index] = boundingRect(Mat(poly[index]));
        if(contours[index].size() > 100)
            rectangle(src, boundRect[index].tl(), boundRect[index].br(), Scalar(0,0,255), 2, 8, 0);
        cout<<"Size = "<<contours[index].size()<<"\n";
    }

    //return the live image with the rectangle
    return src;
}
int main()
{
    Mat frame1, frame2, gray1, gray2, dstImage, processImage;
    VideoCapture cap(1);
    char ch;
    namedWindow("The ball", CV_WINDOW_NORMAL);
    namedWindow("Live Feed", CV_WINDOW_NORMAL);

    while(ch=waitKey(1) != 27)
    {
        //Capture first frame and convert to grayscale
        cap>>frame1;
        cvtColor(frame1, gray1, CV_BGR2GRAY);
        //Capture second frame and also convert to grayscale
        cap>>frame2;
        cvtColor(frame2, gray2, CV_BGR2GRAY);

        dstImage = debugImage(gray1, gray2);

        //Create new image for further processing to track object
        dstImage.copyTo(processImage);
        trackObject(processImage, frame1);

        //Show both the mask and the live image
        imshow("The ball", dstImage);
        imshow("Live Feed", frame1);
    }

    return 0;
    //END
}
