#include "steganosaurus.cpp"

int main() {
    cout << "Behold, Steganosaurus!" << endl;
    // Replace this later with command line argument.
    const char *const file_name   = "food/sloth.bmp";
    const char *const target_name = "excretions/target.bmp";
    Steganosaurus rex(file_name);
    string secret_message         = "Drake looks sort of like a sloth";

    // Check that message is hide-able inside bmp.
    int width  = rex.width();
    int height = rex.height();
    if (width * height < secret_message.length()) {
        // Throw an exception if the message length exceeds the number of pixels.
        throw;
     }

    // Hide the message in the image.
    rex.hide_message(secret_message);

    // Save the modified image under a target name.
    rex.excrete();

    // Open target image.
    Steganosaurus tgt_rex(target_name);

    cout << "Decoded message: " << tgt_rex.decode_message() << endl;

    return 0;
}
