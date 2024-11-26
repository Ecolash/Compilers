# Phony Targets:
# - run				: This is the default target that generates the executable file
# - test			: This target runs the project's test suite to verify that the code is functioning as expected.
# - clean: 			: This target removes all files generated during the build process, ensuring a clean state.
# - dump: 			: This target removes all files generated during the build process,except test outputs

LEX_FILE = defs.l
YACC_FILE = defs.y
TRANSLATOR_CXX = translator.cxx
TRANSLATOR_H = translator.h
OUTPUT_EXEC = a.out
TEST_DIR = Outputs
TEST_INPUT_DIR = Inputs

.SUFFIXES= 

TEST_CASES = 1.c 2.c 3.c 4.c 5.c

OBJ_FILES = lex.yy.o defs.tab.o translator.o

run: $(OBJ_FILES)
	g++ $(OBJ_FILES) -o $(OUTPUT_EXEC)

translator.o: $(TRANSLATOR_H) $(TRANSLATOR_CXX)
	g++ -c $(TRANSLATOR_H)
	g++ -c $(TRANSLATOR_CXX)

lex.yy.o: lex.yy.c
	g++ -c lex.yy.c

defs.tab.o: defs.tab.c
	g++ -c defs.tab.c

lex.yy.c: $(LEX_FILE) defs.tab.h $(TRANSLATOR_H)
	flex $(LEX_FILE)

defs.tab.c defs.tab.h: $(YACC_FILE)
	bison -dtv $(YACC_FILE)

test: $(OUTPUT_EXEC)
	mkdir -p $(TEST_DIR)
	@echo "\nInputs contains the test cases.\n"
	@echo "\nRunning test cases...\n"
	@for test_case in $(TEST_CASES); do \
		./$(OUTPUT_EXEC)  $(TEST_INPUT_DIR)/input$$test_case > $(TEST_DIR)/quads$${test_case%.c}.out; \
		echo "Test case input$$test_case executed successfully."; \
		sleep 0.2; \
	done
	@echo "\nAll test cases executed successfully.\n"
	@echo "\nCheck $(TEST_DIR) folder for the outputs.\n"

clean:
	rm -f lex.yy.c *.tab.c *.tab.h *.output *.o $(OUTPUT_EXEC) *.gch $(TEST_DIR)/*quads*.out
	
dump:
	rm -f lex.yy.c *.tab.c *.tab.h *.output *.o $(OUTPUT_EXEC) *.gch 
