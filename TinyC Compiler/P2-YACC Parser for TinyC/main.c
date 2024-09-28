#include <stdio.h>
#include <stdlib.h>
#include "defs.tab.h"

extern int yyparse();
extern FILE *yyin;
extern void dfs(struct ParseTreeNode *node, int depth);

struct ParseTreeNode *root;

void yyerror(char *s)
{
    fprintf(stderr, "Error: %s\n", s);
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s <input_file>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    FILE *input = fopen(argv[1], "r");
    if (!input)
    {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    yyin = input;
    yyparse();
    dfs(root, 0);
    fclose(input);
    return 0;
}