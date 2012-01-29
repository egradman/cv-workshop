#ifndef FREENECT_CV_H
#define FREENECT_CV_H

#define WIDTH 640
#define HEIGHT 480
#define SIZE (cvSize(WIDTH, HEIGHT))

#include <opencv/cv.h>

	IplImage *freenect_sync_get_depth_cv(int index);
	IplImage *freenect_sync_get_rgb_cv(int index);


#endif
