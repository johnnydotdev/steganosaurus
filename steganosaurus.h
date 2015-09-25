#define cimg_use_jpeg
#include "CImg.h"
#include <iostream>
#include <string>
#include <sstream>
#include <bitset>

using namespace std;
using namespace cimg_library;

void hide_letter(CImg<unsigned char> &image, int x, int y, char letter);

unsigned char decode_letter(const unsigned char * red, const unsigned char * green, const unsigned char * blue);

void hide_message(CImg<unsigned char> &image, string message);

string decode_message(CImg<unsigned char> const &image);

string get_user_input();

string get_secret_message();
