#ifndef CIPHER
#define CIPHER

#include <iostream>
#include <fstream>
#include <ctype.h>
#include <stdexcept>

enum Mode {
    ENCRYPT,
    DECRYPT
};

enum Case {
    NULL_CASE,
    UPPER_CASE,
    LOWER_CASE
};

enum {
    ALPHABET_LENGTH = 26
};

void playfair (const std::string &, Mode, std::istream &input = std::cin, std::ostream &output = std::cout);

#endif
