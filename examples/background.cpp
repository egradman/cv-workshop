#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <stdio.h>
#include "libfreenect_cv.h"
#include "glviewcolor.h"

int main(int argc, char **argv)
{
  IplImage *bg_im = cvCreateImage(SIZE, 8, 3);
  IplImage *mask_im = cvCreateImage(SIZE, 8, 1);
  IplImage *sub_im = cvCreateImage(SIZE, 8, 3);

	while (true) {
    int key = cvWaitKey(10);
		IplImage *im = freenect_sync_get_rgb_cv(0);
		if (!im) {
		    printf("Error: Kinect not connected?\n");
		    return -1;
		}
		cvCvtColor(im, im, CV_RGB2BGR);

    cvAbsDiff(im, bg_im, sub_im);

    cvCvtColor(sub_im, mask_im, CV_BGR2GRAY);
    cvCmpS(mask_im, 32, mask_im, CV_CMP_LT);

    cvCopy(im, sub_im);
    cvSet(sub_im, cvScalar(0,0,0), mask_im);

		cvShowImage("RGB", im);
		cvShowImage("BACKGROUND", bg_im);
		cvShowImage("MASK", mask_im);
		cvShowImage("SUB", sub_im);

    if (key > 0) {
      if (key == 32) {
        cvCopy(im, bg_im);
      } else {
        break;
      }
    }
	}
	return 0;
}
