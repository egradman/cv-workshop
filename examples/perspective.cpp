#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <stdio.h>
#include "libfreenect_cv.h"
#include "glviewcolor.h"

CvPoint2D32f corners[4];
CvPoint2D32f dst[4] = {{0,0},{WIDTH,0},{WIDTH,HEIGHT},{0,HEIGHT}};
int n=0;
CvMat *pmat = cvCreateMat(3, 3, CV_64F);

void onMouse(int event, int x, int y, int flags, void *param)
{
  if (event == CV_EVENT_LBUTTONDOWN && n < 4) {
    printf("got corner %d at %d,%d\n", n, x, y);
    corners[n].x = x;
    corners[n].y = y;
    n += 1;
  }
  if (n == 4) {
    cvGetPerspectiveTransform(corners, dst, pmat);
  }
}

int main(int argc, char **argv)
{
  cvNamedWindow("RGB");
  cvSetMouseCallback("RGB", onMouse);

  IplImage *p_im = cvCreateImage(SIZE, 8, 3);


	while (cvWaitKey(10) < 0) {
		IplImage *im = freenect_sync_get_rgb_cv(0);
		cvCvtColor(im, im, CV_RGB2BGR);

    for (int i=0; i<n; i++) {
      cvCircle(im, cvPoint(corners[i].x, corners[i].y), 3, CV_RGB(0, 255, 0));
    }
    if (n == 4) {
      cvWarpPerspective(im, p_im, pmat);
    }

		cvShowImage("RGB", im);
		cvShowImage("PERSPECTIVE", p_im);
	}
	return 0;
}
