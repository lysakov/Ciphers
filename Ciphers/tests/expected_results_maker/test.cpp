#include <iostream>
#include <fstream>

void transposition () {
    std::ifstream input("tests/test.txt");
    std::ofstream output("tests/answer2.txt");
    while (input) {
        char c = input.get();
        if (!input) {
            break;
        }
        if (c == '\n') {
            output << ' ';
        } else {
            output << c;
        }
    }
}

enum { ERROR = -1 };

static char read_alpha (std::istream &input, std::string &buf) {
    char symb;
    while (input) {
        symb = input.get();
        if (!isalpha(symb) && input) {
            buf += symb;
        } else {
            break;
        }
    }
    if (!input) {
        return ERROR;
    }
    return tolower(symb);
}

void playfair () {
    std::ifstream input("tests/test.txt");
    std::ofstream output("tests/answer5.txt");
    char tmp = 0;
    while (input) {
        char symb1, symb2;
        std::string buf1, buf2;
        if (!tmp) {
            symb1 = read_alpha(input, buf1);
        } else {
            symb1 = tmp;
            tmp = 0;
        }
        if (symb1 == 'j') {
            symb1 = 'i';
        }
        if (symb1 != ERROR) {
            symb2 = read_alpha(input, buf2);
        } else {
            output << buf1;
            break;
        }
        if (symb2 == 'j') {
            symb2 = 'i';
        }
        if (symb1 == symb2) {
            tmp = symb2;
            symb2 = 'x';
        }
        output << buf1 << symb1 << buf2 << symb2;
    }
}

int main () {
    //transposition();
    //playfair();
    return 0;
}
