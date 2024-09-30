LEX_SRC = poly.l
YACC_SRC = poly.y
UTILS_SRC = polyutils.c

LEX_GEN = lex.yy.c
YACC_GEN = y.tab.c y.tab.h
EXEC = parser

all: $(EXEC)

$(EXEC): $(LEX_GEN) $(YACC_GEN) $(UTILS_SRC)
	@echo "+++ Compiling with gcc..."
	gcc -o $(EXEC) $(UTILS_SRC)

$(LEX_GEN): $(LEX_SRC)
	@echo "+++ Generating lexical analyzer code with flex..."
	flex $(LEX_SRC)

$(YACC_GEN): $(YACC_SRC)
	@echo "+++ Generating parser code with yacc..."
	yacc -d $(YACC_SRC)

run: $(EXEC)
	@echo "+++ Running parser on input.txt..."
	./$(EXEC) input.txt > output.txt

clean:
	@echo "+++ Cleaning up generated files..."
	rm -f $(LEX_GEN) $(YACC_GEN) $(EXEC) output.txt
