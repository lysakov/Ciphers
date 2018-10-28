#include "interface.hpp"

std::istream& getline (std::istream &input, std::string &str) {
    std::getline(input, str);
    while (isspace(str.back())) {
        str.pop_back();
    }
    return input;
}

template <typename T> 
static void cipher (T cipher_func, const std::string &key, Mode mode, const std::string &input_name, const std::string &output_name) {
    if (input_name == "stdin") {
        cipher_func(key, mode, (std::istream&)std::cin, (std::ostream&)std::cout);
        return;
    }
    if (output_name == "stdout") {
        std::ifstream input(input_name);
        if (!input) {
            throw std::runtime_error("Input file doesn't exist.");
        }
        cipher_func(key, mode, input, (std::ostream&)std::cout);
        return;
    }
    std::ifstream input(input_name);
    if (!input) {
        throw std::runtime_error("Input file doesn't exist.");
    }
    std::ofstream output(output_name);
    cipher_func(key, mode, input, output);
}

static int read_int () {
    int res;
    bool flag = true;
    do {
        std::string str;
        std::istream &input = getline(std::cin, str);
        try {
            size_t pos = 0;
            res = std::stoi(str, &pos);
            if (pos != str.size()) {
                throw std::invalid_argument("");
            }
            flag = true;
        } catch (std::exception&) {
            if (!input) {
                throw std::runtime_error("Ctrl+D pressed.");
            }
            flag = false;
            std::cerr << "Number is not integer. Try again." << std::endl;
        }
    } while (!flag);
    return res;
}

static int choose_cipher () {
    int cipher;
    do {
        std::cout << "1.VIGENER CIPHER" << std::endl;
        std::cout << "2.PLAYFAIR CIPHER" << std::endl;
        std::cout << "3.COLUMNAR TRANSPOSITION CIPHER" << std::endl;
        cipher = read_int();
    } while (cipher < 1 || cipher > 3);
    return cipher;
}

static Mode choose_mode () {
    int x;
    Mode mode;
    do {
        std::cout << "1.ENCRYPT" << std::endl << "2.DECRYPT" << std::endl;
        x = read_int();
    } while (x != 1 && x != 2);
    if (x == 1) {
        mode = ENCRYPT;
    } else {
        mode = DECRYPT;
    }
    return mode;
}

static void read_arguments (std::string &key, std::string &input_name, std::string &output_name) {
    std::cout << "Enter key : ";
    getline(std::cin, key);
    std::cout << "Enter name of input file : ";
    getline(std::cin, input_name);
    if (input_name == "stdin") {
        return;
    }
    std::cout << "Enter name of output file : ";
    getline(std::cin, output_name);
}

static void run_cipher (int cipher_code, std::string &key, Mode mode, std::string &input_name, std::string &output_name) {
    switch (cipher_code) {
        case 1 :
            try {
                cipher(vigenere, key, mode, input_name, output_name);
            } catch (const std::exception &e) {
                std::cerr << "VIGENERE CIPHER : " << e.what() << std::endl;
            }
            break;
        case 2 :
            try {
                cipher(playfair, key, mode, input_name, output_name);
            } catch (const std::exception &e) {
                std::cerr << "PLAYFAIR CIPHER : " << e.what() << std::endl;
            }
            break;
        case 3 :
            try {
                cipher(transposition, key, mode, input_name, output_name);
            } catch (const std::bad_alloc &e) {
                std::cerr << "COLUMNAR TRANSPOSITION CIPHER : File is too large." << e.what() << std::endl;
            } catch (const std::exception &e) {
                std::cerr << "COLUMNAR TRANSPOSITION CIPHER : " << e.what() << std::endl;
            }
            break;
        default :
            break;
    }
}

void run () {
    int repeat = 0;
    do {
        int cipher = choose_cipher();
        Mode mode = choose_mode();
        std::string key, input_name, output_name;
        read_arguments(key, input_name, output_name);
        run_cipher(cipher, key, mode, input_name, output_name);
        std::cout << "REPEAT? (1 - yes, 0 - no) ";
        repeat = read_int();
    } while (repeat);
}
