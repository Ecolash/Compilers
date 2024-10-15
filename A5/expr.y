/*=========================================//
NAME - TUHIN MONDAL
ROLL NUMBER - 22CS10087
//=========================================*/

%{
    #include <stdio.h>
    #include <stdlib.h>
    #include <stdbool.h>

    extern void yyerror(const char* s);
    extern int yylex();

    FILE *TAC;

    unsigned int regP = 2;
    unsigned int memP = 0;
    unsigned int temp_cnt = 0;
    bool reg[12] = {};
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
%}

%union { 
    int num; 
    char* id; 
    int exp; 
    arg info;
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
%type<exp> EXPR
%type<info> ARG
%type<id> OP

%% 
//------------------------------------------------
// LIST OF PRODUCTION RULES & ACTIONS
//------------------------------------------------
PROGRAM: 
    STMT PROGRAM { }
    | STMT       { }
    ;

EXPRSTMT: 
    EXPR 
    { 
        $$ = $1;
        regP = 2;
    };

EXPR: 
    '(' OP ARG ARG ')' 
    { 
        arg1 = $3.type;
        arg2 = $4.type;
        if (arg1 == 1) fprintf(TAC, "\tR[0] = MEM[%d];\n", $3.memloc);
        if (arg2 == 1) fprintf(TAC, "\tR[1] = MEM[%d];\n", $4.memloc);

        if (strcmp($2, "^") == 0) {
            switch (arg1) {
            case 1: switch (arg2) {
                case 1: fprintf(TAC, "\tR[%d] = pwr(R[0], R[1]);\n", $$ = regP); regP++; break;
                case 2: fprintf(TAC, "\tR[%d] = pwr(R[0], %d);\n", $$ = regP, $4.val); regP++; break;
                case 3: fprintf(TAC, "\tR[%d] = pwr(R[0], R[%d]);\n", $$ = $4.val, $4.val); regP = $4.val + 1; break;
            }
            break;
            case 2: switch (arg2) {
                case 1: fprintf(TAC, "\tR[%d] = pwr(%d, R[1]);\n", $$ = regP, $3.val); regP++; break;
                case 2: fprintf(TAC, "\tR[%d] = pwr(%d, %d);\n", $$ = regP, $3.val, $4.val); regP++; break;
                case 3: fprintf(TAC, "\tR[%d] = pwr(%d, R[%d]);\n", $$ = $4.val, $3.val, $4.val);  regP = $4.val + 1; break;
            }
            break;
            case 3: switch (arg2) {
                case 1: fprintf(TAC, "\tR[%d] = pwr(R[%d], R[1]);\n", $$ = $3.val, $3.val); regP = $3.val + 1; break;
                case 2: fprintf(TAC, "\tR[%d] = pwr(R[%d], %d);\n", $$ = $3.val, $3.val, $4.val); regP = $3.val + 1; break;
                case 3: fprintf(TAC, "\tR[%d] = pwr(R[%d], R[%d]);\n", $$ = $3.val, $3.val, $4.val); regP = $3.val + 1; break;
            }
            break;
            }
        } else {
            switch (arg1) {
            case 1: switch (arg2) {
                case 1: fprintf(TAC, "\tR[%d] = R[0] %s R[1];\n", $$ = regP, $2); regP++; break;
                case 2: fprintf(TAC, "\tR[%d] = R[0] %s %d;\n", $$ = regP, $2, $4.val); regP++; break;
                case 3: fprintf(TAC, "\tR[%d] = R[0] %s R[%d];\n", $$ = $4.val, $2, $4.val); regP = $4.val + 1; break;
            }
            break;
            case 2: switch (arg2) {
                case 1: fprintf(TAC, "\tR[%d] = %d %s R[1];\n", $$ = regP, $3.val, $2); regP++; break;
                case 2: fprintf(TAC, "\tR[%d] = %d %s %d;\n", $$ = regP, $3.val, $2, $4.val); regP++; break;
                case 3: fprintf(TAC, "\tR[%d] = %d %s R[%d];\n", $$ = $4.val, $3.val, $2, $4.val); regP = $4.val + 1; break;
            }
            break;
            case 3: switch (arg2) {
                case 1: fprintf(TAC, "\tR[%d] = R[%d] %s R[1];\n", $$ = $3.val, $3.val, $2); regP = $3.val + 1; break;
                case 2: fprintf(TAC, "\tR[%d] = R[%d] %s %d;\n", $$ = $3.val, $3.val, $2, $4.val); regP = $3.val + 1; break;
                case 3: fprintf(TAC, "\tR[%d] = R[%d] %s R[%d];\n", $$ = $3.val, $3.val, $2, $4.val); regP = $3.val + 1; break;
            }
            break;
            }
        }
    };

STMT: 
      SETSTMT  { fprintf(TAC, "\tmprn(MEM, %d);\n\n", $1);}
    | EXPRSTMT { fprintf(TAC, "\teprn(R, %d);\n\n", $1);};

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
        fprintf(TAC, "\tMEM[%d] = R[%d];\n", loc, $4);
        for(int i = 0; i < 12; i++) reg[i] = false;
        regP = 2;
        $$ = loc;        
    };
    | '(' SET ID ID ')' 
    { 
        update($3);
        int loc1 = get($3);
        int loc2 = get($4);
        fprintf(TAC, "\tR[0] = MEM[%d];\n", loc2);
        fprintf(TAC, "\tMEM[%d] = R[0];\n", loc1);
        $$ = loc1;
    }


ARG: 
    ID   
    { 
        int loca = get($1);
        $$.type = 1;
        $$.val = -1;
        $$.memloc = loca;
    };

    | NUM  
    { 
        $$.type = 2;
        $$.val = $1;
    };
    | EXPR 
    { 
        $$.type = 3;
        $$.val = $1;
    };

OP: 
      '+' { $$ = "+"; }
    | '-' { $$ = "-"; }
    | '*' { $$ = "*"; }
    | '/' { $$ = "/"; }
    | '%' { $$ = "%"; }
    | '^' { $$ = "^"; };

%% 

