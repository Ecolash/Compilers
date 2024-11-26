#include <stdio.h>
#include <stdlib.h>
#include "defs.h"

extern int yyparse();
extern FILE *yyin;

ParseTreeNode* createNode(char* s) {
    ParseTreeNode* node = (ParseTreeNode*)malloc(sizeof(ParseTreeNode));
    node->name = s;
    node->children = NULL; 
    node->childCount = 0;
    node->capacity = 0;    
    return node;
}

void addChild(ParseTreeNode* parent, ParseTreeNode* child) {
    if (parent->childCount == parent->capacity) {
        parent->capacity = parent->capacity == 0 ? 1 : parent->capacity * 2;
        parent->children = (ParseTreeNode**)realloc(parent->children, parent->capacity * sizeof(ParseTreeNode*));
    }
    parent->children[parent->childCount++] = child;
}

void dfs(ParseTreeNode* node, int depth, int last, int* markers) {
    if (!node) return;
    for (int i = 0; i < depth - 1; i++) {
        if (markers[i]) printf(" │ ");
        else printf("   ");
    }

    if (depth > 0) printf(last ? " └─ " : " ├─ ");
    printf("%s\n", node->name);

    if (node->childCount == 0) return;
    if (depth > 0) markers[depth - 1] = !last;
    for (int i = 0; i < node->childCount; i++) dfs(node->children[i], depth + 1, i == node->childCount - 1, markers);
}

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
    int markers[1000] = {0}; 
    printf("==================================\n");
    printf("PARSE TREE FOR TEST FILE:   \n");
    printf("==================================\n\n");
    dfs(root, 0, 1, markers);
    fclose(input);
    return 0;
}
