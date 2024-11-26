%{
#define EXPR 1001
#define OP 1002
#define ARG 1003
#define REST 1004
#define LP 1005
#define RP 1006
#define PLUS 1007
#define STAR 1008
#define NUM 1009
%}

ws	[ \t\n]+
digits	[0-9]+
frac	\.{digits}
expt	[eE][+-]?{digits}
num	[+-]?{digits}{frac}?{expt}?

%%

{ws}	{ }
{num}	{ return NUM; }
"("	{ return LP; }
")"	{ return RP; }
"+"	{ return PLUS; }
"*"	{ return STAR; }
.	{ }

%%
