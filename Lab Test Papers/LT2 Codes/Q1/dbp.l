%{
#include "y.tab.h"
int yylex();
void yyerror ( char * );
%}

ws	[ \t\n]+
num	[+-]?[0-9]+(\.[0-9]*)?

%%

{ws}	{ }
"max"	{ yylval.KWD = MAX; return MAX; }
"min"	{ yylval.KWD = MIN; return MIN; }
"avg"	{ yylval.KWD = AVG; return AVG; }
"("	{ yylval.PUNC = '('; return LP; }
")"	{ yylval.PUNC = ')'; return RP; }
","	{ yylval.PUNC = ','; return SEP; }
{num}	{ yylval.VAL = atof(yytext); return NUM; }
.	{ }

%%

int yywrap ( ) { return 1; }
