# Phony Targets:
# - all				: This is the default target that generates the executable file
# - run  			: This target runs the sample.txt file
# - clean: 			: This target removes all files generated during the build process, ensuring a clean state.
# - dump: 			: This target removes all files generated during the build process,except 3 output files

LEX_SRC = prog.l
YACC_SRC = prog.y
GEN_SRC = codegen.cpp
SAMPLE = input.txt

LEX_GEN = lex.yy.c
YACC_GEN = y.tab.c y.tab.h
EXEC_GEN = parser
EXEC = ic

all: $(EXEC_GEN)

$(EXEC_GEN): $(LEX_GEN) $(YACC_GEN) $(GEN_SRC)
	@echo "+++ Compiling incodegen.c with gcc..."
	g++ -o $(EXEC_GEN) -w $(GEN_SRC)

$(LEX_GEN): $(LEX_SRC)
	@echo "+++ Generating lexical analyzer code with flex..."
	flex $(LEX_SRC)

$(YACC_GEN): $(YACC_SRC)
	@echo "+++ Generating parser code with yacc..."
	yacc -d $(YACC_SRC)

run: $(EXEC_GEN)
	@echo "+++ Running parser..."
	./$(EXEC_GEN) $(SAMPLE)

	@echo "===================================================="
	@echo ">>> Successfully generated 3 files"
	@echo "----------------------------------------------------"
	@echo "Intermediate code   >> intermediate.out"
	@echo "Machine Target code >> target.out"
	@echo "Register Log Info   >> register_log.out"
	@echo "===================================================="

clean:
	@echo "+++ Cleaning up..."
	rm -f $(LEX_GEN) $(YACC_GEN) $(EXEC_GEN) $(EXEC)
	rm -f intermediate.out target.out register_log.out

dump:
	@echo "+++ Deleting generated files except output..."
	rm -f $(LEX_GEN) $(YACC_GEN) $(EXEC_GEN)


