#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lex.yy.c"

typedef struct _psnode {
   int data;
   struct _psnode *next;
} psnode;
typedef psnode *pstack;

typedef struct _tnode {
   int type;
   union {
      int op;
      double num;
   } data;
   struct _tnode *L, *R, *N;
} tnode;
typedef tnode *parsetree;

typedef struct _nsnode {
   tnode *ptr;
   struct _nsnode *next;
} nsnode;
typedef nsnode *nstack;

int ps_top ( pstack S )
{
   if (S == NULL) {
      fprintf(stderr, "*** Read from an empty parse stack\n");
      exit(1);
   }
   return S -> data;
}

pstack ps_push ( pstack S, int token )
{
   psnode *p;

   p = (psnode *)malloc(sizeof(psnode));
   p -> data = token;
   p -> next = S;
   return p;
}

pstack ps_pop ( pstack S )
{
   psnode *p;

   if (S == NULL) {
      fprintf(stderr, "*** Pop from an empty parse stack\n");
      exit(1);
   }
   p = S;
   S = S -> next;
   free(p);
   return S;
}

tnode *ns_top ( nstack S )
{
   if (S == NULL) {
      fprintf(stderr, "*** Read from an empty node stack\n");
      exit(2);
   }
   return S -> ptr;
}

nstack ns_push ( nstack S, tnode *parent )
{
   nsnode *p;

   p = (nsnode *)malloc(sizeof(nsnode));
   p -> ptr = parent;
   p -> next = S;
   return p;
}

nstack ns_pop ( nstack S )
{
   nsnode *p;

   if (S == NULL) {
      fprintf(stderr, "*** Pop from an empty node stack\n");
      exit(2);
   }
   p = S;
   S = S -> next;
   free(p);
   return S;
}

parsetree pt_init ( )
{
   tnode *T;

   T = (tnode *)malloc(sizeof(tnode));
   T -> type = 0;
   T -> L = T -> R = T -> N = NULL;
   return T;
}

tnode *pt_addchild ( tnode *p, int type )
{
   tnode *q;

   if (p == NULL) {
      fprintf(stderr, "*** Insert node in an empty parse tree\n");
      exit(3);
   }

   q = (tnode *)malloc(sizeof(tnode));
   q -> L = q -> R = q -> N = NULL;
   q -> type = type;
   if (type == OP) (q -> data).op = yytext[0];
   else if (type == NUM) (q -> data).num = atof(yytext);

   if (p -> L == NULL) {
      p -> L = p -> N = q;
   } else {
      p -> N -> R = q;
      p -> N = q;
   }

   return q;
}

void prntree ( parsetree T, int l )
{
   int i;

   if (T == NULL) return;
   for (i=0; i<l; ++i) printf("      ");
   if (T -> type == OP) printf("%c\n", (T -> data).op);
   else if (T -> type == NUM) printf("%le\n", (T -> data).num);
   prntree(T -> L, l + 1);
   prntree(T -> R, l);
}

double evaltree ( parsetree T )
{
   double res;
   tnode *p;

   if (T == NULL) return 0;
   if (T -> type == NUM) return (T -> data).num;
   if (T -> type == OP) {
      p = T -> L;
      if ((T -> data).op == '+') {
         res = 0;
         while (p) {
            res += evaltree(p);
            p = p -> R;
         }
      } else if ((T -> data).op == '*') {
         res = 1;
         while (p) {
            res *= evaltree(p);
            p = p -> R;
         }
      }
      return res;
   }
   return -1;
}

parsetree parse ( )
{
   pstack PS = NULL;
   nstack NS = NULL;
   parsetree PT = pt_init();
   int A, a;

   NS = ns_push(NS, PT);
   PS = ps_push(PS, EXPR);

   a = yylex();
   while (PS != NULL) {
      // printf("Next token: %s\n", yytext);
      A = ps_top(PS); PS = ps_pop(PS);
      switch (A) {
         case EXPR:
            if (a != LP) {
               fprintf(stderr, "*** Expected ( in place of %s\n", yytext);
               exit(4);
            }
            PS = ps_push(PS,RP);
            PS = ps_push(PS,REST);
            PS = ps_push(PS,ARG);
            PS = ps_push(PS,OP);
            PS = ps_push(PS,LP);
            break;
         case OP:
            if ( (a != PLUS) && (a != STAR) ) {
               fprintf(stderr, "*** Expected operator in place of %s\n", yytext);
               exit(5);
            }
            if (a == PLUS) PS = ps_push(PS, PLUS);
            else if (a == STAR) PS = ps_push(PS, STAR);
            break;
         case ARG:
            if (a == LP) PS = ps_push(PS,EXPR);
            else if (a == NUM) PS = ps_push(PS,NUM);
            else {
               fprintf(stderr, "*** Expected argument in place of %s\n", yytext);
               exit(6);
            }
            break;
         case REST:
            if ((a == LP) || (a == NUM)) {
               PS = ps_push(PS,REST);
               PS = ps_push(PS,ARG);
            } else if (a == RP) {
               NS = ns_pop(NS);
            } else {
               fprintf(stderr, "*** Expected argument or end of expression in place of %s\n", yytext);
               exit(7);
            }
            break;
         case PLUS:
         case STAR:
         case NUM:
         case LP:
         case RP: 
            if (A != a) {
               fprintf(stderr, "*** Failed to match terminal symbol of input with top of stack\n");
               exit(8);
            }
            if ( (a == PLUS) || (a == STAR) ) {
               NS = ns_push(NS, pt_addchild(ns_top(NS), OP));
            } else if (a == NUM) {
               pt_addchild(ns_top(NS), NUM);
            }
            a = yylex();
            break;
         default:
            fprintf(stderr, "*** Unknown token %s\n", yytext);
            exit(9);
      }
   }
   return PT;
}

int main ( )
{
   parsetree PT;

   PT = parse();
   printf("Parsing completed successfully!\n");
   prntree(PT->L,0);
   printf("The expression evaluates to %le.\n", evaltree(PT->L));
   exit(0);
}
