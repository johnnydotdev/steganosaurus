#define cimg_use_jpeg
#include "CImg.h"
#include <iostream>
#include <string>

using namespace std;
using namespace cimg_library;

void hide_message(CImg<unsigned char> &image, string message);

string get_user_input();

string get_secret_message();
