#bin/bash

lex latex.l
gcc procltx.c -o lexer
./lexer < A1.tex > output.txt
rm lexer lex.yy.c
