#!/bin/bash

g++ -c translator.h
g++ -c translator.cxx

bison -dtv defs.y
g++ -c defs.tab.c
flex defs.l
g++ -c lex.yy.c

g++ lex.yy.o defs.tab.o translator.o -o a.out
mkdir -p ./Outputs

echo "Inputs contains the test cases."
echo "Running test cases..."

./a.out Inputs/input1.c > Outputs/output1.out
echo "(1/5) Testcases run successfully..."

./a.out Inputs/input2.c > Outputs/output2.out
echo "(2/5) Testcases run successfully..."

./a.out Inputs/input3.c > Outputs/output3.out
echo "(3/5) Testcases run successfully..."

./a.out Inputs/input4.c > Outputs/output4.out
echo "(4/5) Testcases run successfully..."

./a.out Inputs/input5.c > Outputs/output5.out
echo "(5/5) Testcases run successfully..."

echo "Check Outputs folder for the outputs..."
rm -f lex.yy.c lex.yy.o defs.tab.c defs.tab.h defs.tab.o 
rm -f translator.o a.out translator.h.gch defs.output