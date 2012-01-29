#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <stdio.h>
#include "libfreenect_cv.h"
#include "glviewcolor.h"


int main(int argc, char **argv)
{
  int h_center = 128;
  int h_radius = 10;
  int s_center = 128;
  int s_radius = 10;
  int v_center = 128;
  int v_radius = 10;

  IplImage *im_hsv = cvCreateImage(SIZE, 8, 3);
  IplImage *im_good = cvCreateImage(SIZE, 8, 1);

  cvNamedWindow("config", CV_WINDOW_AUTOSIZE);
  cvCreateTrackbar("h_center", "config", &h_center, 255, NULL);
  cvCreateTrackbar("h_radius", "config", &h_radius, 64, NULL);
  cvCreateTrackbar("s_center", "config", &s_center, 255, NULL);
  cvCreateTrackbar("s_radius", "config", &s_radius, 64, NULL);
  cvCreateTrackbar("v_center", "config", &v_center, 255, NULL);
  cvCreateTrackbar("v_radius", "config", &v_radius, 64, NULL);

	while (cvWaitKey(10) < 0) {
		IplImage *im = freenect_sync_get_rgb_cv(0);
		if (!im) {
		    printf("Error: Kinect not connected?\n");
		    return -1;
		}
		cvCvtColor(im, im, CV_RGB2BGR);
		cvCvtColor(im, im_hsv, CV_BGR2HSV);


    cvZero(im_good);
    for (int row=0; row<HEIGHT; row++) {
      for (int col=0; col<WIDTH; col++) {
        CvScalar hsv = cvGet2D(im_hsv, row, col);
        int h = hsv.val[0];
        int s = hsv.val[1];
        int v = hsv.val[2];
        if (
               (h_center-h_radius<h && h<=h_center+h_radius)
            && (s_center-s_radius<s && s<=s_center+s_radius)
            && (v_center-v_radius<v && v<=v_center+v_radius))
          cvSet2D(im_good, row, col, cvScalar(255));
      }
    }

		cvShowImage("RGB", im);
		cvShowImage("GOOD", im_good);
	}
	return 0;
}
