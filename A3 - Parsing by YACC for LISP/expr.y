/*=========================================//
NAME - TUHIN MONDAL
ROLL NUMBER - 22CS10087
//=========================================*/

%{
    #include <stdio.h>
    #include <stdlib.h>
    #include "expr.h"

    extern void yyerror(const char* s);
    extern SYMBOL_TABLE T;
    extern int yylex();
%}

%union { 
    int num; 
    char* id; 
    TreeNode* exp; 
}

//------------------------------------------------
// LIST OF TERMINALS
//------------------------------------------------
%token SET 
%token<num> NUM
%token<id> ID
//------------------------------------------------
// LIST OF NON-TERMINALS
//------------------------------------------------
%start PROGRAM
%type<exp> STMT SETSTMT PROGRAM EXPRSTMT
%type<exp> ARG EXPR
%type<id> OP

%% 
//------------------------------------------------
// LIST OF PRODUCTION RULES & ACTIONS
//------------------------------------------------
PROGRAM: 
    STMT PROGRAM { return 0; }
    | STMT       { return 0; }
    ;

EXPRSTMT: 
    EXPR { 
        int result = evaluate(T, $1);
        printf("Stand alone expression E = %d\n", result);
        free_($1);
    };

EXPR: 
    '(' OP ARG ARG ')' { $$ = initOPNode($2, $3, $4); };

STMT: 
    SETSTMT { ; }
    | EXPRSTMT { ; };

SETSTMT: 
    '(' SET ID NUM ')' { 
        set(T, $3, $4);
        printf("%s := %d\n", $3, $4);
    }
    | '(' SET ID EXPR ')' { 
        int value = evaluate(T, $4);
        set(T, $3, value);
        free_($4);
        printf("%s := %d\n", $3, value);
    };
    | '(' SET ID ID ')' { 
        int value = get(T, $4); 
        set(T, $3, value); 
        printf("%s := %d\n", $3, value); 
    }

ARG: 
      ID { $$ = initIDLeaf($1); }
    | NUM { $$ = initNLeaf($1); }
    | EXPR { $$ = $1; };

OP: 
      '+' { $$ = "+"; }
    | '-' { $$ = "-"; }
    | '*' { $$ = "*"; }
    | '/' { $$ = "/"; }
    | '%' { $$ = "%"; }
    | '^' { $$ = "^"; };

%% 

