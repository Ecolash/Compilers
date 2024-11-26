%{
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int yylex ( );

struct addr {
   int type;  /* NUM, ID, or TMP */
   int val;   /* Integer value for NUM, temporary number for TMP, 0 for ID */
   char *id;  /* Name of the variable for ID, NULL for NUM and TMP */
};

int tmpno = 0;  /* Number of the temporary in the sequence 1, 2, 3, ... */

/* Whenever a new temporary is to be created, call this function */
struct addr *gentmpaddr ( struct addr * , char , struct addr * ) ;

%}

%start E

%union { struct addr *ADDR; char SYMB; }
%token <ADDR> NUM ID TMP
%token <SYMB> STAR CARET LP RP
%type <ADDR> E F B

%%

E	: F		{ $$ = $1; }
	| E STAR F	{ $$ = gentmpaddr($1,$2,$3); }
	;

F	: B		{ $$ = $1; }
	| B CARET F	{ $$ = gentmpaddr($1,$2,$3); }
	;

B	: NUM		{ $$ = $1; }
	| ID		{ $$ = $1; }
	| LP E RP	{ $$ = $2; }
	;

%%

struct addr *gentmpaddr ( struct addr *A1, char op, struct addr *A2 )
{
   struct addr *A;

   ++tmpno;
   A = (struct addr *)malloc(sizeof(struct addr));
   A->type = TMP;
   A->val = tmpno;
   A->id = NULL;

   printf("$%-4d =  ", tmpno);
   if (A1->type == NUM) printf("%d", A1->val);
   else if (A1->type == ID) printf("%s", A1->id);
   else if (A1->type == TMP) printf("$%d", A1->val);
   printf(" %c ", op);
   if (A2->type == NUM) printf("%d", A2->val);
   else if (A2->type == ID) printf("%s", A2->id);
   else if (A2->type == TMP) printf("$%d", A2->val);
   printf("\n");

   return A;
}

int main ()
{
   yyparse();
   exit(0);
}

void yyerror ( char *msg ) { fprintf(stderr, "Error: %s\n", msg); }
