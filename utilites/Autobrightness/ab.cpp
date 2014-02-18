#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#include <iostream>
#include <stdio.h>

using namespace cv;
using namespace std;

void setbrightness(Mat &);
void gesture(Mat &);

CascadeClassifier fist;
Point center, previous;

const int maxm = 1;
int main()
{
  fist.load("fist.xml");
  Mat img, gray;
  VideoCapture cap(0);
  if(!cap.isOpened())
    {
      cout<<"**** Please check your camera *****\n";
      return -1;
    }

  int val=0;
  namedWindow("AutoBrightness", CV_WINDOW_NORMAL);
  createTrackbar("Mode \n 0. Auto-Brightness \n 1. Gesture-Brightness", "AutoBrightness", &val, maxm, NULL);
  char ch;
  
  for(; ;)
    {
      cap>>img;
      cvtColor(img, gray, CV_BGR2GRAY);
      if(!val)
        {
          setbrightness(gray);
          imshow("AutoBrightness", gray);
        }
      else
        {
          gesture(img);
          imshow("AutoBrightness", img);
        }
      
      ch = waitKey(10);
      if(ch == 27)
        break;
    }
}

void setbrightness(Mat &img)
{
  unsigned int total = 0;
  int brightness;
  
  for(int i=0; i<img.cols; i++)
    {
      for(int j=0; j<img.rows; j++)
        {
          total += (int)img.at<uchar>(i,j);
        }
    }
  brightness = total/(img.rows*img.cols);
  
  if(brightness < 30)
    {
      system("echo 3 > /sys/class/backlight/acpi_video0/brightness");
    }
  else if(brightness >=30 && brightness <= 50)
    {
      system("echo 5 > /sys/class/backlight/acpi_video0/brightness");
    }
  else if(brightness >= 50 && brightness <=85)
    {
      system("echo 6 > /sys/class/backlight/acpi_video0/brightness");
    }
  else if(brightness > 85 && brightness <=120)
    {
      system("echo 8 > /sys/class/backlight/acpi_video0/brightness");
    }
  else if(brightness >120 && brightness<180)
    {
      system("echo 10 > /sys/class/backlight/acpi_video0/brightness");
    }
  else if(brightness > 180)
    {
      system("echo 13 > /sys/class/backlight/acpi_video0/brightness");
    }
}

void gesture(Mat &img)
{
  vector<Rect> _fist;

  fist.detectMultiScale(img, _fist, 1.1, 3, 0|CV_HAAR_FIND_BIGGEST_OBJECT, Point(0,0));
  
  for(int i=0 ; i<_fist.size(); i++)
    {
      center = Point(_fist[i].x+_fist[i].width/2, _fist[i].y+_fist[i].height/2);
      rectangle(img, Point(_fist[i].x, _fist[i].y), Point(_fist[i].x+_fist[i].width, _fist[i].y+_fist[i].height), Scalar(255,0,0), 2, 8, 0);
      if(center.x > previous.x+10)
        {
          system("xdotool key XF86MonBrightnessUp");
        }
      else if(previous.x-10 > center.x)
        {
          system("xdotool key XF86MonBrightnessDown");
        }
      
      previous = center;
    }
}
