#include <vector>
#include <sstream>
#include "ciphers.hpp"

void print_table (const std::vector<int> &key, const std::vector<std::string> &table) noexcept {
    for (const int c : key) {
        std::cout << c << ' ';
    }
    std::cout << std::endl;
    for (unsigned long i = 0; i < table[0].size(); ++i) {
        for (unsigned long j = 0; j < table.size(); ++j) {
            switch (table[j][i]) {
                case '\n' :
                    std::cout << '^' << ' ';
                    break;
                case '\r' :
                    std::cout << '^' << ' ';
                    break;
                case ' ' :
                    std::cout << '_' << ' ';
                    break;
                default :
                    std::cout << table[j][i] << ' ';
                    break;
            }
        }
        std::cout << std::endl;
    }
}

static void make_key_vector (const std::string &key, std::vector<int> &new_key) {
    unsigned long i = 0;
    if (key.empty()) {
        throw std::runtime_error("");
    }
    while (i < key.size()) {
        std::string buf;
        while (key[i] != ',' && i < key.size()) {
            buf += key[i];
            ++i;
        }
        ++i;
        if (!isdigit(buf[0])) {
            throw std::invalid_argument("");
        }
        size_t pos = 0;
        int x = std::stoi(buf, &pos);
        if (pos != buf.size()) {
            throw std::invalid_argument("");
        }
        new_key.push_back(x);
    }    
}

static void key_check (const std::string &key, std::vector<int> &new_key) {
    try {
        make_key_vector(key, new_key);
    } catch (std::exception&) {
        throw std::runtime_error("Incorrect key.");
    }
    std::vector<bool> transposition;
    for (int i = 0; i < (int)new_key.size(); ++i) {
        transposition.push_back(false);
    }
    for (int number : new_key) {
        if (number <= (int)transposition.size() && number > 0) {
            if (!transposition[number - 1]) {
                transposition[number - 1] = true;
            } else {
                throw std::runtime_error("Incorrect key.");
            }
        } else {
            throw std::runtime_error("Incorrect key.");
        }
    }
    for (const bool &bit : transposition) {
        if (!bit) {
            throw std::runtime_error("Incorrect key.");
        }
    }
}

static int find (const std::vector<int> &key, int i) {
    int index = 0;
    for (int x : key) {
        if (x == i) {
            return index;
        }
        ++index; 
    }
    throw std::runtime_error("ERROR");
}

static void make_encryption_table (std::vector<std::string> &table, const int length, std::istream &input) {
    int i = 0;
    table.resize(length);
    while (input) {
        char c = input.get();
        if (!input) {
            break;
        }
        if (c == ' ' || !isspace(c)) {
            table[i] += c;
            ++i;
            i %= length;
        }
    }
    while (i % length) {
        table[i] += ' ';
        ++i;
    }
}

static void encrypt (std::vector<std::string> &table, const std::vector<int> &key, std::ostream &output) noexcept {
    for (unsigned long j = 0; j < key.size(); ++j) {
        auto n = find(key, j + 1);
        output << table[n];
    }
}

static void make_decryption_table (std::vector<std::string> &table, const std::vector<int> &key, const int length, std::istream &input) {
    std::string text, buf;
    while (input) {
        char c = input.get();
        if (!input) {
            break;
        }
        if (c == ' ' || !isspace(c)) {
            text += c;
        }
    }
    table.resize(length);
    if (text.size() % length) {
        std::cout << text.size() << ' ' << length << '\n';
        throw std::runtime_error("Impossible to decrypt by this method.");
    }
    const int str_length = text.size() / length;
    int pos = 0;
    for (int i = 0; i < length; ++i) {
        auto n = find(key, i + 1);
        table[n] = text.substr(pos, str_length);
        pos += str_length;
    }
}

static void decrypt (std::vector<std::string> &table, std::ostream &output) noexcept {
    auto length = table.size();
    auto width = table[0].size();
    for (unsigned long i = 0; i < width; ++i) {
        for (unsigned long j = 0; j < length; ++j) {
            output << table[j][i];
        }
    }
}

void transposition (const std::string &key, Mode mode, std::istream &input, std::ostream &output) {
    std::vector<int> new_key;
    key_check(key, new_key);
    const int length = new_key.size();
    std::vector<std::string> table;
    if (mode == ENCRYPT) {
        make_encryption_table(table, length, input);
        //print_table(new_key, table);
        encrypt(table, new_key, output);
    } else {
        make_decryption_table(table, new_key, length, input);
        //print_table(new_key, table);
        decrypt(table, output);
    }
    output << std::endl;
}
