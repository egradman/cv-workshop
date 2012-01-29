#include <opencv/cxcore.h>
#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <stdio.h>

IplImage *input_im, *output_im;

void func(void)
{
  %s
}

int main(int argc, char **argv)
{
  input_im = cvLoadImage(argv[1]);
  func();
  cvSaveImage(argv[2], output_im);
  exit(0);
}
