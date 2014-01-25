#include <opencv2/opencv.hpp>
#include <iostream>
#include <stdio.h>
#include <cstdlib>

using namespace cv;
using namespace std;

void brightness(Point, Point);
void volume(Point, Point);
void mouse(Point, Point);
void camera(Mat&, Mat& );
void moveup(void);
void movedown(void);
void moveleft(void);
void moveright(void);

const int max_val=1;
CascadeClassifier c1, c2, c3;

vector<Rect> face, hand;
int volum=0,coun=0;
float cposx=683, cposy=384;
char choice;

int main()
{
	int sys=0, mice=0, cam=0;
	char ch;
	Mat img, image;
	namedWindow("SyCon",CV_WINDOW_NORMAL);
	createTrackbar("System", "SyCon", &sys, max_val, NULL);
	createTrackbar("Mouse", "SyCon", &mice, max_val, NULL);
	createTrackbar("Camera", "SyCon", &cam, max_val, NULL);

	c1.load("haar/face.xml");
	c2.load("haar/fist.xml");

	VideoCapture cap(1);
	Point center, previous;

	while(true)
	{
		cap>>img;
		c2.detectMultiScale(img, hand, 1.1, 3, 0|CV_HAAR_FIND_BIGGEST_OBJECT, Point(0,0));
		if(sys==1)
		{
			putText(img, "Brightness/Volume Control Mode", Point(80,80), 1, 1, Scalar(0,0,255), 2, 8, false);
			for(int i=0; i<hand.size(); i++)
			{
				Point center(hand[i].x+hand[i].width*0.5, hand[i].y+hand[i].height*0.5);
				rectangle(img, Point(hand[i].x, hand[i].y), Point(hand[i].x+hand[i].width, hand[i].y+hand[i].height), Scalar(0,0,0), 2, 8, 0);
				brightness(center, previous);
				volume(center, previous);
				line(img, previous, center, Scalar(255,0,0), 2, 8, 0);
				previous=center;				
			}
			cposx=683, cposy=384;
		}
		if(mice==1)
		{
			putText(img, "Mouse Control Mode", Point(80,95), 1, 1, Scalar(0,255,255), 2, 8, false);
			
			for(int i=0; i<hand.size(); i++)
			{
				Point center(hand[i].x+hand[i].width/2, hand[i].y+hand[i].height/2);
				rectangle(img, Point(hand[i].x, hand[i].y), Point(hand[i].x+hand[i].width, hand[i].y+hand[i].height), Scalar(0,0,255), 2, 8, 0);
				mouse(center, previous);
				line(img, previous, center, Scalar(255,0,0), 2, 8, 0);
				previous=center;
			}
		}

		if(cam==1)
		{
			putText(img, "Camera Mode", Point(30,30), 1, 1, Scalar(255,0,255), 2, 8, false);
			cap>>image;
			c1.detectMultiScale(img, face, 1.1, 3, 0|CV_HAAR_FIND_BIGGEST_OBJECT, Point(0,0));
			for(int i=0; i<face.size(); i++)
			{
				rectangle(img, Point(face[i].x, face[i].y), Point(face[i].x+face[i].width, face[i].y+face[i].height), Scalar(0,0,255), 2, 8, 0);
				camera(image, img);
			}
			cposx=683, cposy=384;
		}

		imshow("SyCon",img);
		ch=waitKey(1);
		if(ch==27)
			break;
	}	
	return 0;
	
}
void volume(Point center, Point previous)
{
	string vol;
	stringstream s;
	if(previous.y-5 > center.y)
	{
		if(volum<=100)
		{
			s<<volum;
			vol=s.str();
			string command="amixer sset 'Master' "+ vol +"%";
			const char *cmd=command.c_str();
			system(cmd);
			volum+=5;	
			if(volum>=100)
				volum=100;		
		}	
	}

	if(previous.y+5 < center.y)
	{
		if(volum>=0)
		{
			s<<volum;
			vol=s.str();
			string command="amixer sset 'Master' "+ vol +"%";
			const char *cmd=command.c_str();
			system(cmd);
			volum-=5;
			if(volum<=0)
				volum=0;
		}	
		
	}
}
void brightness(Point center, Point previous)
{
	if(previous.x+10 < center.x)
	{
		system("xdotool key XF86MonBrightnessUp");	
	}

	if(previous.x-10 > center.x)
	{
		system("xdotool key XF86MonBrightnessDown");	
	}	
}
void mouse(Point p1, Point p2)
{
	if(p1.x > p2.x+5)
	{
		moveright();	
	}
	if(p1.x < p2.x-5)
	{	
		moveleft();
	}
	if(p1.y > p2.y+5)
	{
		movedown();
	}
	if(p1.y < p2.y-5)
	{
		moveup();
	}
}
void moveright(void)
{
	cposx+=80;
	string x,y;
	stringstream sx,sy;
	
	sx<<cposx;
	x=sx.str();

	sy<<cposy;
	y=sy.str();
 
	string command = "xdotool mousemove " + x + " " + y;
	const char *cmd=command.c_str();
	system(cmd); 
}
void moveleft(void)
{
	cposx-=80;
	string x,y;
	stringstream sx,sy;
	
	sx<<cposx;
	x=sx.str();

	sy<<cposy;
	y=sy.str();
 
	string command = "xdotool mousemove " + x + " " + y;
	const char *cmd=command.c_str();
	system(cmd); 
}
void moveup(void)
{
	cposy-=80;
	string x,y;
	stringstream sx,sy;
	
	sx<<cposx;
	x=sx.str();

	sy<<cposy;
	y=sy.str();
 
	string command = "xdotool mousemove " + x + " " + y;
	const char *cmd=command.c_str();
	system(cmd); 
}
void movedown(void)
{
	cposy+=80;
	string x,y;
	stringstream sx,sy;
	
	sx<<cposx;
	x=sx.str();

	sy<<cposy;
	y=sy.str();
 
	string command = "xdotool mousemove " + x + " " + y;
	const char *cmd=command.c_str();
	system(cmd); 
}

void camera(Mat& img, Mat &image)
{
	string s,cnt;
	stringstream s1;
	s1<<coun;
	s=s1.str();
	putText(image, "Face Detected.. Should I take the photo??", Point(80,80), 1, 1, Scalar(0,255,0), 2, 8, false);
	putText(image, "Press \"O\" or \"o\" to Capture", Point(120,120), 1, 1, Scalar(0,0,255), 2, 8, false);
	choice=waitKey(1);
	if(choice=='O' || choice=='o')
	{
		putText(image, "Photo Captured.", Point(200,200), 1, 1, Scalar(255,0,0), 2, 8, false);
		string file= "images/Your-Image-"+s+".png";
		const char *cnt=file.c_str();
		imwrite(file, img);
		coun++;
	}
}