#!/bin/bash

make

mkdir /tmp/ciphers

./ciphers.out < tests/files/input3.txt > /tmp/ciphers/output.txt

if cmp -s tests/files/expected_results_enc4.txt tests/files/result_enc4.txt; then
    echo "VIGENERE : OK"
else
    echo "VIGENERE : FAIL"
fi

if cmp -s tests/files/expected_results_enc5.txt tests/files/result_enc5.txt; then
    echo "PLAYFAIR : OK"
else
    echo "PLAYFAIR : FAIL"
fi

size=$(wc -c < tests/files/expected_results_enc2.txt)

if cmp -sn $size tests/files/expected_results_enc2.txt tests/files/result_enc2.txt; then
    echo "COLUMNAR TRANSPOSITION : OK"
else
    echo "COLUMNAR TRANSPOSITION : FAIL"
fi
