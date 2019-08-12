#!/bin/bash
# Test brute-log
rm -rf a.out brute_example0 brute_example1

g++ -Wall example.cc -o brute_example0 2>/dev/null
./brute_example0

echo

g++ -DBRUTE_NDEBUG example.cc -o brute_example1 2>/dev/null
./brute_example1

