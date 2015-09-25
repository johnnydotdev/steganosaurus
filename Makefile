all:
	g++ -o steganosaurus -O2 -L/usr/X11R6/lib -lm -ljpeg -lpthread -lX11 src/steganosaurus.cpp
