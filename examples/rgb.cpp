#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <stdio.h>
#include "libfreenect_cv.h"
#include "glviewcolor.h"

int main(int argc, char **argv)
{
  IplImage *image_red =   cvCreateImage(SIZE, 8, 1);
  IplImage *image_green = cvCreateImage(SIZE, 8, 1);
  IplImage *image_blue =  cvCreateImage(SIZE, 8, 1);

  IplImage *image_red2 = cvCreateImage(SIZE, 8, 3);
  IplImage *image_green2 = cvCreateImage(SIZE, 8, 3);
  IplImage *image_blue2 = cvCreateImage(SIZE, 8, 3);

	while (cvWaitKey(10) < 0) {
		IplImage *image = freenect_sync_get_rgb_cv(0);
		if (!image) {
		    printf("Error: Kinect not connected?\n");
		    return -1;
		}
		cvCvtColor(image, image, CV_RGB2BGR);

    CvSize size = cvSize(image->width, image->height);

    cvZero(image_red2);
    cvZero(image_green2);
    cvZero(image_blue2);

    cvSplit(image, image_red, image_green, image_blue, NULL);

    cvSetImageCOI(image_red2, 1);
    cvCopy(image_red, image_red2);
    cvSetImageCOI(image_red2, 0);

    cvSetImageCOI(image_green2, 2);
    cvCopy(image_green, image_green2);
    cvSetImageCOI(image_green2, 0);

    cvSetImageCOI(image_blue2, 3);
    cvCopy(image_blue, image_blue2);
    cvSetImageCOI(image_blue2, 0);

		cvShowImage("RGB", image);
		cvShowImage("R", image_red2);
		cvShowImage("G", image_green2);
		cvShowImage("B", image_blue2);
	}
	return 0;
}
