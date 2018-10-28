#include "ciphers.hpp"

unsigned long my_stoul (const std::string buf) {
    size_t pos = 0;
    if (!isdigit(buf[0])) {
        throw std::invalid_argument("Number is not integer.");
    }
    unsigned long length = std::stoul(buf, &pos);
    if (pos != buf.size()) {
        throw std::invalid_argument("Number is not integer.");
    }
    return length;
}

static unsigned long get_key_length (std::string &key) {
    if (key.empty()) {
        throw std::runtime_error("Incorrect key.");
    }
    std::string buf;
    while (!isspace(key[0]) && !key.empty()) {
        buf += key[0];
        key.erase(key.begin());
    }
    key.erase(key.begin());
    return my_stoul(buf);
}
    
static std::string check_key (const std::string &key) {
    std::string new_key = key;
    auto length = get_key_length(new_key);
    if (length <= 0) {
        throw std::runtime_error("Incorrect key size.");
    }
    if (length > new_key.size()) {
        throw std::runtime_error("Declared size of key is bigger than the real one.");
    }
    unsigned long i = 0;
    for (i = 0; i < length; ++i) {
        if (!isalpha(new_key[i])) {
            throw std::runtime_error("Incorrect key.");
        }
    }
    new_key.erase(length, new_key.size() - length);
    return new_key;
}

static Case define_case (const char symb) {
    if (!isalpha(symb)) {
        throw std::runtime_error("ERROR");
    }
    if (symb == toupper(symb)) {
        return UPPER_CASE;
    } else {
        return LOWER_CASE;
    }
}

static void shift (char &symb, int &cur_pos, const std::string &key, Mode mode) noexcept {
    Case symb_case = define_case(symb);
    symb = toupper(symb);
    symb -= 'A';
    if (mode == ENCRYPT) {
        symb += tolower(key[cur_pos]) - 'a';
        symb %= ALPHABET_LENGTH;
    } else {
        symb -= tolower(key[cur_pos]) - 'a';
        symb = (symb + ALPHABET_LENGTH) % ALPHABET_LENGTH;
    }        
    symb += 'A';
    if (symb_case == LOWER_CASE) {
        symb = tolower(symb);
    }
    ++cur_pos;
    cur_pos %= key.size();
}

static unsigned long get_length (std::istream &input) {
    std::string buf;
    while (input) {
        char c = input.get();
        if (isspace(c)) {
            break;
        }
        if (input) {
            buf += c;
        }
    }
    return my_stoul(buf);
}

void vigenere (const std::string &key, Mode mode, std::istream &input, std::ostream &output) {
    char symb;
    int cur_pos = 0;
    std::string new_key = check_key(key);
    auto length = get_length(input);
    unsigned int i = 0;
    while (input && i < length) {
        symb = input.get();
        if (isalpha(symb)) {
            shift(symb, cur_pos, new_key, mode);
        }
        if (input) {
            output << symb;
        }
        ++i;
    }
    if (i < length) {
        std::cerr << "Declared size of text bigger then the real one." << std::endl;
    }
}
