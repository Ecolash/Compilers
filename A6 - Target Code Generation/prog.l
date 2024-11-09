%{
    #include "y.tab.h"
    extern int yylineno;
%}

/* REGULAR EXPRESSIONS */
/*---------------------*/
digit       [0-9]
inits       [a-zA-Z_]
chars       [a-zA-Z0-9_]
id          {inits}({chars}*)
num         [+-]?({digit}+)
ws          [ \t]+
nl          [\n]
%%

"set"       { yylval.keyword = set; return set; }
"when"      { yylval.keyword = when; return when; }
"while"     { yylval.keyword = while_; return while_; }
"loop"      { yylval.keyword = loop; return loop; }

"+"         { yylval.op = strdup(yytext); return ADD; }
"-"         { yylval.op = strdup(yytext); return SUB; }
"*"         { yylval.op = strdup(yytext); return MUL; }
"/"         { yylval.op = strdup(yytext); return DIV; }
"%"         { yylval.op = strdup(yytext); return MOD; }

"="         { yylval.relop = strdup(yytext); return EQ; }
"<"         { yylval.relop = strdup(yytext); return LT; }
">"         { yylval.relop = strdup(yytext); return GT; }
"<="        { yylval.relop = strdup(yytext); return LE; }
">="        { yylval.relop = strdup(yytext); return GE; }
"/="        { yylval.relop = strdup(yytext); return NE; }
"("         { return LP; }
")"         { return RP; }


{num}       { yylval.num = atoi(yytext); return NUMB; }
{id}        { yylval.id = strdup(yytext); return IDEN; }
{nl}        { yylineno++;  }
{ws}        { /* ignore */ }
.           { fprintf(stderr, "Unrecognized character: %s\n", yytext);exit(1); }
%%

int yywrap(void) { return 1;}


