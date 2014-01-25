#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<stdio.h>
#include<iostream>

using namespace cv;

Mat img,gray,res;
char str[]=" \n0.Color \n1.Grayscale \nPress 'c/C' to capture \n Press ESC to exit",k;
const int max_opt=1;
const int min_opt=0;
int opt=0;
char name[20];
int main() 
{
	VideoCapture cap=VideoCapture(1);
	cap>>img;
	cv::namedWindow("Webcam PhotoCapture");
	createTrackbar(str,"Webcam PhotoCapture",&opt,max_opt,NULL);
	while(true)
	{
		cap>>img;
		k=waitKey(100);
		if(opt==0&&k!=27)
		{	
			imshow("Webcam PhotoCapture",img);
			if(k==99||k==67)
				cv::imwrite("~Your Image~.jpg",img);
		}
		else if(opt==1&&k!=27)
		{
			cv::cvtColor(img,gray,CV_RGB2GRAY);
			imshow("Webcam PhotoCapture",gray);
			if(k==99||k==67)
				cv::imwrite("~Your Gray Image~.jpg",gray);		
		}
		else if(k==27)
			break;
	}
}
