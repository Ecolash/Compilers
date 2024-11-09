echo "+++ Generating parser code with yacc..."
yacc -dtv prog.y

echo "+++ Generating lexical analyzer code with flex..."
flex prog.l

echo "+++ Compiling with g++..."
g++ -o parser codegen.cpp

echo "+++ Running parser on input.txt..."
./parser input.txt

echo "+++ Cleaning up generated files..."
rm -f lex.yy.c y.tab.c y.tab.h parser

echo "+++ Done."