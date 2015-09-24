#define cimg_use_jpeg
#include "CImg.h"
#include <iostream>

using namespace cimg_library;
using namespace std;

int main() {
    CImg<unsigned char> image("sloth.jpg");
    const unsigned char color[] = { 255, 255, 255 };
    image.draw_point(50, 50, color);
    image.save("drake.jpg");

    return 0;
}
