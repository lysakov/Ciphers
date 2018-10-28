CC = g++
LCOV_DIR = lcov/bin
CFLAGS = -Iinc -Wall -Werror -pedantic-errors -Wextra -std=c++14 -ftrapv -O2 -g
OBJECTS = obj/vigenere.o obj/playfair.o obj/transposition.o obj/interface.o
EXEC = ciphers.out 
TESTS_DIR = tests/files/
RESULTS = $(TESTS_DIR)result4.txt $(TESTS_DIR)result5.txt $(TESTS_DIR)result2.txt $(TESTS_DIR)result_enc4.txt $(TESTS_DIR)result_enc5.txt $(TESTS_DIR)result_enc2.txt

all : $(EXEC)

$(EXEC) : $(OBJECTS) obj/main.o
	$(CC) $(OBJECTS) obj/main.o -o $(EXEC)

obj/main.o : src/main.cpp inc/ciphers.hpp inc/interface.hpp
	$(CC) src/main.cpp $(CFLAGS) -c -o obj/main.o

obj/vigenere.o : src/vigenere.cpp inc/ciphers.hpp
	$(CC) src/vigenere.cpp $(CFLAGS) -c -o obj/vigenere.o

obj/playfair.o : src/playfair.cpp inc/ciphers.hpp inc/playfair.hpp
	$(CC) src/playfair.cpp $(CFLAGS) -c -o obj/playfair.o

obj/transposition.o : src/transposition.cpp inc/ciphers.hpp
	$(CC) src/transposition.cpp $(CFLAGS) -c -o obj/transposition.o

obj/interface.o : src/interface.cpp inc/interface.hpp inc/ciphers.hpp
	$(CC) src/interface.cpp $(CFLAGS) -c -o obj/interface.o

obj/transposition_main.o : src/transposition_main.cpp inc/interface.hpp inc/ciphers.hpp
	$(CC) src/transposition_main.cpp $(CFLAGS) -c -o obj/transposition_main.o

obj/vigenere_main.o : src/vigenere_main.cpp inc/interface.hpp inc/ciphers.hpp
	$(CC) src/vigenere_main.cpp $(CFLAGS) -c -o obj/vigenere_main.o

obj/playfair_main.o : src/playfair_main.cpp inc/interface.hpp inc/ciphers.hpp
	$(CC) src/playfair_main.cpp $(CFLAGS) -c -o obj/playfair_main.o

transposition : $(OBJECTS) obj/transposition_main.o
	$(CC)  $(OBJECTS) obj/transposition_main.o $(CFLAGS) -o transposition.out

vigenere : $(OBJECTS) obj/vigenere_main.o
	$(CC)  $(OBJECTS) obj/vigenere_main.o $(CFLAGS) -o vigenere.out

playfair : $(OBJECTS) obj/playfair_main.o
	$(CC)  $(OBJECTS) obj/playfair_main.o $(CFLAGS) -o playfair.out

clean :
	rm -f *.out obj/*.o
	rm -rf *.dSYM
	rm -f $(RESULTS)

run : $(EXEC)
	./$(EXEC)
