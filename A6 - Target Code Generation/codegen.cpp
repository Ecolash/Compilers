#include <iostream>
#include <fstream>
#include <cstring>
#include <iomanip>
#include "codegen.h"

extern STPtr __GLOBAL_SYMBOL_TABLE__;
extern QTPtr __GLOBAL_QUAD_TABLE__;
extern QTPtr __TARGET_CODE_TABLE__;

extern int BLOCK_NUM;
extern int QUAD_CNT;
extern int OFFSET;
extern int yylineno;
extern FILE *yyin;

const string sep = string(80, '=');
const string sep2 = string(80, '-');

using namespace std;

sPtr init_symbol(char *name, int type, int size, int offset)
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

QTPtr init_QT()
{
    QTPtr table = new Quad_table();
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

void gen_blocks2()
{
    for (int i = 0; i < 1024; i++)
    for (int j = 0; j < 10; j++)
    if (target_code[i][j] != 0)
    {
        int label = correlation[i];
        int idx = target_code[i][j] - 1;
        if (label == -1) label = ASSEMBLY_CNT + 1;
        qPtr temp = __TARGET_CODE_TABLE__->head;
        for (; temp != NULL; temp = temp->next)
        {
            if (temp->idx == idx)
            {
                temp->result = new char[10];
                sprintf(temp->result, "%d", label + 1);
                break;
            }
        }
    }
}

void insert(char *name, int type, int size, int offset)
{
    sPtr S0 = init_symbol(name, type, size, offset);
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

void printTC()
{
    qPtr quad = __TARGET_CODE_TABLE__->head;
    int lineno = 1;
    while (quad != NULL)
    {
        if (!strcmp(quad->op, "Block"))
        {
            cout << "\nBlock " << BLOCK_NUM++ << endl;
            quad = quad->next;
            continue;
        }
        cout << setw(4) << lineno << " : ";
        if (!strcmp(quad->op, "LDI") || !strcmp(quad->op, "LD")) cout << quad->op << "  " << quad->arg1 << " " << quad->result << endl;
        else if (!strcmp(quad->op, "ST")) cout << quad->op << " " << quad->result << " " << quad->arg1 << endl;
        else if (!strcmp(quad->op, "JMP")) cout << quad->op << " " << quad->result << endl;
        else if (quad->op[0] == 'J') cout << quad->op << " " << quad->arg1 << " " << quad->arg2 << " " << quad->result << endl;
        else cout << quad->op << " " << quad->result << " " << quad->arg1 << " " << quad->arg2 << endl;
        quad = quad->next;
        lineno++;
    }
    cout << endl;
    cout << setw(4) << lineno << " :" << endl;
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
        cout << "No input file provided." << endl;
        cout << "Provide input file name and N (number of registers, optional) as command line arguments." << endl;
        cout << "Usage: " << argv[0] << " <input_file> [N = 5]" << endl;
        exit(1);
    }

    __GLOBAL_SYMBOL_TABLE__ = init_ST();
    __GLOBAL_QUAD_TABLE__ = init_QT();
    __TARGET_CODE_TABLE__ = init_QT();

    if (argc > 2) NUM_REG = atoi(argv[2]);
    freopen("intermediate.out", "w", stdout);
    cout << sep << "\nIntermediate Code " << endl;
    cout << sep2 << "\nSource File: " << argv[1] << endl;
    cout << "Generated at: " << __DATE__ << ", " << __TIME__ << endl;
    cout << sep << endl;
    yyparse();
    BLOCK_NUM = 0; gen_blocks();
    printQT();

    memset(target_code, 0, 1024 * 10 * sizeof(int));
    memset(correlation, -1, 2024 * sizeof(int));

    freopen("target.out", "w", stdout);
    cout << sep << "\nTarget Code " << endl;
    cout << sep2 <<  "\nSource File: " << argv[1] << endl;
    cout << "Generated at: " << __DATE__ << ", " << __TIME__ << endl;
    cout << sep << endl;
    
    target_code_generator();
    BLOCK_NUM = 1; gen_blocks2();
    ASSEMBLY_CNT = 0;
    printTC();
    return 0;
}