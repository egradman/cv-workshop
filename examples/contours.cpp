#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <stdio.h>
#include "libfreenect_cv.h"
#include "glviewcolor.h"


int main(int argc, char **argv)
{
  int thresh = 128;
  int erode = 0;
  int dilate = 0;
  int do_contour = 0;

  IplImage *image_bw = cvCreateImage(SIZE, 8, 1);
  IplImage *image_thresh = cvCreateImage(SIZE, 8, 1);
  IplImage *image_temp = cvCreateImage(SIZE, 8, 1);

  cvNamedWindow("config", CV_WINDOW_AUTOSIZE);
  cvCreateTrackbar("threshold", "config", &thresh, 255, NULL);
  cvCreateTrackbar("erode", "config", &erode, 10, NULL);
  cvCreateTrackbar("dilate", "config", &dilate, 10, NULL);
  cvCreateTrackbar("contour", "config", &do_contour, 1, NULL);

  CvMemStorage *storage = cvCreateMemStorage();

	while (cvWaitKey(10) < 0) {
		IplImage *image = freenect_sync_get_rgb_cv(0);
		if (!image) {
		    printf("Error: Kinect not connected?\n");
		    return -1;
		}
		cvCvtColor(image, image, CV_RGB2BGR);

    cvCvtColor(image, image_bw, CV_RGB2GRAY);
	  cvThreshold(image_bw, image_thresh, thresh, 255, CV_THRESH_BINARY);

    cvErode(image_thresh, image_thresh, NULL, erode);
    cvDilate(image_thresh, image_thresh, NULL, dilate);

    if (do_contour) {
      CvSeq *contours;
      cvCopy(image_thresh, image_temp);
      cvFindContours(image_temp, storage, &contours);
      cvDrawContours(image, contours, CV_RGB(0, 255, 0), CV_RGB(0, 255, 255), 1);
    }

		cvShowImage("RGB", image);
		cvShowImage("BW", image_bw);
		cvShowImage("THRESH", image_thresh);
	}
	return 0;
}
