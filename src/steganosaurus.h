#define cimg_use_jpeg
#include "CImg.h"
#include <iostream>
#include <string>
#include <sstream>
#include <bitset>

using namespace std;
using namespace cimg_library;

class Steganosaurus {
    public:
        Steganosaurus();
        Steganosaurus(CImg<unsigned char> image);
        Steganosaurus(const char *const file_name);
        Steganosaurus operator=(Steganosaurus &rex);
        ~Steganosaurus();

        void hide_message(string secret_message);
        string decode_message();
        void excrete();

        int width();
        int height();

    private:
        CImg<unsigned char> * food;

        void set_rgb_bits(bitset<8> &red_bits, bitset<8> &green_bits, bitset<8> &blue_bits, bitset<8> const &letter_bits);
        void decode_rgb_bits(const bitset<8> &red_bits, const bitset<8> &green_bits, const bitset<8> &blue_bits, bitset<8> &letter_bits);
        void hide_letter(CImg<unsigned char> &image, int x, int y, char letter);
        unsigned char decode_letter(CImg<unsigned char> const &image, int x, int y);
        string get_user_input(string prompt);
        string get_secret_message();
};
