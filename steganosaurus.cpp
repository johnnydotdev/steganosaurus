#include "steganosaurus.h"

using namespace cimg_library;
using namespace std;

/*
 * 
 */
void hide_message(CImg<unsigned char> &image, string message) {
    // Note: RGB is stored as a planar structure, not interleaved.
    int width = image.width();
    int height = image.height();

    int red = 0, green = 0, blue = 0;

    auto it     = begin(message);
    auto it_end = end(message);

    // TODO: fix for loop later
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            red   = (int) (*image.data(i, j, 0, 0));
            green = (int) (*image.data(i, j, 0, 1));
            blue  = (int) (*image.data(i, j, 0, 2));

            if (it == it_end) {
                return;
            } else {
                char temp_char = *it;
                cout << "Adding " << temp_char << endl;
                const unsigned char colors[] = { red, green, blue, (int) temp_char };
                image.draw_point(i, j, colors);
                it++;
            }
        }
    }
    return;
}

string decode_message(CImg<unsigned char> const &image) {
    return "";
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
    const char *const file_name   = "sloth.jpg";
    const char *const target_name = "target.jpg";
    string secret_message         = get_secret_message();

    // Grab the image inside the current working directory with the specified filename.
    CImg<unsigned char> image(file_name);
    const unsigned char colors[] = {255, 254, 253};
    image.draw_point(50, 50, colors);

//    // Test
//    unsigned char * data_test = image.data(50, 50, 0, 1);
//    int data_test_int = (int) (*data_test);
//    cout << data_test_int << endl;
//
//    data_test = image.data(50, 50, 0, 2);
//    data_test_int = (int) (*data_test);
//    cout << data_test_int << endl;

    // Hide the message in the image.
    hide_message(image, secret_message);

    // Save the modified image under a target name.
    image.save(target_name);

    return 0;
}
