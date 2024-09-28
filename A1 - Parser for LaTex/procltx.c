/*=========================================//
NAME - TUHIN MONDAL
ROLL NUMBER - 22CS10087
//=========================================*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "lex.yy.c"

typedef struct _node
{
    char *name;
    int count;
    struct _node *next;
} node;

typedef node *Symbol_Table;

Symbol_Table addtbl(Symbol_Table T, char *id)
{
    node *p;
    p = T;
    while (p)
    {
        if (!strcmp(p->name, id))
        {
            p->count++;
            return T;
        }
        p = p->next;
    }
    p = (node *)malloc(sizeof(node));
    p->name = (char *)malloc((strlen(id) + 1) * sizeof(char));
    p->count = 1;
    strcpy(p->name, id);
    p->next = T;
    return p;
}

void freeTable(Symbol_Table T) {
   node *p;
   while (T) {
      p = T;
      T = T->next;
      free(p->name);
      free(p);
   }
}

void helper(node *p) {
    if (p == NULL)  return;
    helper(p->next);
    printf("%15s  (%1d)\n", p->name, p->count);
}

void TablePrint(Symbol_Table T) {
    helper(T);
}

int main()
{
    char name[100];
    int ntoken;
    Symbol_Table commands = NULL;
    Symbol_Table environments = NULL;
    int inline_ = 0;
    int displayed = 0;

    ntoken = yylex();
    while (ntoken)
    {
        switch (ntoken)
        {

        case BEGIN_:
            strncpy(name, yytext + 7, strlen(yytext) - 8);
            name[strlen(yytext) - 8] = '\0';
            environments = addtbl(environments, name);
            break;

        case COMMAND:
            commands = addtbl(commands, yytext);
            break;

        case MATH_MODE:
            displayed++;
            break;

        case INLINE_MODE:
            inline_++;
            break;

        default:
            break;
        }
        ntoken = yylex();
    }
    printf("Commands used:\n");
    TablePrint(commands);

    printf("\nEnvironments used:\n");
    TablePrint(environments);

    inline_ /= 2;
    displayed /= 2;

    printf("\n%d math equations found\n", inline_);
    printf("%d displayed equations found\n", displayed);
    freeTable(commands);
    freeTable(environments);
    return 0;
}