#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#include <iostream>
#include <stdio.h>

using namespace cv;
using namespace std;

Mat img;

vector<Rect> palm;
vector<Rect> hands;

CascadeClassifier Hand, Palm;

int main()
{
		VideoCapture cap(0);
		char ch;
		namedWindow("Face Recognition",CV_WINDOW_NORMAL);
		Palm.load("face.xml");
		Hand.load("hand.xml");
		while(true)
		{	cap>>img;
			Palm.detectMultiScale(img,palm,1.1,3,0|CV_HAAR_FIND_BIGGEST_OBJECT,Size(30,30));
			Hand.detectMultiScale(img,hands,1.1,3,0|CV_HAAR_FIND_BIGGEST_OBJECT,Size(30,30));
			for(int	i=0 ,j=0; i< hands.size() || j < palm.size() ; j++,i++)
			{
				if(hands.size())
					circle(img, Point(hands[i].x+ hands[i].width/2 , hands[i].y+ hands[i].height/2), hands[i].width/2, Scalar(0,255,0), 2, 8 );
				if(palm.size())
					circle(img, Point(palm[j].x+ palm[j].width/2 , palm[j].y+ palm[j].height/2), palm[j].width/2, Scalar(255,0,0), 2, 8 );				
			}	
			imshow("Face Recognition",img);
			ch=waitKey(1);
			if(ch==27)
			{
				break;
			}	
		}
	return 0;
}
