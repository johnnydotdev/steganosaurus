#include "steganosaurus.h"

const string END_SEQUENCE = "ENDENDEND";

Steganosaurus::Steganosaurus() {
    
}

Steganosaurus::Steganosaurus(CImg<unsigned char> image) {
    this->food = new CImg<unsigned char> (image);
}

Steganosaurus::Steganosaurus(const char *const file_name) {
    this->food = new CImg<unsigned char> (file_name);
}

Steganosaurus::~Steganosaurus() {
    delete this->food;
}

int Steganosaurus::width() {
    return this->food->width();
}

int Steganosaurus::height() {
    return this->food->height();
}

void Steganosaurus::excrete() {
    this->food->save("excretions/target.bmp");
}

void Steganosaurus::set_rgb_bits(bitset<8> &red_bits, bitset<8> &green_bits, bitset<8> &blue_bits, bitset<8> const &letter_bits) {
    red_bits[0]   = letter_bits[0];
    red_bits[1]   = letter_bits[1];
    red_bits[2]   = letter_bits[2];
    green_bits[0] = letter_bits[3];
    green_bits[1] = letter_bits[4];
    green_bits[2] = letter_bits[5];
    blue_bits[0]  = letter_bits[6];
    blue_bits[1]  = letter_bits[7];
}

void Steganosaurus::decode_rgb_bits(const bitset<8> &red_bits, const bitset<8> &green_bits, const bitset<8> &blue_bits, bitset<8> &letter_bits) {
    letter_bits[0] = red_bits[0];
    letter_bits[1] = red_bits[1];
    letter_bits[2] = red_bits[2];
    letter_bits[3] = green_bits[0];
    letter_bits[4] = green_bits[1];
    letter_bits[5] = green_bits[2];
    letter_bits[6] = blue_bits[0];
    letter_bits[7] = blue_bits[1];
}

void Steganosaurus::hide_letter(CImg<unsigned char> &image, int x, int y, char letter) {
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

unsigned char Steganosaurus::decode_letter(CImg<unsigned char> const &image, int x, int y) {
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
void Steganosaurus::hide_message(const string secret_message) {
    // Note: RGB is stored as a planar structure, not interleaved.
    int width = this->food->width();
    int height = this->food->height();

    unsigned char *red, *green, *blue;

    // The secret message with the end sequence appended.
    string message = secret_message + END_SEQUENCE;

    auto it     = begin(message);
    auto it_end = end(message);

    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            red   = this->food->data(i, j, 0, 0);
            green = this->food->data(i, j, 0, 1);
            blue  = this->food->data(i, j, 0, 2);

            if (it == it_end) {
                return;
            } else {
                char temp_char = *it;
                hide_letter(*this->food, i, j, temp_char);
                it++;
            }
        }
    }
    return;
}

string Steganosaurus::decode_message() {
    stringstream ret;

    int width  = this->width();
    int height = this->height();

    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            const unsigned char * red   = this->food->data(0, i, 0, 0);
            const unsigned char * green = this->food->data(0, i, 0, 1);
            const unsigned char * blue  = this->food->data(0, i, 0, 2);

            ret << decode_letter(*this->food, i, j);

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
string Steganosaurus::get_user_input(string prompt) {
    cout << prompt << endl;

    string ret;
    cin >> ret;

    return ret;
}

/*
 * TODO: use user input for this
 */
string Steganosaurus::get_secret_message() {
    return get_user_input("Please input your secret message below to be fed into Steganosaurus Rex");
}
