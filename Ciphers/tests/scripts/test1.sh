#!/bin/bash

size=$(wc -c < tests/files/test.txt)

make

mkdir /tmp/ciphers

./ciphers.out < tests/files/input1.txt > /tmp/ciphers/output.txt

if cmp -s tests/files/test.txt tests/files/result4.txt; then
    echo "VIGENERE : OK"
else
    echo "VIGENERE : FAIL"
fi

if cmp -s tests/files/expected_results5.txt tests/files/result5.txt; then
    echo "PLAYFAIR : OK"
else
    echo "PLAYFAIR : FAIL"
fi

if cmp -sn $size tests/files/test.txt tests/files/result2.txt;  then
    echo "COLUMNAR TRANSPOSITION : OK"
else
    echo "COLUMNAR TRANSPOSITION : FAIL"
fi
