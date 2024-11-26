%{
#include "y.tab.h"
int yylex();
void yyerror ( char * );

struct addr {
   int type;
   int val;
   char *id;
};
%}

ws      [ \t\n]+
num     [+-]?[0-9]+
id      [a-zA-Z_][a-zA-Z0-9_]*

%%

{ws}	{ }
"*"	{ yylval.SYMB = '*'; return STAR; }
"^"	{ yylval.SYMB = '^'; return CARET; }
"("	{ yylval.SYMB = '('; return LP; }
")"	{ yylval.SYMB = ')'; return RP; }
{num}   { yylval.ADDR = (struct addr *)malloc(sizeof(struct addr));
          yylval.ADDR -> type = NUM;
          yylval.ADDR -> val = atoi(yytext);
          yylval.ADDR -> id = NULL;
          return NUM;
        }
{id}	{ yylval.ADDR = (struct addr *)malloc(sizeof(struct addr));
          yylval.ADDR -> type = ID;
          yylval.ADDR -> val = 0;
          yylval.ADDR -> id = (char *)malloc((1 + strlen(yytext))*sizeof(char));
          strcpy(yylval.ADDR -> id, yytext);
          return ID;
        }
.	{ }

%%

int yywrap ( ) { return 1; }
