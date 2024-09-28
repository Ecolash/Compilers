%{
    #define ID 1
    #define NUM 2
    #define ADD 3
    #define SUB 4
    #define MUL 5
    #define DIV 6
    #define MOD 7
    #define LPAREN 8
    #define RPAREN 9
    #define END 10

    #define EXPR 11
    #define OP 12
    #define ARG 13
    #define OTHER 14
%}

digit   [0-9]
number  [+-]?{digit}+
letter  [A-Za-z_]
others  [A-Za-z0-9_]
ID      {letter}{others}*
space   [ \t\n]
symbol  [.,;:!?{}\[\]'"`~@#$^&<>|\\]
symbols {symbol}+
%%

"+"                   { return ADD; }
"-"                   { return SUB; }
"*"                   { return MUL; }
"/"                   { return DIV; }
"%"                   { return MOD; }
"("                   { return LPAREN; }
")"                   { return RPAREN; }
{number}              { return NUM; }
{ID}                  { return ID; }
{space}               ;
{symbols}             { return OTHER; }
.                     { return OTHER; }

%%
int yywrap(void){ return 1; }
int yylex();
bool parse();
