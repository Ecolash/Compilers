#!/bin/bash

yacc -d expr.y
lex expr.l
rm intcode.c
gcc intcodegen.c -o icgen
./icgen sample.txt
gcc intcode.c -o ic
./ic > output.out
rm icgen ic lex.yy.c y.tab.c y.tab.h