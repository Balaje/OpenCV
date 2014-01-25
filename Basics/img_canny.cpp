#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<iostream>
#include<stdio.h>
using namespace cv;

Mat img,gray,dst;
char name[]="Edge Detection",ch;
const int max_thresh=100;
int thresh=0;
const int kernel=3;

void edge(int, void*)
{	cv::namedWindow(name,CV_WINDOW_NORMAL);
	img=cv::imread("1.jpg");
	cv::cvtColor(img,gray,CV_BGR2GRAY);
	cv::createTrackbar("Min Threshold",name,&thresh,max_thresh,NULL);
	while(true) {	
	ch=waitKey(200);
	Canny(gray,dst,thresh,thresh*3,kernel);
	cv::imshow(name,dst);
	if(ch==27)
	{
		return ;
	}
}
	
}

int main(int argc, char* argv[] )
{
	edge(0,argv[1]);
	return 0;
}

