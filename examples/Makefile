CC=g++
CPPFLAGS=-I/usr/local/include/libfreenect
LDFLAGS=-L/usr/local/lib -lcv -lcvaux -lhighgui -lfreenect_sync

TARGETS=cvdemo bw rgb contours hsv hue depth_thresh background perspective convolve

all: $(TARGETS)

cvdemo: cvdemo.o libfreenect_cv.o
bw: bw.o libfreenect_cv.o
rgb: rgb.o libfreenect_cv.o
contours: contours.o libfreenect_cv.o
hsv: hsv.o libfreenect_cv.o
hue: hue.o libfreenect_cv.o
depth_thresh: depth_thresh.o libfreenect_cv.o
background: background.o libfreenect_cv.o
perspective: perspective.o libfreenect_cv.o
convolve: convolve.o libfreenect_cv.o

clean:
	rm -f *.o $(TARGETS)
