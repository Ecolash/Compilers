#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "y.tab.c"
#include "lex.yy.c"

extern FILE *TAC;
extern FILE *yyin;
extern void yyerror(const char *s);

extern unsigned int size;
extern unsigned int regP, memP;

typedef struct node Node;
extern Node SymbolTable[5000];

void add(char* id)
{
    SymbolTable[size].id = id;
    SymbolTable[size].offset = memP;
    memP = memP + 1;
    size++;
}

void update(char* id)
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
    fprintf(stderr, "Warning: %s not initialised before! \n", id);
    add(id);
    return get(id);
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
    fprintf(TAC, "#include <stdio.h>\n");
    fprintf(TAC, "#include <stdlib.h>\n");
    fprintf(TAC, "#include \"aux.c\"\n\n");
    fprintf(TAC, "int main() \n{\n");
    fprintf(TAC, "\tint R[12];\n");
    fprintf(TAC, "\tint MEM[65536];\n\n");

    yyparse();

    fprintf(TAC, "\texit(0);");
    fprintf(TAC, "\n}\n");
    fclose(yyin);
    fclose(TAC);
    return 0;
}

void yyerror(const char *s)
{
    fprintf(stderr, "%s\n", s);
}


