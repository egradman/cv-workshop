#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <stdio.h>
#include "libfreenect_cv.h"
#include "glviewcolor.h"


int main(int argc, char **argv)
{
  IplImage *image_bw = cvCreateImage(
    SIZE,
    8, 1
  );
	while (cvWaitKey(10) < 0) {
		IplImage *image = freenect_sync_get_rgb_cv(0);
		if (!image) {
		    printf("Error: Kinect not connected?\n");
		    return -1;
		}
		cvCvtColor(image, image, CV_RGB2BGR);
    cvCvtColor(image, image_bw, CV_RGB2GRAY);
		
		cvShowImage("RGB", image);
		cvShowImage("BW", image_bw);
	}
	return 0;
}
