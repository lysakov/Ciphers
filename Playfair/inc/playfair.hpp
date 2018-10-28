#ifndef PLAYFAIR
#define PLAYFAIR

#include <tuple>

typedef std::pair<int, int> coordinates;
typedef std::tuple<Case, Case, Case> Case_vector;

enum {
    ERROR = -1,
    DOUBLE_CHAR = 'x',
    OMIT_CHAR = 'j'
};

class Matrix {

  public :
    enum {
        MATRIX_LENGTH = 5,
        MATRIX_WIDTH = 5
    };
    Matrix (const std::string&);
    void print () const noexcept;
    coordinates find_pos (const char) const noexcept;
    const char* operator [] (int) const noexcept;
  private :
    char matrix[MATRIX_LENGTH][MATRIX_WIDTH] = {{0}, {0}, {0}, {0}, {0}};
    bool find_char (const char) const noexcept;
    void check_char (char&) const;

};

#endif
