#include "ImageMagick-6.9.2-3/Magick++/lib/Magick++.h"
#include <iostream>

using namespace std;
using namespace Magick;

int main() {
    Image image;

    try {
        image.read("sloth.jpg");

        image.crop( Geometry(100, 100, 100, 100) );

        image.write("drake.jpg");
    } catch (Exception &error_ ) {
        cout << "Caught exception: " << error_.what() << endl;
        return 1;
    }

    return 0;
}
