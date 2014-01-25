#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/objdetect/objdetect.hpp>
#include<cstdlib>
#include<stdio.h>
#include<time.h>

using namespace cv;
using namespace std;

Mat img;
char name[]="Live-Gesture-Recognition",ch;
CascadeClassifier cascade;
std::vector<Rect> hand;
int flag=0,ctr=0;
int length;
Point win_cen,cen;

int main()
{	
	cv::VideoCapture cap(0);
	cap>>img;
	cv::namedWindow(name,CV_WINDOW_NORMAL);
	cascade.load("fist.xml");
	while(true)
	{	
		cap>>img;
		Point win_cen(img.rows*0.5, img.cols*0.5);
		ellipse(img,win_cen,Size(100,100),0,0,360,Scalar(0,255,0),4,8,0);
		cascade.detectMultiScale(img,hand,1.1,2,0|CV_HAAR_SCALE_IMAGE,Size(20,20));
		if(hand.size())
		{	
			for(int i = 0; i < hand.size(); i++ )
	        	{	if(!ctr)
	        		{	Point initial(hand[i].x+hand[i].width*0.5, hand[i].y+hand[i].height*0.5);
					ellipse(img,initial,Size(hand[i].width*0.5, hand[i].height*0.5),0,0,360,Scalar(0,255,0),4,8,0);
					system("echo \"pause\" | telnet localhost 1234");
					flag=1;
					ctr=1;
				}					
	        	}
		}

		else
		{	if(flag==0 || ctr==1)	
			{	system("echo \"play\" | telnet localhost 1234");
				flag=0;	ctr=0;
			}	
		}	
		ch=waitKey(1);
		cv::imshow(name,img);
		if(ch==27)
		    break;
	}	 	
}
