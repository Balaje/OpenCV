#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<stdio.h>
using namespace cv;
Mat img1,img2,img3,res;
int main(int argc, char *argv[])
{	char ch;
	img1=cv::imread(argv[1]);
	img2=cv::imread(argv[2]);
	cv::addWeighted(img1,0.5,img2,1.0,0.,res);
	cv::namedWindow("Result",CV_WINDOW_NORMAL);
	while(true)
	{
		ch=waitKey(30);
		cv::imshow("Result",res);
		if(ch==27)
			break;
	}
	cv::imwrite("OP.jpg",res);
	return 0;
}
