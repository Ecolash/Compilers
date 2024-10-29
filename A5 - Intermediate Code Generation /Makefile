LEX_SRC = expr.l
YACC_SRC = expr.y
UTILS_SRC = intcodegen.c
GEN_SRC = intcode.c

LEX_GEN = lex.yy.c
YACC_GEN = y.tab.c y.tab.h
EXEC_GEN = icgen
EXEC = ic

all: $(EXEC_GEN)

$(EXEC_GEN): $(LEX_GEN) $(YACC_GEN) $(UTILS_SRC)
	@echo "+++ Compiling incodegen.c with gcc..."
	gcc -o $(EXEC_GEN) $(UTILS_SRC)

$(LEX_GEN): $(LEX_SRC)
	@echo "+++ Generating lexical analyzer code with flex..."
	flex $(LEX_SRC)

$(YACC_GEN): $(YACC_SRC)
	@echo "+++ Generating parser code with yacc..."
	yacc -d $(YACC_SRC)

run: $(EXEC) 

$(EXEC): $(GEN_SRC) 
	@echo "+++ Compiling intcode.c with gcc..."
	gcc -o $(EXEC) $(GEN_SRC) 
	./$(EXEC) > output.txt
	@echo ">>> The output is stored in output.txt"

$(GEN_SRC): $(EXEC_GEN) 
	@echo "+++ Running icgen on sample.txt..."
	./$(EXEC_GEN) sample.txt 
	@echo ">>> Generated intcode.c"

clean:
	@echo "+++ Cleaning up generated files..."
	rm -f $(LEX_GEN) $(YACC_GEN) $(EXEC_GEN) $(EXEC) $(GEN_SRC) output.txt
