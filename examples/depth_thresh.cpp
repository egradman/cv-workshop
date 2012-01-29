#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <stdio.h>
#include "libfreenect_cv.h"
#include "glviewcolor.h"


int main(int argc, char **argv)
{
  int thresh = 128;

  IplImage *im_depth = cvCreateImage(SIZE, 8, 1); 
  IplImage *im_thresh = cvCreateImage(SIZE, 8, 1); 

  cvNamedWindow("config", CV_WINDOW_AUTOSIZE);
  cvCreateTrackbar("thresh", "config", &thresh, 255, NULL);

	while (cvWaitKey(10) < 0) {
		IplImage *depth = freenect_sync_get_depth_cv(0);
		IplImage *im = freenect_sync_get_rgb_cv(0);
    cvConvertScale(depth, im_depth, 255.0/pow(2, 11));
    cvThreshold(im_depth, im_thresh, thresh, 255, CV_THRESH_BINARY);

    cvSet(im, cvScalar(0,0,0), im_thresh);
		cvShowImage("RGB", im);
		cvShowImage("depth", im_depth);
		cvShowImage("GOOD", im_thresh);
	}
	return 0;
}
