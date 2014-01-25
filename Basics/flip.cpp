#include<stdio.h>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/core/core.hpp>

using namespace cv;
Mat image,res;
int main(int argc, char *argv[])
{
	printf("\nSize: %d , %d \n",image.size().height,image.size().width);
	image=cv::imread(argv[1]);

	if(!image.data)
	{
		printf("\nImage not found or image corrupted :(");
		exit(0);
	}	
	cv::namedWindow("Original img");
	cv::imshow("Original img",image);
	
	cv::flip(image,res,1);
	cv::namedWindow("Result");
	cv::imshow("Result",res);
	cv::waitKey(0);

	cv::imwrite("output.jpg",res);
}	
