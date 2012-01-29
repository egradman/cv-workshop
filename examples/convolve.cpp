#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <stdio.h>
#include "libfreenect_cv.h"
#include "glviewcolor.h"

int main(int argc, char **argv)
{
  IplImage *c_im = cvCreateImage(SIZE, 8, 3);
  CvMat *kernel = cvCreateMatHeader(3, 3, CV_32FC1);
  float vals[3][3] = {
    {-1, 2, -1},
    {-1, 2, -1},
    {-1, 2, -1}
  };
  cvSetData(kernel, vals, 3*sizeof(float));

	while (cvWaitKey(10) < 0) {
		IplImage *im = freenect_sync_get_rgb_cv(0);
		cvCvtColor(im, im, CV_RGB2BGR);

    cvFilter2D(im, c_im, kernel);

		cvShowImage("RGB", im);
		cvShowImage("convolved", c_im);
	}
	return 0;
}
