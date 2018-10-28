CC = g++
LCOV_DIR = lcov/bin
CFLAGS = -Iinc -Wall -Werror -pedantic-errors -Wextra -std=c++14 -ftrapv -O2 -g
OBJECTS = obj/vigenere.o obj/interface.o
EXEC = vigenere.out 

all : $(EXEC)

$(EXEC) : $(OBJECTS) obj/main.o
	$(CC) $(OBJECTS) obj/main.o -o $(EXEC)

obj/main.o : src/main.cpp inc/ciphers.hpp inc/interface.hpp
	$(CC) src/main.cpp $(CFLAGS) -c -o obj/main.o

obj/vigenere.o : src/vigenere.cpp inc/ciphers.hpp
	$(CC) src/vigenere.cpp $(CFLAGS) -c -o obj/vigenere.o

obj/interface.o : src/interface.cpp inc/interface.hpp inc/ciphers.hpp
	$(CC) src/interface.cpp $(CFLAGS) -c -o obj/interface.o

clean :
	rm -f *.out obj/*.o
	rm -rf *.dSYM
