#include "steganosaurus.h"



void hide_letter(CImg<unsigned char> &image, int x, int y, char letter) {
    unsigned char * red   = image.data(x, y, 0, 0);
    unsigned char * green = image.data(x, y, 0, 1);
    unsigned char * blue  = image.data(x, y, 0, 2);

    bitset<8> letter_bits (letter);

    bitset<8> red_bits (*red);
    bitset<8> green_bits (*green);
    bitset<8> blue_bits (*blue);

    red_bits[0]   = letter_bits[0];
    red_bits[1]   = letter_bits[1];
    red_bits[2]   = letter_bits[2];
    green_bits[0] = letter_bits[3];
    green_bits[1] = letter_bits[4];
    green_bits[2] = letter_bits[5];
    blue_bits[0]  = letter_bits[6];
    blue_bits[1]  = letter_bits[7];

    *red   = (char) red_bits.to_ulong();
    *green = (char) green_bits.to_ulong();
    *blue  = (char) blue_bits.to_ulong();
}

unsigned char decode_letter(CImg<unsigned char> const &image, int x, int y) {
    bitset<8> letter_bits;

    const unsigned char * red   = image.data(x, y, 0, 0);
    const unsigned char * green = image.data(x, y, 0, 1);
    const unsigned char * blue  = image.data(x, y, 0, 2);

    bitset<8> red_bits (*red);
    bitset<8> green_bits (*green);
    bitset<8> blue_bits (*blue);

    letter_bits[0] = red_bits[0];
    letter_bits[1] = red_bits[1];
    letter_bits[2] = red_bits[2];
    letter_bits[3] = green_bits[0];
    letter_bits[4] = green_bits[1];
    letter_bits[5] = green_bits[2];
    letter_bits[6] = blue_bits[0];
    letter_bits[7] = blue_bits[1];

    return (unsigned char) letter_bits.to_ulong();
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
                hide_letter(image, i, j, temp_char);
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

        ret << decode_letter(image, 0, i);
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
