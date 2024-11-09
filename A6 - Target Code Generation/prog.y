%{
    #include <iostream>
    #include <cstdlib>
    #include <cstring>
    #include <cstdio>

    int yylex();
    void yyerror(const char* s);

    struct Quad;
    struct Symbol;
    struct Quad_table;
    struct Symbol_table;

    using qPtr = Quad*;
    using sPtr = Symbol*;
    using QTPtr = Quad_table*;
    using STPtr = Symbol_table*;

    struct Symbol {
        char *name;
        bool type; 
        int size;
        int offset;
        Symbol *next;
    };

    struct Quad {
        int idx;
        char* op;
        char* arg1;
        char* arg2;
        char* result;
        Quad *next;
    };

    struct Symbol_table { sPtr head; };
    struct Quad_table   { qPtr head;};

    struct S { int nextlist; };
    struct B { int truelist, falselist; };

    STPtr __GLOBAL_SYMBOL_TABLE__;
    QTPtr __GLOBAL_QUAD_TABLE__;
    int QUAD_CNT = 0;
    int TEMP_CNT = 0;
    int OFFSET = 0;

    STPtr init_ST();
    QTPtr init_QT();
    sPtr init(char *name, int type, int size, int offset);
    qPtr init(int idx, char* op, char* arg1, char* arg2, char* result);

    int getQTSize();
    int nextinstr();
    sPtr find(char* name);
    void backpatch(int idx, int instr);
    void insert(char* name, int type, int size, int offset);
    int emit(char* op, char* arg1, char* arg2, char* result);
    
%}

%union {
    sPtr symb;
    S stmt; B bools;
    char* id; char* op; char* relop;
    int num; int keyword; int punc; int instr;
}

%start START
%type <op> OPER
%type <relop> RELN
%type <symb> EXPR ATOM
%type <stmt> LIST STMT COND LOOP
%type <bools> BOOL
%type <instr> M

%token <id> IDEN
%token <num> NUMB
%token <keyword> set when loop while_
%token <op> ADD SUB MUL DIV MOD
%token <relop> EQ LT GT LE GE NE
%token <punc> LP RP

%%
    START: LIST;

    LIST: STMT { $$ = $1; }
        | STMT M LIST {  $1.nextlist = $2; $$ = $3; }
        ;

    STMT: ASGN { $$.nextlist = 0; }
        | COND { $$ = $1; }
        | LOOP { $$ = $1; }
        ;

    ASGN: LP set IDEN ATOM RP {
            if (find($3) == NULL) {
                insert($3, 1, sizeof($3), OFFSET);
            }
            OFFSET += sizeof($3);
            emit((char*)"=", $4->name, NULL, find($3)->name);
        }
        ;

    COND: LP when BOOL LIST M RP {
            backpatch($3.falselist, $5); // change
            $$ = $4;
        }
        ;

    LOOP: LP loop while_ M BOOL LIST M RP {
            char* instr = (char*)malloc(10 * sizeof(char));
            sprintf(instr, "%d", $4);
            emit((char*)"goto", NULL, NULL, instr);
            backpatch($5.falselist, $7 + 1); // change
            $6.nextlist = $4; // backpatch
            $$.nextlist = $7 + 1;
        }
        ;

    EXPR: LP OPER ATOM ATOM RP {
            char* temp = (char*)malloc(10 * sizeof(char));
            TEMP_CNT++;
            sprintf(temp, "$%d", TEMP_CNT);
            insert(temp, 0, 4, OFFSET);
            OFFSET += 4;

            emit($2, $3->name, $4->name, temp);
            $$ = find(temp);
        }
        ;

    BOOL: LP RELN ATOM ATOM RP {
            emit($2, $3->name, $4->name, (char*)"if");
            $$.falselist = emit((char*)"goto", NULL, NULL, (char*)"-1");
        }
        ;

    ATOM: IDEN {
            sPtr temp = find($1);
            if (temp == NULL) {
                printf("Error: Symbol not found\n");
                exit(EXIT_FAILURE);
            }
            $$ = temp;
        }
        | NUMB {
            sPtr temp = new Symbol();
            char* num = new char[10];
            sprintf(num, "%d", $1);
            $$ = init(num, 0, 4, -1);
        }
        | EXPR { $$ = $1; }
        ;

    OPER: ADD { $$ = $1; }
        | SUB { $$ = $1; }
        | MUL { $$ = $1; }
        | DIV { $$ = $1; }
        | MOD { $$ = $1; }
        ;

    RELN: EQ { $$ = $1; }
        | LT { $$ = $1; }
        | GT { $$ = $1; }
        | LE { $$ = $1; }
        | GE { $$ = $1; }
        | NE { $$ = $1; }
        ;

    M: %empty {
            $$ = nextinstr();
        }
        ;

        
%%
