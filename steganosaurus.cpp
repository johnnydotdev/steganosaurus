#include "steganosaurus.h"

void hide_letter(CImg<unsigned char> &image, int x, int y, char letter) {
    unsigned char * red   = image.data(x, y, 0, 0);
    unsigned char * green = image.data(x, y, 0, 1);
    unsigned char * blue  = image.data(x, y, 0, 2);

    unsigned char red_char   = (letter >> 5);
    unsigned char green_char = (letter << 3) >> 5;
    unsigned char blue_char  = (letter << 6) >> 6;

    cout << "hide letter " << letter << " r " << red_char << " g " << green_char << " b " << blue_char << endl;

    *red = *red & red_char;
    *green = *green & green_char;
    *blue = *blue & blue_char;
}

unsigned char decode_letter(const unsigned char * red, const unsigned char * green, const unsigned char * blue) {
    unsigned char red_char   = (*red << 5);
    unsigned char green_char = (*green << 5) >> 3;
    unsigned char blue_char  = (*blue << 6) >> 6;

    cout << "decode letter r " << red_char << " g " << green_char << " b " << blue_char << endl;

    unsigned char ret = red_char & green_char & blue_char;

    return ret;
}

/*
 * Hides message in image.
 */
void hide_message(CImg<unsigned char> &image, string message) {
    // Note: RGB is stored as a planar structure, not interleaved.
    int width = image.width();
    int height = image.height();

    unsigned char *red, *green, *blue;

    auto it     = begin(message);
    auto it_end = end(message);

    // TODO: fix for loop later
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            red   = image.data(i, j, 0, 0);
            green = image.data(i, j, 0, 1);
            blue  = image.data(i, j, 0, 2);

            if (it == it_end) {
                return;
            } else {
                char temp_char = *it;
                cout << "Adding " << temp_char << endl;
                hide_letter(image, i, j, temp_char);
                cout << "char at i " << i << " and j " << j << " is " << *image.data(i, j, 0, 0) << endl;
                it++;
            }
        }
    }
    return;
}

string decode_message(CImg<unsigned char> const &image) {
    // TODO: add EOL sequence.
    stringstream ret;

    for (int i = 0; i < 24; i++) {
        const unsigned char * red = image.data(0, i, 0, 0);
        const unsigned char * green = image.data(0, i, 0, 1);
        const unsigned char * blue = image.data(0, i, 0, 2);

        ret << decode_letter(red, green, blue);
    }
    
    return ret.str();
}

/*
 * Helper method to get user input.
 */
string get_user_input() {
    return "Getting user input";
}

/*
 * TODO: use user input for this
 */
string get_secret_message() {
    return "Drake looks like a sloth";
}

int main() {
    // Replace this later with command line argument.
    const char *const file_name   = "sloth.bmp";
    const char *const target_name = "target.bmp";
    string secret_message         = get_secret_message();

    // Grab the image inside the current working directory with the specified filename.
    CImg<unsigned char> image(file_name);

    // Hide the message in the image.
    hide_message(image, secret_message);

    // Save the modified image under a target name.
    image.save(target_name);

    // Open target image.
    CImg<unsigned char> target_image(target_name);

    cout << "Decoded: " << decode_message(target_image) << endl;

    return 0;
}
