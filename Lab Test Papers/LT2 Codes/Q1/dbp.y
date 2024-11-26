%{
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int yylex ( );

typedef struct _node {
   int type;
   int op;
   double value;
   double partial;
   int count;
   struct _node *C[4];
} node;

node *addnodeP ( node * , node * );
node *addnodeS ( int , node * );
node *addnodeA ( double , node * );
%}

%start PROG

%union { struct _node *NODE; char PUNC; int KWD; double VAL; }
%token <KWD> MAX MIN AVG
%token <PUNC> LP RP SEP
%token <VAL> NUM
%type <NODE> PROG STMT ARG

%%

PROG	: STMT			{ $$ = addnodeP($1,NULL); }
	| STMT PROG		{ $$ = addnodeP($1,$2); }
	;

STMT	: MAX LP ARG RP		{ $$ = addnodeS(MAX,$3); }
	| MIN LP ARG RP		{ $$ = addnodeS(MIN,$3); }
	| AVG LP ARG RP		{ $$ = addnodeS(AVG,$3); }
	;

ARG	: NUM			{ $$ = addnodeA($1,NULL); }
	| NUM SEP ARG		{ $$ = addnodeA($1,$3); }
	;

%%

void yyerror ( char *msg ) { fprintf(stderr, "Error: %s\n", msg); }
