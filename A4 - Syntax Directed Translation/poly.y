%{
    #include <stdio.h>
    #include <stdlib.h>

    void yyerror(char* s);
    extern int yylex();

    typedef struct Node node;
    typedef struct Node* NodePtr;

    NodePtr ROOT;
    NodePtr createNode(char name);
    void addChild(NodePtr parent, NodePtr child);
%}

%union {
    char cval;  
    NodePtr exp;
}

%start S
%token <cval> DIGIT ONE ZERO 
%token <cval> XVAR
%token <cval> PLUS MINUS EXP
 
%type <exp> S P T N M X

%%
S   : P
    {
        // printf("S -> P\n");
        $$ = createNode('S');
        addChild($$, $1);
        ROOT = $$;
    }
    | PLUS P
    {
        // printf("S -> + P\n");
        $$ = createNode('S');
        addChild($$, createNode($1));
        addChild($$, $2);
        ROOT = $$;
    }
    | MINUS P 
    {
        // printf("S -> - P\n");
        $$ = createNode('S');
        addChild($$, createNode($1));
        addChild($$, $2);
        ROOT = $$;
    }
    ;

P   : T 
    {
        // printf("P -> T\n");
        $$ = createNode('P');
        addChild($$, $1);
    }
    | T PLUS P 
    {
        // printf("P -> T + P\n");
        $$ = createNode('P');
        addChild($$, $1);
        addChild($$, createNode($2));
        addChild($$, $3);
    }
    | T MINUS P
    {
        // printf("P -> T - P\n");
        $$ = createNode('P');
        addChild($$, $1);
        addChild($$, createNode($2));
        addChild($$, $3);
    }
    ;

T   : ONE 
    {
        // printf("T -> 1\n");
        $$ = createNode('T');
        addChild($$, createNode($1));
    }
    | N 
    {
        // printf("T -> N\n");
        $$ = createNode('T');
        addChild($$, $1);
    }
    | X 
    {
        // printf("T -> X\n");
        $$ = createNode('T');
        addChild($$, $1);
    }
    | N X
    {
        // printf("T -> N X\n");
        $$ = createNode('T');
        addChild($$, $1);
        addChild($$, $2);
    }
    ;

X   : XVAR 
    {
        // printf("X -> x\n");
        $$ = createNode('X');
        addChild($$, createNode($1));
    }
    | XVAR EXP N 
    {
        // printf("X -> x ^ N\n");
        $$ = createNode('X');
        addChild($$, createNode($1));
        addChild($$, createNode($2));
        addChild($$, $3);
    }
    ;

N   : DIGIT 
    {
        // printf("N -> %c\n", $1);
        $$ = createNode('N');
        addChild($$, createNode($1));
    }
    | ONE M 
    {
        // printf("N -> 1 M\n");
        $$ = createNode('N');
        addChild($$, createNode($1));
        addChild($$, $2);
    } 
    | DIGIT M 
    {
        // printf("N -> %c M\n", $1);
        $$ = createNode('N');
        addChild($$, createNode($1));
        addChild($$, $2);
    }
    ;

M   : ZERO 
    {
        // printf("M -> 0\n");
        $$ = createNode('M');
        addChild($$, createNode($1));
    }
    | ONE 
    {
        // printf("M -> 1\n");
        $$ = createNode('M');
        addChild($$, createNode($1));
    }
    | DIGIT 
    {
        // printf("M -> %c\n", $1);
        $$ = createNode('M');
        addChild($$, createNode($1));
    }
    | ZERO M 
    {
        // printf("M -> 0 M\n");
        $$ = createNode('M');
        addChild($$, createNode($1));
        addChild($$, $2);
    }
    | ONE M 
    {
        // printf("M -> 1 M\n");
        $$ = createNode('M');
        addChild($$, createNode($1));
        addChild($$, $2);
    }
    | DIGIT M 
    {
        // printf("M -> %c M\n", $1);
        $$ = createNode('M');
        addChild($$, createNode($1));
        addChild($$, $2);
    }
    ;
%%
