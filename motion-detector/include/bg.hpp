#ifndef BG_HPP
#define BG_HPP

using namespace cv;
using namespace std;

BackgroundSubtractorMOG2 bg;

void background(Mat &img, Mat &fore, Mat &back)
{
  bg.operator()(img, fore);
  bg.getBackgroundImage(back);

  erode(fore, fore, Mat());
  return ;
}

#endif
