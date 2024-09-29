
CC = gcc
FLEX = flex
BISON = bison

YACC_SRC = defs.y
LEX_SRC = defs.l
MAIN_SRC = main.c
INPUT_SRC = test.c
OUTPUT_SRC = output.txt

YACC_OUTPUT = defs.tab.c
YACC_HEADER = defs.tab.h
LEX_OUTPUT = lex.yy.c

all: output

output: parser
	./parser $(INPUT_SRC) > $(OUTPUT_SRC)

parser: $(MAIN_SRC) $(YACC_OUTPUT) $(LEX_OUTPUT)
	$(CC) -o parser $(MAIN_SRC) $(YACC_OUTPUT) $(LEX_OUTPUT)

$(YACC_OUTPUT) $(YACC_HEADER): $(YACC_SRC)
	$(BISON) -d $(YACC_SRC)

$(LEX_OUTPUT): $(LEX_SRC)
	$(FLEX) $(LEX_SRC)

clean:
	rm -f $(YACC_OUTPUT) $(YACC_HEADER) $(LEX_OUTPUT) parser $(OUTPUT_SRC)
