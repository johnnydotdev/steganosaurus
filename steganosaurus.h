#define cimg_use_jpeg
#include "CImg.h"
#include <iostream>
#include <string>
#include <sstream>

using namespace std;
using namespace cimg_library;

void hide_message(CImg<unsigned char> &image, string message);

string decode_message(CImg<unsigned char> const &image);

string get_user_input();

string get_secret_message();
