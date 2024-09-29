#!/bin/bash

echo "+++ (1) Generating parser using bison..."
bison -d defs.y


echo "+++ (2) Generating lexer using flex..."
flex defs.l

echo "+++ (3) Compiling the lexer, parser, and main.c..."
gcc -o parser lex.yy.c defs.tab.c main.c -ll

echo "+++ (4) Running the parser on test.c and storing the output in output.out..."
./parser test.c > output.out

echo ""
echo "Done! Output stored in output.out"
rm -f lex.yy.c defs.tab.c defs.tab.h parser
