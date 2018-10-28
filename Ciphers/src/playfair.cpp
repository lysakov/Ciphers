#include "ciphers.hpp"
#include "playfair.hpp"

bool Matrix::find_char (const char c) const noexcept {
    for (int i = 0; i < MATRIX_LENGTH; ++i) {
        for (int j = 0; j < MATRIX_WIDTH; ++j) {
            if (matrix[i][j] == c) {
                return true;
            }
        }
    }
    return false;
}

void Matrix::check_char (char &c) const {
    if (!isalpha(c)) {
        throw std::runtime_error("Incorrect key.");
    }
    if (c == OMIT_CHAR) {
        --c;
    }
}

Matrix::Matrix (const std::string &string) {
    int counter = 0;
    if (string.empty()) {
        throw std::runtime_error("Incorrect key.");
    }
    for (char c : string) {
        check_char(c);
        if (!find_char(tolower(c))) {
            matrix[counter / MATRIX_LENGTH][counter % MATRIX_WIDTH] = tolower(c);
            ++counter;
        }   
    }
    char c = 'a';
    while (counter < MATRIX_LENGTH * MATRIX_WIDTH) {
        if (!find_char(c) && c != OMIT_CHAR) {
            matrix[counter / MATRIX_LENGTH][counter % MATRIX_WIDTH] = c;
            ++counter;
        }
        ++c;
    }   
}

void Matrix::print () const noexcept {
    for (int i = 0; i < MATRIX_LENGTH; ++i) {
        for (int j = 0; j < MATRIX_WIDTH; ++j) {
            std::cout << matrix[i][j] << ' ';
        }
        std::cout << std::endl;
    }
}

coordinates Matrix::find_pos (char c) const noexcept {
    if (c == OMIT_CHAR) {
        --c;
    }
    for (int i = 0; i < MATRIX_LENGTH; ++i) {
        for (int j = 0; j < MATRIX_WIDTH; ++j) {
            if (matrix[i][j] == c) {
                return coordinates (i, j);
            }
        }
    }
    return coordinates (ERROR, ERROR);
}

const char* Matrix::operator [] (int i) const noexcept {
    return matrix[i];
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

static char case_cast (const char symb, Case s_case) {
    if (!isalpha(symb)) {
        throw std::runtime_error("ERROR");
    }
    switch (s_case) {
        case LOWER_CASE :
            return tolower(symb);
        case UPPER_CASE :
            return toupper(symb);
        default :
            return symb;
    }
}

static char read_alpha (std::istream &input, std::string &buf, Case &s_case) {
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
    s_case = define_case(symb);
    return tolower(symb);
}

static int shift (int x, int shift) noexcept {
    x += shift;
    if (x < 0) {
        x = Matrix::MATRIX_LENGTH - 1;
    }
    return x;
}

static void playfair_rules (const Matrix &matrix, coordinates &xy1, coordinates &xy2, char &symb1, char &symb2, char &tmp, Mode mode, Case_vector &cases) noexcept { 
    int shift = 1;
    if (mode == DECRYPT) {
        shift = -1;
    }
    if ((xy1.first == xy2.first && xy1.second == xy2.second) || (xy2.second == ERROR)) {
        tmp = symb2;
        std::get<2>(cases) = std::get<1>(cases);
        xy2 = matrix.find_pos((symb2 = DOUBLE_CHAR));
        std::get<1>(cases) = LOWER_CASE;
    }
    if (xy1.first == xy2.first && xy1.second != xy2.second) {
        symb1 = case_cast(matrix[xy1.first][::shift(xy1.second, shift) % Matrix::MATRIX_WIDTH], std::get<0>(cases));
        symb2 = case_cast(matrix[xy2.first][::shift(xy2.second, shift) % Matrix::MATRIX_WIDTH], std::get<1>(cases));
    }
    if (xy1.first != xy2.first && xy1.second == xy2.second) {
        symb1 = case_cast(matrix[::shift(xy1.first, shift) % Matrix::MATRIX_LENGTH][xy1.second], std::get<0>(cases));
        symb2 = case_cast(matrix[::shift(xy2.first, shift) % Matrix::MATRIX_LENGTH][xy2.second], std::get<1>(cases));
    }
    if (xy1.first != xy2.first && xy1.second != xy2.second) {
        symb1 = case_cast(matrix[xy1.first][xy2.second], std::get<0>(cases));
        symb2 = case_cast(matrix[xy2.first][xy1.second], std::get<1>(cases));
    }
}

void playfair (const std::string &key, Mode mode, std::istream &input, std::ostream &output) {
    Matrix matrix(key);
    char tmp = 0;
    Case_vector cases = std::make_tuple(NULL_CASE, NULL_CASE, NULL_CASE);
    //matrix.print();
    while (input) {
        char symb1, symb2;
        coordinates xy1, xy2;
        std::string buf1, buf2;
        if (!tmp) {
            xy1 = matrix.find_pos((symb1 = read_alpha(input, buf1, std::get<0>(cases))));
        } else {
            if (mode == DECRYPT) {
                throw std::runtime_error("Text cannot be decrypted by this method.");
            }
            xy1 = matrix.find_pos((symb1 = tmp));
            std::get<0>(cases) = std::get<2>(cases);
            tmp = 0;
        }
        if (xy1.first != ERROR) {
            xy2 = matrix.find_pos((symb2 = read_alpha(input, buf2, std::get<1>(cases))));
        } else {
            output << buf1;
            break;
        }
        if (symb1 == DOUBLE_CHAR && symb2 == DOUBLE_CHAR) {
                throw std::runtime_error("Bigram 'xx' is not allowed.");
        }
        playfair_rules(matrix, xy1, xy2, symb1, symb2, tmp, mode, cases);
        output << buf1 << symb1 << buf2 << symb2;
    }
}
