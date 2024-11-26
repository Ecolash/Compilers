all:
	yacc -d dbp.y
	lex dbp.l
	gcc dbp.c

run: all
	./a.out < sample.txt

clean:
	-rm -f lex.yy.c y.tab.c y.tab.h a.out
