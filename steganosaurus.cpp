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
 * TODO: Replace this with stuff to get the file_name from user input.
 */
string get_file_name() {
    return "sloth.jpg";
}

/*
 * TODO: Replace this with stuff to get the target_name from user input.
 */
string get_target_name() {
    return "drake.jpg";
}

string get_secrete_message() {
    return "Drake looks like a sloth";
}

int main() {
    // Replace this later with command line argument.
    string file_name   = get_file_name();
    string target_name = get_target_name();
    string secret_message = get_secrete_message();

    // Grab the image inside the current working directory with the specified filename.
    CImg<unsigned char> image(file_name);

    // Hide the message in the image.
    hide_message(image, secret_message);

    // Save the modified image under a target name.
    image.save(target_name);

    return 0;
}
