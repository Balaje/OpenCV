#include<stdio.h>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
void thresh(int, void*);

using namespace cv;
const int max_val=255;
int thresh_val=0;
int thresh_type=3;
const int max_bin_val=255;
const int max_type=4;
Mat img,gray,res;

int main()
{
	thresh(0,0);
	return 0;
}

void thresh(int ,void*)
{	char k;	
	VideoCapture cap= VideoCapture(0);
	cap>>img;
	cv::namedWindow("Video Thresh");
	cv::createTrackbar("Value","Video Thresh",&thresh_val,max_val,NULL);
	cv::createTrackbar("Type","Video Thresh",&thresh_type,max_type,NULL);
	while(true)
	{	printf("\nPRESS ESC TO EXIT");
		cap>>img;
		cv::cvtColor(img,gray,CV_RGB2GRAY);
		threshold(gray,res,thresh_val,max_bin_val,thresh_type);
		cv::imshow("Video Thresh",res);
		k=waitKey(100);
		if(k==27)
		{
			printf("\nBye");
			break;
		}
	}
}

