#include <math.h>
#include "lex.yy.c"
#include "y.tab.c"

#define PROG 1000
#define STMT 1001
#define ARG 1002

node *root;

node *addnodeKWD ( int kwd )
{
   node *p;

   p = (node *)malloc(sizeof(node));
   p -> type = kwd;
   p -> C[0] = p -> C[1] = p -> C[2] = p -> C[3] = NULL;
   return p;
}

node *addnodePUNC ( int punc )
{
   node *p;

   p = (node *)malloc(sizeof(node));
   p -> type = punc;
   p -> C[0] = p -> C[1] = p -> C[2] = p -> C[3] = NULL;
   return p;
}

node *addnodeNUM ( double val )
{
   node *p;

   p = (node *)malloc(sizeof(node));
   p -> type = NUM;
   p -> value = val;
   p -> C[0] = p -> C[1] = p -> C[2] = p -> C[3] = NULL;
   return p;
}

node *addnodeP ( node *S, node *P1 )
{
   root = (node *)malloc(sizeof(node));
   root -> type = PROG;
   root -> C[0] = S;
   root -> C[1] = P1;
   root -> C[2] = root -> C[3] = NULL;
   return root;
}

node *addnodeS ( int kwd, node *A )
{
   node *S;

   S = (node *)malloc(sizeof(node));
   S -> type = STMT;
   S -> C[0] = addnodeKWD(kwd);
   S -> C[1] = addnodePUNC(LP);
   S -> C[2] = A;
   S -> C[3] = addnodePUNC(RP);
   return S;
}

node *addnodeA ( double num, node *A1 )
{
   node *A;

   A = (node *)malloc(sizeof(node));
   A -> type = ARG;
   A -> C[0] = addnodeNUM(num);
   A -> C[3] = NULL;
   if (A1 == NULL) {
      A -> C[1] = A -> C[2] = NULL;
   } else {
      A -> C[1] = addnodePUNC(SEP);
      A -> C[2] = A1;
   }
   return A;
}

void eval ( node *p )
{
   double newpartial;

   if (p -> type == PROG) {
      eval(p -> C[0]);
      if (p -> C[1] != NULL) eval(p -> C[1]);
   } else if (p -> type == STMT) {
      if (p -> C[0] -> type == MAX) {
         p -> C[2] -> op = MAX;
         p -> C[2] -> partial = -INFINITY;
         eval(p -> C[2]);
         p -> count = p -> C[2] -> count;
         p -> value = p -> C[2] -> value;
         printf("Maximum of %d items is %lf\n", p -> count, p -> value);
      } else if (p -> C[0] -> type == MIN) {
         p -> C[2] -> op = MIN;
         p -> C[2] -> partial = INFINITY;
         eval(p -> C[2]);
         p -> count = p -> C[2] -> count;
         p -> value = p -> C[2] -> value;
         printf("Minimum of %d items is %lf\n", p -> count, p -> value);
      } else if (p -> C[0] -> type == AVG) {
         p -> C[2] -> op = AVG;
         p -> C[2] -> partial = 0;
         eval(p -> C[2]);
         p -> count = p -> C[2] -> count;
         p -> value = p -> C[2] -> value / p -> count;
         printf("Average of %d items is %lf\n", p -> count, p -> value);
      }
   } else if (p -> type == ARG) {
      if (p -> op == MAX) {
         newpartial = (p -> C[0] -> value > p -> partial) ? p -> C[0] -> value : p -> partial;
      } else if (p -> op == MIN) {
         newpartial = (p -> C[0] -> value < p -> partial) ? p -> C[0] -> value : p -> partial;
      } else if (p -> op == AVG) {
         newpartial = p -> partial + p -> C[0] -> value;
      }
      if (p -> C[2] == NULL) {
         p -> value = newpartial;
         p -> count = 1;
      } else {
         p -> C[2] -> op = p -> op;
         p -> C[2] -> partial = newpartial;
         eval(p -> C[2]);
         p -> value = p -> C[2] -> value;
         p -> count = 1 + p -> C[2] -> count;
      }
   }
}

int main ()
{
   yyparse();
   eval(root);
   exit(0);
}
