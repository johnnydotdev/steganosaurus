#include "steganosaurus.h"

const string END_SEQUENCE = "ENDENDEND";

void set_rgb_bits(bitset<8> &red_bits, bitset<8> &green_bits, bitset<8> &blue_bits, bitset<8> const &letter_bits) {
    red_bits[0]   = letter_bits[0];
    red_bits[1]   = letter_bits[1];
    red_bits[2]   = letter_bits[2];
    green_bits[0] = letter_bits[3];
    green_bits[1] = letter_bits[4];
    green_bits[2] = letter_bits[5];
    blue_bits[0]  = letter_bits[6];
    blue_bits[1]  = letter_bits[7];
}

void decode_rgb_bits(const bitset<8> &red_bits, const bitset<8> &green_bits, const bitset<8> &blue_bits, bitset<8> &letter_bits) {
    letter_bits[0] = red_bits[0];
    letter_bits[1] = red_bits[1];
    letter_bits[2] = red_bits[2];
    letter_bits[3] = green_bits[0];
    letter_bits[4] = green_bits[1];
    letter_bits[5] = green_bits[2];
    letter_bits[6] = blue_bits[0];
    letter_bits[7] = blue_bits[1];
}

void hide_letter(CImg<unsigned char> &image, int x, int y, char letter) {
    unsigned char * red   = image.data(x, y, 0, 0);
    unsigned char * green = image.data(x, y, 0, 1);
    unsigned char * blue  = image.data(x, y, 0, 2);

    bitset<8> letter_bits (letter);
    bitset<8> red_bits (*red);
    bitset<8> green_bits (*green);
    bitset<8> blue_bits (*blue);

    set_rgb_bits(red_bits, green_bits, blue_bits, letter_bits);

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

    decode_rgb_bits(red_bits, green_bits, blue_bits, letter_bits);
    
    return (unsigned char) letter_bits.to_ulong();
}

/*
 * Hides message in image.
 */
void hide_message(CImg<unsigned char> &image, const string secret_message) {
    // Note: RGB is stored as a planar structure, not interleaved.
    int width = image.width();
    int height = image.height();

    unsigned char *red, *green, *blue;

    // The secret message with the end sequence appended.
    string message = secret_message + END_SEQUENCE;

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
    stringstream ret;

    int width = image.width();
    int height = image.height();

    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            const unsigned char * red   = image.data(0, i, 0, 0);
            const unsigned char * green = image.data(0, i, 0, 1);
            const unsigned char * blue  = image.data(0, i, 0, 2);

            ret << decode_letter(image, i, j);

            // TODO: make this more efficient. how to search in stringstream? or maybe implement a basic FSM?
            if(ret.str().find(END_SEQUENCE) != string::npos) {
                return ret.str();
            }
        }
    }
    
    return ret.str();
}

/*
 * Helper method to get user input.
 */
string get_user_input(string prompt) {
    cout << prompt << endl;

    string ret;
    cin >> ret;

    return ret;
}

/*
 * TODO: use user input for this
 */
string get_secret_message() {
    return get_user_input("Welcome! Please input your secret message below to be fed into Steganosaurus Rex");
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

    cout << "DECODING...";

    // Open target image.
    CImg<unsigned char> target_image(target_name);

    cout << "Decoded message: " << decode_message(target_image) << endl;

    return 0;
}
