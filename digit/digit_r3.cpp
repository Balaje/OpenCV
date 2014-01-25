#include <opencv2/opencv.hpp>
#include <stdio.h>
#include <iostream>

using namespace cv;
using namespace std;

Mat edge(Mat &);
Mat findContour(Mat &);
Mat corners(Mat &);


int main(int argc, char *argv[])
{
	Mat img, canny, contour, graph;
	Point x, y;
	namedWindow("Model",0);
	
	if(argc != 2)
	{
		cout<<"\nUsage ./digit_r3 <Your Image>";
		return -1;
	}

	img = imread(argv[1]);

	canny = edge(img);
	contour = findContour(canny);
	graph = corners(contour);

	imshow("Model", graph);
	waitKey();
}

int findBiggestContour(vector<vector<Point> >contours)
{
	int index=-1;
	int size=0;
	for(int i=0; i<contours.size(); i++)
	{
		if(size < contours[i].size())
		{
			size=contours[i].size();
			index=i;
		}	
	}	
	return index;
}

Mat edge(Mat &img)
{
	Mat gray, canny, blur;

	cvtColor(img, gray, CV_BGR2GRAY);	
	int thresh = 120, aperture = 3;
	GaussianBlur(gray, blur, Size(3,3), 0);
	Canny(blur, canny, thresh, thresh*3, aperture);

	return canny;
}

Mat findContour(Mat &canny)
{
	vector<vector<Point> > contours;
	vector<Vec4i> h;

	findContours(canny, contours, h, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0,0));

	int s = findBiggestContour(contours);
	vector<vector<Point> > poly(contours.size());
	vector<Rect> boundRect(contours.size());

	Mat boundaries = Mat::zeros(canny.size(), CV_8UC1);
	Mat outline = Mat::zeros(canny.size(), CV_8UC1);
	Mat pts = Mat::zeros(canny.size(), CV_8UC1);


	if(s!=-1)
	{
		approxPolyDP( Mat(contours[s]), poly[s], 3, true );
		boundRect[s] = boundingRect( Mat(poly[s]) );
		rectangle(boundaries, boundRect[s].tl(), boundRect[s].br(), Scalar(255,255,255), 2, 8, 0);
		drawContours(outline, contours, s, Scalar(255,255,255), 2, 8, h, 0, Point());
	}

	return outline;
}	

Mat corners(Mat &outline)
{
	Mat dst, dst_norm, dst_norm_scaled;
	int thresh = 110;

	cornerHarris( outline, dst, 2, 3, 0.04, BORDER_DEFAULT );

  	normalize( dst, dst_norm, 0, 255, NORM_MINMAX, CV_32FC1, Mat() );
	convertScaleAbs( dst_norm, dst_norm_scaled );

  	for( int j = 0; j < dst_norm.rows ; j++ )
    { 
    	for( int i = 0; i < dst_norm.cols; i++ )
        {
           if( (int) dst_norm.at<float>(j,i) > thresh )
            {
               circle( dst, Point( i, j ), 5,  Scalar(255,255,255), 2, 8, 0 );
            }
       }
    }

    return dst;
}




