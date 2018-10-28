#include "interface.hpp"

std::istream& getline (std::istream &input, std::string &str) {
    std::getline(input, str);
    while (isspace(str.back())) {
        str.pop_back();
    }
    return input;
}
