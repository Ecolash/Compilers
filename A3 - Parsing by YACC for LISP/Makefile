all: expr

expr: expr.l expr.y evalexpr.c
	yacc -d expr.y
	flex expr.l
	gcc -o expr y.tab.c lex.yy.c evalexpr.c 

run: expr
	./expr input.txt > output.txt

clean:
	rm -f expr lex.yy.c y.tab.c y.tab.h 

deepclean:
	rm -f expr lex.yy.c y.tab.c y.tab.h output.txt`

