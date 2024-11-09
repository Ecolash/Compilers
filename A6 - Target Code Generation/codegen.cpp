#include <iostream>
#include <fstream>
#include <cstring>
#include <iomanip>

using namespace std;

#include "y.tab.c"
#include "lex.yy.c"

extern FILE *yyin;
extern int yylineno;
extern int block[1 << 15];

extern STPtr __GLOBAL_SYMBOL_TABLE__;
extern QTPtr __GLOBAL_QUAD_TABLE__;
extern QTPtr 
extern int BLOCK_NUM;
extern int QUAD_CNT;
extern int TEMP_currline;
extern int OFFSET;


sPtr init(char *name, int type, int size, int offset)
{
    sPtr S0 = new Symbol();
    S0->name = strdup(name);
    S0->next = NULL;
    S0->size = size;
    S0->type = type;
    S0->offset = offset;
    return S0;
}

qPtr init(char *op, char *arg1, char *arg2, char *result)
{
    qPtr Q0 = new Quad();
    Q0->idx = QUAD_CNT++;
    Q0->op = op;
    Q0->arg1 = arg1;
    Q0->arg2 = arg2;
    Q0->result = result;
    Q0->next = NULL;
    return Q0;
}

STPtr init_ST()
{
    STPtr table = new Symbol_table();
    table->head = NULL;
    return table;
}

void gen_blocks()
{
    qPtr quad = __GLOBAL_QUAD_TABLE__->head;
    for (; quad != NULL; quad = quad->next)
    {
        if (!strcmp(quad->op, "goto")) block[atoi(quad->result)] = 1;
        else continue;
    }
}

QTPtr init_QT()
{
    QTPtr table = new Quad_table();
    table->head = NULL;
    return table;
}

void insert(char *name, int type, int size, int offset)
{
    sPtr S0 = init(name, type, size, offset);
    sPtr *temp = &__GLOBAL_SYMBOL_TABLE__->head;
    while (*temp != NULL) temp = &(*temp)->next;
    *temp = S0;
}

sPtr find(char *name)
{
    sPtr temp = __GLOBAL_SYMBOL_TABLE__->head;
    while (temp != NULL)
    {
        if (!strcmp(temp->name, name)) return temp;
        temp = temp->next;
    }
    return NULL;
}

int getQTSize()
{
    int size = 0;
    for (qPtr temp = __GLOBAL_QUAD_TABLE__->head; temp != NULL; temp = temp->next)
    {
        size = size + 1;
        if (temp->result and !strcmp(temp->result, "if")) temp = temp->next;
    }
    return size;
}

int emit(char *op, char *arg1, char *arg2, char *result)
{
    qPtr Q0 = init(op, arg1, arg2, result);
    qPtr *temp = &__GLOBAL_QUAD_TABLE__->head;
    while (*temp != NULL) temp = &(*temp)->next;
    *temp = Q0;
    return Q0->idx;
}

int nextinstr()
{
    int instrno = getQTSize() + 1;
    return instrno;
}

void backpatch(int idx, int instr)
{
    qPtr temp = __GLOBAL_QUAD_TABLE__->head;
    while (temp != NULL)
    {
        if (temp->idx == idx)
        {
            char *instr_str = new char[10];
            sprintf(instr_str, "%d", instr);
            temp->result = instr_str;
        }
        temp = temp->next;
    }
}

void printQT(int currline = 1)
{
    qPtr quad = __GLOBAL_QUAD_TABLE__->head;
    while (quad != NULL)
    {
        if (currline == 1) cout << "Block " << ++BLOCK_NUM << endl;
        else if (block[currline] == 1) cout << "\nBlock " << ++BLOCK_NUM << endl;
        cout << setw(4) << currline << " :\t";

        if (!strcmp(quad->result, "if"))
        {
            cout << "ifFalse (";
            cout << quad->arg1 << " " << (strcmp(quad->op, "=") == 0 ? "==" : (strcmp(quad->op, "/=") == 0 ? "!=" : quad->op)) << " " << quad->arg2;
            cout << ") goto " << quad->next->result << endl;
            cout << "\nBlock " << ++BLOCK_NUM << endl;
            quad = quad->next->next;
        }

        else if (!strcmp(quad->op, "goto"))
        {
            cout << "goto " << quad->result << endl;
            quad = quad->next;
        }
        else
        {
            cout << quad->result << " = " << quad->arg1;
            if (strcmp(quad->op, "=") != 0) cout << " " << quad->op << " " << quad->arg2;
            cout << endl;
            quad = quad->next;
        }
        currline++;
    }
    cout << setw(4) << currline << " :\t";
    cout << "EOP" << endl;
    return;
}

void yyerror(const char* s)
{
    int line = yylineno;
    cerr << "!!! ERROR: " << s << " at line " << line << endl;
    return;
}
int main(int argc, char *argv[])
{
    yyin = stdin;
    if (argc > 1)
    {
        FILE *file = fopen(argv[1], "r");
        if (!file) fprintf(stderr, "Error opening file: %s\n", argv[1]);
        if (!file) exit(1);
        yyin = file;
    }
    else 
    {
        cout 
        cout << "Usage: " << argv[0] << " <input_file> [N]" << endl;
        exit(1);
    }

    int N = 5; 
    if (argc > 2)
    if (argc > 2) N = atoi(argv[2]);


    freopen("intermediate.out", "w", stdout);
    __GLOBAL_SYMBOL_TABLE__ = init_ST();
    __GLOBAL_QUAD_TABLE__ = init_QT();
    yyparse();
    gen_blocks();
    printQT();

    freopen("target.out", "w", stdout);

    return 0;
}