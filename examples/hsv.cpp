#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <stdio.h>
#include "libfreenect_cv.h"
#include "glviewcolor.h"


int main(int argc, char **argv)
{
  IplImage *image_hsv = cvCreateImage(SIZE, 8, 3);
  IplImage *image_h = cvCreateImage(SIZE, 8, 1);
  IplImage *image_s = cvCreateImage(SIZE, 8, 1);
  IplImage *image_v = cvCreateImage(SIZE, 8, 1);

  cvNamedWindow("config", CV_WINDOW_AUTOSIZE);
  //cvCreateTrackbar("threshold", "config", &thresh, 255, NULL);

	while (cvWaitKey(10) < 0) {
		IplImage *image = freenect_sync_get_rgb_cv(0);
		if (!image) {
		    printf("Error: Kinect not connected?\n");
		    return -1;
		}
		cvCvtColor(image, image, CV_RGB2BGR);
		cvCvtColor(image, image_hsv, CV_BGR2HSV);

    cvSplit(image_hsv, image_h, image_s, image_v, NULL);

		cvShowImage("RGB", image);
		cvShowImage("HSV", image_hsv);
		cvShowImage("H", image_h);
		cvShowImage("S", image_s);
		cvShowImage("V", image_v);
	}
	return 0;
}
