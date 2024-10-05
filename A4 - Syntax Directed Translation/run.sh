#!/bin/bash

echo "+++ Generating parser code with yacc..."
yacc -d poly.y

echo "+++ Generating lexical analyzer code with flex..."
flex poly.l

echo "+++ Compiling with gcc..."
gcc -o parser polyutils.c

echo "+++ Running parser on input.txt..."
./parser input.txt > output.txt

echo "+++ Cleaning up generated files..."
rm -f lex.yy.c y.tab.c y.tab.h parser

echo "+++ Done."