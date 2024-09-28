#!/bin/bash

lex list.l
g++ -O2 evalexpr.cpp -o parser

: > output.txt

echo "Output of list.txt:" >> output.txt
echo "--------------------------------" >> output.txt
./parser < list.txt >> output.txt
echo "================================" >> output.txt
echo "Output of biglist.txt:" >> output.txt
echo "--------------------------------" >> output.txt
./parser < biglist.txt >> output.txt
rm parser lex.yy.c
