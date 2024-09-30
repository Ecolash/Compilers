#!/bin/bash

yacc -d poly.y
flex poly.l
gcc -o parser polyutils.c
./parser input.txt > output.txt
rm -f lex.yy.c y.tab.c y.tab.h parser
