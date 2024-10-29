/*=========================================//
NAME - TUHIN MONDAL
ROLL NUMBER - 22CS10087
//=========================================*/
%{
#include "y.tab.h"
#include <stdio.h>
#include <stdlib.h>
%}

digit   [0-9]
space   [ \t\n]
letter  [a-zA-Z_]
others  [a-zA-Z0-9_]
num     [+-]?[1-9]({digit}*)
id      {letter}({others}*)

%%
"set"          { return SET; }
{id}           { yylval.id = strdup(yytext); return ID; }
{num}          { yylval.num = atoi(yytext); return NUM; }
"("            { return '('; }
")"            { return ')'; }
"+"            { return '+'; }
"-"            { return '-'; }
"*"            { return '*'; }
"/"            { return '/'; }
"%"            { return '%'; }
"**"           { return '^'; }
{space}        { /* ignore whitespace */ }
.              { /* ignore invalid characters */ }
%%

int yywrap() {
    return 1;
}