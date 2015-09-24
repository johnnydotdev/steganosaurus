#define cimg_use_jpeg
#include "CImg.h"
#include <iostream>
#include <string>

using namespace cimg_library;
using namespace std;

void hide_message(CImg<unsigned char> &image, string message) {
    
    return image;
}

/*
 * Helper method to get user input.
 */
string get_user_input() {
}

/*
 * TODO: use user input for this
 */
string get_secret_message() {
    return "Drake looks like a sloth";
}

int main() {
    // Replace this later with command line argument.
    const char *const file_name   = "sloth.jpg";
    const char *const target_name = "target.jpg";
    string secret_message         = get_secret_message();

    // Grab the image inside the current working directory with the specified filename.
    CImg<unsigned char> image(file_name);

    // Hide the message in the image.
    hide_message(image, secret_message);

    // Save the modified image under a target name.
    image.save(target_name);

    return 0;
}
