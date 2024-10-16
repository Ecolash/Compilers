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

    typedef struct expr
    {
        int type;
        int val;
    } expr;

    int temp() {
        char *temp = (char *)malloc(10);
        sprintf(temp, "$t%d", ++temp_cnt);
        add(temp);
        return get(temp);
    }
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

EXPRSTMT: 
    EXPR 
    { 
        $$ = $1.type;
        regP = 2;
    };

EXPR: 
    '(' OP ARG ARG ')' 
    { 
        arg1 = $3.type;
        arg2 = $4.type;
        if (arg1 == 1) fprintf(TAC, "\tR[0] = MEM[%d];\n", $3.memloc);
        if (arg2 == 1) fprintf(TAC, "\tR[1] = MEM[%d];\n", $4.memloc);

        // if (strcmp($2, "^") == 0) {
            switch (arg1) {
            case 1: switch (arg2) {
                case 1:
                    if (regP >= 12)
                    {
                        $$.type = 1;
                        $$.val = temp();
                        if (strcmp($2, "^") == 0) fprintf(TAC, "\tR[0] = pwr(R[0], R[1]);\n");
                        else fprintf(TAC, "\tR[0] = R[0] %s R[1];\n", $2);
                        fprintf(TAC, "\tMEM[%d] = R[0];\n", $$.val);
                    }
                    else
                    {
                        $$.type = 2;
                        $$.val = regP++;
                        if (strcmp($2, "^") == 0) fprintf(TAC, "\tR[%d] = pwr(R[0], R[1]);\n", $$.val);
                        else fprintf(TAC, "\tR[%d] = R[0] %s R[1];\n", $$.val, $2);
                    }
                    break;
                case 2: 
                    if (regP >= 12)
                    {
                        $$.type = 1;
                        $$.val = temp();
                        if (strcmp($2, "^") == 0) fprintf(TAC, "\tR[0] = pwr(R[0],%d);\n", $4.val);
                        else fprintf(TAC, "\tR[0] = R[0] %s %d;\n", $2, $4.val);
                        fprintf(TAC, "\tMEM[%d] = R[0];\n", $$.val);
                    }
                    else
                    {
                        $$.type = 2;
                        $$.val = regP++;
                        if (strcmp($2, "^") == 0) fprintf(TAC, "\tR[%d] = pwr(R[0],%d);\n", $$.val, $4.val);
                        else fprintf(TAC, "\tR[%d] = R[0] %s %d;\n", $$.val, $2, $4.val);
                    }
                    break;
                case 3: 
                    $$.type = 2;
                    $$.val = $4.val;
                    if (strcmp($2, "^") == 0) fprintf(TAC, "\tR[%d] = pwr(R[0], R[%d]);\n", $4.val, $4.val);
                    else fprintf(TAC, "\tR[%d] = R[0] %s R[%d];\n", $4.val, $2, $4.val);
                    regP = $4.val + 1;
                    break;
            }
            break;
            case 2: switch (arg2) {
                case 1: 
                    if (regP >= 12)
                    {
                        $$.type = 1;
                        $$.val = temp();
                        if (strcmp($2, "^") == 0) fprintf(TAC, "\tR[0] = pwr(%d, R[1]);\n", $3.val);
                        else fprintf(TAC, "\tR[0] = %d %s R[1];\n", $3.val, $2);
                        fprintf(TAC, "\tMEM[%d] = R[0];\n", $$.val);
                    }
                    else
                    {
                        $$.type = 2;
                        $$.val = regP++;
                        if (strcmp($2, "^") == 0) fprintf(TAC, "\tR[%d] = pwr(%d, R[1]);\n", $$.val, $3.val);
                        else fprintf(TAC, "\tR[%d] = %d %s R[1];\n", $$.val, $3.val, $2);
                    }
                    break;
                case 2: 
                    if (regP >= 12)
                    {
                        $$.type = 1;
                        $$.val = temp();
                        if (strcmp($2, "^") == 0) fprintf(TAC, "\tR[0] = pwr(%d,%d);\n", $3.val, $4.val);
                        else fprintf(TAC, "\tR[0] = %d %s %d;\n", $3.val, $2, $4.val);
                        fprintf(TAC, "\tMEM[%d] = R[0];\n", $$.val);
                    }
                    else
                    {
                        $$.type = 2;
                        $$.val = regP++;
                        if (strcmp($2, "^") == 0) fprintf(TAC, "\tR[%d] = pwr(%d,%d);\n", $$.val, $3.val, $4.val);
                        else fprintf(TAC, "\tR[%d] = %d %s %d;\n", $$.val, $3.val, $2, $4.val);
                    }
                    break;
                case 3: 
                    $$.type = 2;
                    $$.val = $4.val;
                    if (strcmp($2, "^") == 0) fprintf(TAC, "\tR[%d] = pwr(%d, R[%d]);\n", $4.val, $3.val, $4.val);
                    else fprintf(TAC, "\tR[%d] = %d %s R[%d];\n", $4.val, $3.val, $2, $4.val);
                    regP = $4.val + 1;
                    break;
            }
            break;
            case 3: switch (arg2) {
                case 1: 
                    $$.type = 2;
                    $$.val = $3.val;
                    if (strcmp($2, "^") == 0) fprintf(TAC, "\tR[%d] = pwr(R[%d], R[1]);\n", $3.val, $3.val);
                    else fprintf(TAC, "\tR[%d] = R[%d] %s R[1];\n", $3.val, $3.val, $2);
                    regP = $3.val + 1;
                    break;
                case 2: 
                    $$.type = 2;
                    $$.val = $3.val;
                    if (strcmp($2, "^") == 0) fprintf(TAC, "\tR[%d] = pwr(R[%d],%d);\n", $3.val, $3.val, $4.val);
                    else fprintf(TAC, "\tR[%d] = R[%d] %s %d;\n", $3.val, $3.val, $2, $4.val);
                    regP = $3.val + 1;
                    break;
                case 3: 
                    $$.type = 2;
                    $$.val = $3.val;
                    if (strcmp($2, "^") == 0) fprintf(TAC, "\tR[%d] = pwr(R[%d], R[%d]);\n", $3.val, $3.val, $4.val);
                    else fprintf(TAC, "\tR[%d] = R[%d] %s R[%d];\n", $3.val, $3.val, $2, $4.val);
                    regP = $3.val + 1;
                    break;
            }
            break;
            }
        // } else {
        //     switch (arg1) {
        //     case 1: switch (arg2) {
        //         case 1: fprintf(TAC, "\tR[%d] = R[0] %s R[1];\n", $$ = regP, $2); regP++; break;
        //         case 2: fprintf(TAC, "\tR[%d] = R[0] %s %d;\n", $$ = regP, $2, $4.val); regP++; break;
        //         case 3: fprintf(TAC, "\tR[%d] = R[0] %s R[%d];\n", $$ = $4.val, $2, $4.val); regP = $4.val + 1; break;
        //     }
        //     break;
        //     case 2: switch (arg2) {
        //         case 1: fprintf(TAC, "\tR[%d] = %d %s R[1];\n", $$ = regP, $3.val, $2); regP++; break;
        //         case 2: fprintf(TAC, "\tR[%d] = %d %s %d;\n", $$ = regP, $3.val, $2, $4.val); regP++; break;
        //         case 3: fprintf(TAC, "\tR[%d] = %d %s R[%d];\n", $$ = $4.val, $3.val, $2, $4.val); regP = $4.val + 1; break;
        //     }
        //     break;
        //     case 3: switch (arg2) {
        //         case 1: fprintf(TAC, "\tR[%d] = R[%d] %s R[1];\n", $$ = $3.val, $3.val, $2); regP = $3.val + 1; break;
        //         case 2: fprintf(TAC, "\tR[%d] = R[%d] %s %d;\n", $$ = $3.val, $3.val, $2, $4.val); regP = $3.val + 1; break;
        //         case 3: fprintf(TAC, "\tR[%d] = R[%d] %s R[%d];\n", $$ = $3.val, $3.val, $2, $4.val); regP = $3.val + 1; break;
        //     }
        //     break;
        //     }
        // }
    };

STMT: 
      SETSTMT  { fprintf(TAC, "\tmprn(MEM,%d);\n", $1);}
    | EXPRSTMT { fprintf(TAC, "\teprn(R,%d);\n", $1);};

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
        fprintf(TAC, "\tMEM[%d] = R[%d];\n", loc, $4.val);
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
        if ($1.type == 1) {
            $$.type = 1;
            $$.val = -1;
            $$.memloc = $1.val;
        } 
        else if ($1.type == 2) {
            $$.type = 3;
            $$.val = $1.val;
        }
    };

OP: 
      '+' { $$ = "+"; }
    | '-' { $$ = "-"; }
    | '*' { $$ = "*"; }
    | '/' { $$ = "/"; }
    | '%' { $$ = "%"; }
    | '^' { $$ = "^"; };
%% 