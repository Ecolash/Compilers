CC=gcc
LC=lex
CFLAG=-c 
CFLAGW=-Wall

output.txt: a.out test.c
	./a.out < test.c > output.txt

a.out: lex.yy.c tokenizer.o
	$(CC) $(CFLAGW) tokenizer.o 

lex.yy.c: defs.l
	$(LC) defs.l

tokenizer.o: tokenizer.c
	$(CC) $(CFLAG) tokenizer.c

clean:
	rm -f *.o lex.yy.c a.out

deepclean: 
	rm -f *.o lex.yy.c a.out output.txt