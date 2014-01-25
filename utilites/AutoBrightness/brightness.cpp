#include <opencv2/opencv.hpp>
#include <iostream>
#include <stdio.h>

using namespace cv;
using namespace std;

void setBrightness (int);
int getIntensity(Mat &);

int main()
{
	char chk;
	system("clear");
	cout<<"\nRun as root. Are you root (y/n): ";
	cin>>chk;
	if(chk=='n'||chk=='N')
	{
		cout<<"\nRun as root.. exiting";
		return 0;
	}	
	Mat img, gray;
	VideoCapture cap(0);
	char ch;
	int I;

	while(true)
	{
		cap>>img;
		cvtColor(img,gray,CV_BGR2GRAY);

		if(!I)
			system("echo 5 > /sys/class/backlight/acpi_video0/brightness");
		I= getIntensity(gray);
		setBrightness(I);	

		ch=waitKey(1);
		if(ch==27)
			break;
	}	
	return 0;
}



int getIntensity(Mat &img)
{
	vector<int> Int;
	unsigned int sum;
	for(int i=0; i<img.rows; i++)
	{
		for(int j=0; j<img.cols; j++)
		{
			Int.push_back( (int)img.at<uchar>(j,i) );
		}	
	}	

	for (int i = 0; i < img.rows; i++)
	{
		for (int j = 0; j < img.cols; j++)
		{
			if(!Int.empty())
			{
				sum+=Int.back();
				Int.pop_back();
			}	
		}
	}
	int avg=sum/(img.rows*img.cols);
	return avg;
}

void setBrightness(int I)
{
	if( (I > 200) && ( I < 255) )
		system("echo 10 > /sys/class/backlight/acpi_video0/brightness");
	if( (I > 120) && ( I < 199) )
		system("echo 7 > /sys/class/backlight/acpi_video0/brightness");
	if( (I > 50) && (I < 119 ) )
		system("echo 4 > /sys/class/backlight/acpi_video0/brightness");
	if( (I > 25) && (I < 49) )
		system("echo 2 > /sys/class/backlight/acpi_video0/brightness");
}

