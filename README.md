# Steganosaurus
### A tool to hide secret messages in plain sight. You would use this if you were a spy.

My favorite dinosaur when I was young was the Stegosaurus. Meet Steganosaurus.

He takes your image, a message, and excretes a new image that looks--to the naked eye--identical.

Features:
- Built in C++
- Built on CImg
- Built while waiting for Amtrak
- Takes user input
- It's like a dinosaur that eats your images and messages and excretes the steganographed image

To do:
- Add encryption to messages
- Write message only on the border of the image, "randomly" distributed.
- Find a workaround to const correctness of CImg file names so that Steganosaurus can take user input for file names

To use:
1. Run `make`.
2. `./steganosaurus`

https://en.wikipedia.org/wiki/Security_through_obscurity courtesy of Topher Chung
