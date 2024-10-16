/*=========================================//
NAME - TUHIN MONDAL
ROLL NUMBER - 22CS10087
//=========================================*/

%{
    #include <stdio.h>
    #include <stdlib.h>
    #include <stdbool.h>
    #include <string.h>

    extern void yyerror(const char* s);
    extern int yylex();

    FILE *TAC;
    unsigned int regP = 2;
    unsigned int memP = 0;
    unsigned int temp_cnt = 0;
    int arg1, arg2;

    typedef struct node {
        char* id;
        int offset;
    } Node;

    Node SymbolTable[5000];
    unsigned int size = 0;

    void add(char* id);
    int get(char* id);
    void update(char *id);

    typedef struct arg
    {
        int type;
        int val;
        int memloc;
    } arg;

    typedef struct expr
    {
        int type;
        int val;
    } expr;

    int temp();
    void gen_expr(int arg1, int arg2, char* op, expr* result, arg arg3, arg arg4);
    void set_id_num(char* id, int num, int* result);
    void set_id_expr(char* id, expr expr_val, int* result);
    void set_id_id(char* id1, char* id2, int* result);

    void set_arg_id(arg* argument, char* id);
    void set_arg_num(arg* argument, int num);
    void set_arg_expr(arg* argument, expr expr_val);
%}

%union { 
    int num; 
    char* id; 
    int exp; 
    arg info;
    expr einfo;
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
%type<einfo> EXPR
%type<info> ARG
%type<id> OP

%% 
//------------------------------------------------
// LIST OF PRODUCTION RULES & ACTIONS
//------------------------------------------------
PROGRAM: 
    STMT PROGRAM { return 0; }
    | STMT       { return 0; }
    ;

EXPRSTMT:  EXPR  { $$ = $1.type; regP = 2; };

EXPR:  '(' OP ARG ARG ')' {  gen_expr($3.type, $4.type, $2, &$$, $3, $4);};

STMT: 
      SETSTMT  { fprintf(TAC, "\tmprn(MEM,%d);\n", $1);}
    | EXPRSTMT { fprintf(TAC, "\teprn(R,%d);\n", $1);};

SETSTMT: 
      '(' SET ID NUM ')'  { set_id_num($3, $4, &$$); }
    | '(' SET ID EXPR ')' { set_id_expr($3, $4, &$$);}
    | '(' SET ID ID ')'   { set_id_id($3, $4, &$$);  };

ARG: 
       ID   { set_arg_id(&$$, $1);}
    | NUM   { set_arg_num(&$$, $1);}
    | EXPR  { set_arg_expr(&$$, $1);};

OP: 
      '+' { $$ = "+"; }
    | '-' { $$ = "-"; }
    | '*' { $$ = "*"; }
    | '/' { $$ = "/"; }
    | '%' { $$ = "%"; }
    | '^' { $$ = "^"; };
%%
