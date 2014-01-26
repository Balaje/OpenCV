#include <opencv2/opencv.hpp>
#include <stdio.h>
#include <iostream>

using namespace cv;
using namespace std;

int main(int argc, char *argv[])
{
//Variable Declaration	
	Mat img, canny, eroded;
	namedWindow("Digit Model", CV_WINDOW_NORMAL);

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
	Mat gray, blur;
	cvtColor(img, gray, CV_BGR2GRAY);
	GaussianBlur(gray, blur, Size(3,3), 0);
	Canny(blur, canny, 120, 360, 3);

//contour
	Mat bw;
	canny.copyTo(bw);
	vector<vector<Point> > contours;
	vector<Vec4i> h;
	findContours(canny, contours, h, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0,0));
	for(int i=0; i<contours.size(); i++)
	{
		drawContours(bw, contours, i, Scalar(255,255,255), -1, 8, h, 0, Point());
	}

//skeletonization
	Mat  skel = Mat::zeros(img.size(), CV_8UC1);
	Mat temp(img.size(), CV_8UC1);
	Mat element = getStructuringElement(MORPH_CROSS, Size(3, 3));

	threshold(bw, bw, 127, 255, cv::THRESH_BINARY);

	bool done;
	do
	{
  		morphologyEx(bw, temp, cv::MORPH_OPEN, element);
  		bitwise_not(temp, temp);
  		bitwise_and(bw, temp, temp);
  		bitwise_or(skel, temp, skel);
  		erode(bw, bw, element);
 	
 		double max;
  		minMaxLoc(bw, 0, &max);
  		done = (max == 0);
	}while(!done);

//graph model
		

	imshow("Digit Model", skel);
	waitKey();
}