/*=========================================//
NAME - TUHIN MONDAL
ROLL NUMBER - 22CS10087
//=========================================*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "expr.h"
#include "y.tab.h"

extern int yyparse();
extern int yylex();
extern FILE *yyin;
extern char *yytext;

SYMBOL_TABLE T; // Global Symbol Table for NUM & IDs

/*=========================================//
Custom Function for calculating Power
//=========================================*/
int exponent(int base, int exp)
{
    if (exp == 0) return 1;
    if (exp % 2 == 0) return exponent(base * base, exp / 2);
    return base * exponent(base, exp - 1);
}

/*=========================================//
Symbol Table Functions
//=========================================*/
SYMBOL_TABLE init()
{
    SYMBOL_TABLE table = (SYMBOL_TABLE )malloc(sizeof(SymbolTable));
    table->head = NULL;
    table->size = 0;
    return table;
}

void add(SYMBOL_TABLE table, char *name, int value)
{
    SYM_PTR new_symbol = (SYM_PTR )malloc(sizeof(Symbol));
    new_symbol->name = strdup(name);
    new_symbol->value = value;
    new_symbol->next = table->head;
    table->head = new_symbol;
    table->size++;
}

void free_table(SYMBOL_TABLE table)
{
    SYM_PTR current = table->head;
    SYM_PTR next;
    while (current!= NULL)
    {
        next = current->next;
        free(current->name);
        free(current);
        current = next;
    }
    free(table);
}

SYM_PTR find(SYM_PTR current, char *name)
{
    if (current == NULL) return NULL; 
    if (strcmp(current->name, name) == 0) return current;
    return find(current->next, name);
}

int get(SYMBOL_TABLE table, char *name)
{
    SYM_PTR symbol = find(table->head, name);
    if (symbol != NULL) return symbol->value;
    printf("Error: Symbol %s not found\n", name);
    exit(EXIT_FAILURE);
}

void set(SYMBOL_TABLE table, char *name, int value)
{
    SYM_PTR symbol = find(table->head, name);
    if (symbol) symbol->value = value;
    else add(table, name, value);
}

/*=========================================//
Expression Tree Node Creation and Evaluation Functions
//=========================================*/

int evaluate(SYMBOL_TABLE table, EX_PTR node)
{
    switch (node->type)
    {
        case 0: return node->data.num;
        case 1: return get(table, node->data.id);
        case 2:
        {
            int L = evaluate(table, node->left);
            int R = evaluate(table, node->right);
            switch (node->data.op[0])
            {
                case '+': return L + R;
                case '-': return L - R;
                case '*': return L * R;
                case '/': return L / R;
                case '%': return L % R;
                case '^': return exponent(L, R);
                default:
                    printf("Error: Unknown operator %s\n", node->data.op);
                    exit(EXIT_FAILURE);
            }
        }
        default:
            printf("Error: Unknown node type\n");
            exit(EXIT_FAILURE);
    }
    return 0; 
}

EX_PTR initNLeaf(int num)
{
    EX_PTR node = (EX_PTR)malloc(sizeof(TreeNode));
    node->type = 0;
    node->data.num = num;
    node->left = NULL;
    node->right = NULL;
    return node;
}

EX_PTR initIDLeaf(char *id)
{
    EX_PTR node = (EX_PTR )malloc(sizeof(TreeNode));
    node->type = 1;
    node->data.id = strdup(id);
    node->left = NULL;
    node->right = NULL;
    return node;
}

EX_PTR initOPNode(char *op, EX_PTR left, EX_PTR right)
{
    EX_PTR node = (EX_PTR)malloc(sizeof(TreeNode));
    node->type = 2;
    node->data.op = op;
    node->left = left;
    node->right = right;
    return node;
}

void free_(EX_PTR node)
{
    if (node == NULL) return;
    if (node->type == 1) free(node->data.id);
    free_(node->left);
    free_(node->right);
    free(node);
}

/*=========================================//
Main Fuction to call yyparse() function
//=========================================*/
void yyerror(const char *s)
{
    printf("Error: %s\n", s);
}

int main(int argc, char *argv[])
{
    T = init();
    yyin = stdin;
    if (argc > 1)
    {
        FILE *file = fopen(argv[1], "r");
        if (!file) fprintf(stderr, "Error opening file: %s\n", argv[1]);
        if (!file) exit(EXIT_FAILURE);
        yyin = file; 
    }

    fprintf(stderr, "================================\n");
    if (!yyparse()) fprintf(stderr, "Status: Parsing successful!\n");
    else fprintf(stderr, "Status: Parsing failed!\n");
    fprintf(stderr, "================================\n");

    free_table(T);
    return 0;
}
