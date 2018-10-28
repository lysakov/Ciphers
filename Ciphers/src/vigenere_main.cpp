#include "ciphers.hpp"
#include "interface.hpp"

Mode choose_mode (std::string str) {
    if (str == "encrypt") {
        return ENCRYPT;
    }
    if (str == "decrypt") {
        return DECRYPT;
    }
    throw std::runtime_error("Wrong argument.");
}

int main (int argc, char *argv[]) {
    if (argv[1] == nullptr) {
        std::cerr << "Comand line arguments not found." << std::endl;
        return 1;
    }
    std::ifstream input(argv[argc - 1]);
    if (!input) {
        std::cerr << "File doesn't exist." << std::endl;
        return 1;
    }
    std::string mode, key;
    getline(input, mode);
    getline(input, key);
    try {
        vigenere(key, choose_mode(mode), input);
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}
