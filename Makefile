all:
	g++ -o cimg_test -O2 -L/usr/X11R6/lib -lm -ljpeg -lpthread -lX11 cimg_test.cpp
