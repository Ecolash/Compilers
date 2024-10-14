#include "y.tab.c"
#include "lex.yy.c"

extern FILE *TAC;
extern FILE *yyin;

extern unsigned int size;
extern unsigned int regP, memP;
extern unsigned int offset;

typedef struct node {
    char* id;
    int offset;
} Node;

void add(char* id)
{
    SymbolTable[size].id = id;
    SymbolTable[size].offset = memP;
    offset++;
}

void update(char* id, int offset)
{
    for (int i = 0; i < size; i++)
    {
        int found = strcmp(SymbolTable[i].id, id);
        if (found == 0) return;
    }
    add(id);
}

int get(char* id)
{
    for (int i = 0; i < size; i++)
    {
        int found = strcmp(SymbolTable[i].id, id);
        if (found == 0) return SymbolTable[i].offset;
    }
    fprintf(stderr, "Error: %s not found in Symbol Table\n", id);
    exit(1);
}

int main(int argc, char *argv[])
{
    yyin = stdin;
    TAC = fopen("intcode.c", "w");
    if (argc > 1)
    {
        FILE *file = fopen(argv[1], "r");
        if (!file) fprintf(stderr, "Error opening file: %s\n", argv[1]);
        if (!file) exit(1);
        yyin = file;
    }
    if (TAC == NULL) 
    {
        fprintf(stderr, "Error opening file for writing\n");
        exit(1);
    }
    yyparse();
    fclose(file);
    fclose(TAC);
    return 0;
}