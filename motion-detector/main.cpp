#include <opencv2/opencv.hpp>
#include <stdio.h>
#include <iostream>
#include "include/bg.hpp"
 
int findBiggestContour(vector<vector<Point> > );
int main()
{
  Mat img, back, fore;
  VideoCapture cap(1);
  namedWindow("Secure++ | Fore", CV_WINDOW_AUTOSIZE);
  namedWindow("Secure++ | Back", CV_WINDOW_AUTOSIZE);
  namedWindow("Secure++ | Original Image", CV_WINDOW_AUTOSIZE);

  vector<vector<Point> > contours;
  vector<Vec4i> hierarchy;

  char ch;
  int s;
  for(; ;)
    {
      cap>>img;
      background(img, fore, back);

      findContours(fore, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_NONE, Point());
      
      vector<vector<Point> > poly(contours.size());
      vector<Rect> boundRect(contours.size());

      s=findBiggestContour(contours);
      if(s!=-1)
        {
          approxPolyDP(Mat(contours[s]), poly[s], 3, true);
          boundRect[s]=boundingRect(Mat(poly[s]));
          rectangle(img, boundRect[s].tl(), boundRect[s].br(), Scalar(0,255,0), 2, 8, 0);
        }
           
      imshow("Secure++ | Original Image", img);
      imshow("Secure++ | Back", back);
      imshow("Secure++ | Fore", fore);
      ch=waitKey(1);
      if(ch==27)
        break;
      
    }
}
int findBiggestContour(vector<vector<Point> > contours)
{
  int index=-1, size=0;
  for(int i=0; i<contours.size(); i++)
    {
      if(contours[i].size() > size)
        {
          index = i;
          size = contours[i].size();
        }
    }
  return index;
}
