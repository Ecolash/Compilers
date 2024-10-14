/*=========================================//
NAME - TUHIN MONDAL
ROLL NUMBER - 22CS10087
//=========================================*/

%{
    #include <stdio.h>
    #include <stdlib.h>
    #include <stdbool.h>
    #include "expr.h"

    extern void yyerror(const char* s);
    extern int yylex();

    FILE *TAC;
    bool R0, R1;
    int A0, A1;
    unsigned int regP = 2;
    unsigned int memP = 0;
    unsigned int temp_cnt = 0;
    R0 = R1 = false;
    A0 = A1 = 0;

    typedef struct node Node;
    Node SymbolTable[5000];
    unsigned int size = 0;

    void add(char* id);
    int get(char* id);
    void update(char *id);

    

%}

%union { 
    int num; 
    char* id; 
    int exp; 
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
    EXPR 
    { 
        $$ = $1;
    };

EXPR: 
    '(' OP ARG ARG ')' 
    { 
        R0 = R1 = false;
    };

STMT: 
    SETSTMT 
    { 
        fprintf(TAC, "\tmprn(MEM, %d);\n", $1);
    }

    | EXPRSTMT { fprintf(TAC, "\teprn(R, %d);\n", $1); };

SETSTMT: 
    '(' SET ID NUM ')' 
    { 
        update($3);
        int loc = get($3);
        fprintf(TAC, "\tMEM[%d] = %d;\n", loc, $4);
        $$ = loc;
    }
    | '(' SET ID EXPR ')' 
    { 
        update($3);
        int loc = get($3);
        fprintf(TAC, "\tMEM[%d] = R[%d;]\n", loc, $4);
        $$ = loc;        
    };
    | '(' SET ID ID ')' 
    { 
        update($3);
        int loc1 = get($3);
        int loc2 = get($4);
        fprintf(TAC, "\tMEM[%d] = MEM[%d];\n", loc1, loc2);
        $$ = loc1;
    }


ARG: 
    ID   
    { 
        int loca = get($1);
        if (R1) exit(1);
        fprintf(TAC, "\tR[%d] = MEM[%d];\n", R0 ? 1 : 0, loca);
        R0 ? (R1 = true) : (R0 = true);
        $$ = R0 ? 1 : 0;
    };

    | NUM  
    { 
        int loca = get($1);
        if (R1) exit(1);
        R0 ? (R1 = true) : (R0 = true);
        R0 ? (R1 = true) : (R0 = true);
        $$ = R0 ? 1 : 0;  
    };
    | EXPR { $$ = $1; };

OP: 
      '+' { $$ = "+"; }
    | '-' { $$ = "-"; }
    | '*' { $$ = "*"; }
    | '/' { $$ = "/"; }
    | '%' { $$ = "%"; }
    | '^' { $$ = "^"; };

%% 

