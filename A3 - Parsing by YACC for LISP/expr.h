/*=========================================//
NAME - TUHIN MONDAL
ROLL NUMBER - 22CS10087
//=========================================*/

#ifndef HEADER_
#define HEADER_

/*=========================================//
Symbol Node for Symbol Table
//=========================================*/
typedef struct Symbol
{
    int value;
    char *name;
    struct Symbol *next;
} Symbol;

typedef Symbol *SYM_PTR;

typedef struct SymbolTable
{
    SYM_PTR head;
    int size;
} SymbolTable;

typedef SymbolTable *SYMBOL_TABLE;

/*=========================================//
Function Prototypes for Symbol Table Functions
//=========================================*/

SYMBOL_TABLE init();                                 
void add(SYMBOL_TABLE table, char *name, int value); 
int get(SYMBOL_TABLE table, char *name);             
void set(SYMBOL_TABLE table, char *name, int value); 
void free_table(SYMBOL_TABLE table);                 
SYM_PTR find(SYM_PTR current, char *name);

/*=========================================//
Expression Node for Expression Parse Table
//=========================================*/
typedef union NodeInfo {
    char *op;
    int num;
    char *id;
} NodeInfo;

typedef struct TreeNode {
    int type; /* 0 for NUM, 1 for ID, 2 for OP */  
    NodeInfo data;         
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;

typedef TreeNode *EX_PTR;

/*=========================================//
Function Prototypes for Parse Tree Functions
//=========================================*/

EX_PTR initNLeaf(int num);
EX_PTR initIDLeaf(char *id);
EX_PTR initOPNode(char *op, EX_PTR left, EX_PTR right);
int evaluate(SYMBOL_TABLE table, EX_PTR node);
void free_(EX_PTR node);

#endif
