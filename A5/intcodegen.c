#include "y.tab.c"
#include "lex.yy.c"

extern FILE *TAC;
extern FILE *yyin;
extern void yyerror(const char *s);
extern unsigned int size;
extern unsigned int regP, memP, temp_cnt;

typedef struct node Node;
typedef struct expr expr;
typedef struct arg arg;
extern Node SymbolTable[5000];


void gen_expr(int arg1, int arg2, char* op, expr* ans, arg arg3, arg arg4) {
    if (arg1 == 1) fprintf(TAC, "\tR[0] = MEM[%d];\n", arg3.memloc);
    if (arg2 == 1) fprintf(TAC, "\tR[1] = MEM[%d];\n", arg4.memloc);

    switch (arg1)
    {
    case 1:
        switch (arg2)
        {
        case 1:
            if (regP >= 12)
            {
                ans->type = 1, ans->val = temp();
                if (op[0] == '^') fprintf(TAC, "\tR[0] = pwr(R[0], R[1]);\n");
                else fprintf(TAC, "\tR[0] = R[0] %s R[1];\n", op);
                fprintf(TAC, "\tMEM[%d] = R[0];\n", ans->val);
            }
            else
            {
                ans->type = 2, ans->val = regP++;
                if (op[0] == '^') fprintf(TAC, "\tR[%d] = pwr(R[0], R[1]);\n", ans->val);
                else fprintf(TAC, "\tR[%d] = R[0] %s R[1];\n", ans->val, op);
            }
            break;
        case 2:
            if (regP >= 12)
            {
                ans->type = 1, ans->val = temp();
                if (op[0] == '^') fprintf(TAC, "\tR[0] = pwr(R[0],%d);\n", arg4.val);
                else fprintf(TAC, "\tR[0] = R[0] %s %d;\n", op, arg4.val);
                fprintf(TAC, "\tMEM[%d] = R[0];\n", ans->val);
            }
            else
            {
                ans->type = 2, ans->val = regP++;
                if (op[0] == '^') fprintf(TAC, "\tR[%d] = pwr(R[0],%d);\n", ans->val, arg4.val);
                else fprintf(TAC, "\tR[%d] = R[0] %s %d;\n", ans->val, op, arg4.val);
            }
            break;
        case 3:
            ans->type = 2, ans->val = arg4.val;
            if (op[0] == '^') fprintf(TAC, "\tR[%d] = pwr(R[0], R[%d]);\n", arg4.val, arg4.val);
            else fprintf(TAC, "\tR[%d] = R[0] %s R[%d];\n", arg4.val, op, arg4.val);
            regP = arg4.val + 1;
            break;
        }
        break;
    case 2:
        switch (arg2)
        {
        case 1:
            if (regP >= 12)
            {
                ans->type = 1, ans->val = temp();
                if (op[0] == '^') fprintf(TAC, "\tR[0] = pwr(%d, R[1]);\n", arg3.val);
                else fprintf(TAC, "\tR[0] = %d %s R[1];\n", arg3.val, op);
                fprintf(TAC, "\tMEM[%d] = R[0];\n", ans->val);
            }
            else
            {
                ans->type = 2, ans->val = regP++;
                if (op[0] == '^') fprintf(TAC, "\tR[%d] = pwr(%d, R[1]);\n", ans->val, arg3.val);
                else fprintf(TAC, "\tR[%d] = %d %s R[1];\n", ans->val, arg3.val, op);
            }
            break;
        case 2:
            if (regP >= 12)
            {
                ans->type = 1, ans->val = temp();
                if (op[0] == '^') fprintf(TAC, "\tR[0] = pwr(%d,%d);\n", arg3.val, arg4.val);
                else fprintf(TAC, "\tR[0] = %d %s %d;\n", arg3.val, op, arg4.val);
                fprintf(TAC, "\tMEM[%d] = R[0];\n", ans->val);
            }
            else
            {
                ans->type = 2, ans->val = regP++;
                if (op[0] == '^') fprintf(TAC, "\tR[%d] = pwr(%d,%d);\n", ans->val, arg3.val, arg4.val);
                else fprintf(TAC, "\tR[%d] = %d %s %d;\n", ans->val, arg3.val, op, arg4.val);
            }
            break;
        case 3:
            ans->type = 2, ans->val = arg4.val;
            if (op[0] == '^') fprintf(TAC, "\tR[%d] = pwr(%d, R[%d]);\n", arg4.val, arg3.val, arg4.val);
            else fprintf(TAC, "\tR[%d] = %d %s R[%d];\n", arg4.val, arg3.val, op, arg4.val);
            regP = arg4.val + 1;
            break;
        }
        break;
    case 3:
        switch (arg2)
        {
        case 1:
            ans->type = 2, ans->val = arg3.val;
            if (op[0] == '^') fprintf(TAC, "\tR[%d] = pwr(R[%d], R[1]);\n", arg3.val, arg3.val);
            else fprintf(TAC, "\tR[%d] = R[%d] %s R[1];\n", arg3.val, arg3.val, op);
            regP = arg3.val + 1;
            break;
        case 2:
            ans->type = 2, ans->val = arg3.val;
            if (op[0] == '^') fprintf(TAC, "\tR[%d] = pwr(R[%d],%d);\n", arg3.val, arg3.val, arg4.val);
            else fprintf(TAC, "\tR[%d] = R[%d] %s %d;\n", arg3.val, arg3.val, op, arg4.val);
            regP = arg3.val + 1;
            break;
        case 3:
            ans->type = 2, ans->val = arg3.val;
            if (op[0] == '^') fprintf(TAC, "\tR[%d] = pwr(R[%d], R[%d]);\n", arg3.val, arg3.val, arg4.val);
            else fprintf(TAC, "\tR[%d] = R[%d] %s R[%d];\n", arg3.val, arg3.val, op, arg4.val);
            regP = arg3.val + 1;
            break;
        }
        break;
    }
}

void set_id_num(char* id, int num, int* ans) {
    update(id);
    int loc = get(id);
    fprintf(TAC, "\tMEM[%d] = %d;\n", loc, num);
    *ans = loc;
}

void set_id_expr(char* id, expr expr_val, int* ans) {
    update(id);
    int loc = get(id);
    fprintf(TAC, "\tMEM[%d] = R[%d];\n", loc, expr_val.val);
    regP = 2;
    *ans = loc;
}

void set_id_id(char* id1, char* id2, int* ans) {
    update(id1);
    int loc1 = get(id1);
    int loc2 = get(id2);
    fprintf(TAC, "\tR[0] = MEM[%d];\n", loc2);
    fprintf(TAC, "\tMEM[%d] = R[0];\n", loc1);
    *ans = loc1;
}

int temp() {
    char *temp = (char *)malloc(10);
    sprintf(temp, "$t%d", ++temp_cnt);
    add(temp);
    return get(temp);
}

void set_arg_id(arg* argument, char* id) {
    int loc = get(id);
    argument->type = 1;
    argument->val = -1;
    argument->memloc = loc;
}

void set_arg_num(arg* argument, int num) {
    argument->type = 2;
    argument->val = num;
    argument->memloc = -1;
}

void set_arg_expr(arg* argument, expr expr_val) {
    if (expr_val.type == 1) {
        argument->type = 1;
        argument->val = -1;
        argument->memloc = expr_val.val;
    } else if (expr_val.type == 2) {
        argument->type = 3;
        argument->val = expr_val.val;
        argument->memloc = -1;
    }
}

void add(char* id)
{
    SymbolTable[size].id = id;
    SymbolTable[size].offset = memP;
    memP = memP + 1;
    size++;
}

void update(char* id)
{
    for (int i = 0; i < size; i++)
    {
        int found = strcmp(SymbolTable[i].id, id);
        if (found == 0) return;
    }
    add(id);
}

int get(char* id)
{
    for (int i = 0; i < size; i++)
    {
        int found = strcmp(SymbolTable[i].id, id);
        if (found == 0) return SymbolTable[i].offset;
    }
    fprintf(stderr, "!!! WARNING: %s not initialised before! \n", id);
    add(id);
    return get(id);
}

void symbolTable()
{
    printf("=====================================\n");
    printf("SYMBOL TABLE:\n");
    printf("=====================================\n");
    printf("| %-20s | %-10s |\n", "Name", "Offset");
    printf("|----------------------|------------|\n");
    for (int i = 0; i < size; i++)
    {
        printf("| %-20s | %-10d |\n", SymbolTable[i].id, SymbolTable[i].offset << 2);
    }
    printf("=====================================\n");
}

int main(int argc, char *argv[])
{
    yyin = stdin;
    TAC = fopen("intcode.c", "w");
    if (argc > 1)
    {
        FILE *file = fopen(argv[1], "r");
        if (!file) fprintf(stderr, "Error opening file: %s\n", argv[1]);
        if (!file) exit(1);
        yyin = file;
    }
    if (TAC == NULL) 
    {
        fprintf(stderr, "Error opening file for writing\n");
        exit(1);
    }
    fprintf(TAC, "#include <stdio.h>\n");
    fprintf(TAC, "#include <stdlib.h>\n");
    fprintf(TAC, "#include \"aux.c\"\n\n");
    fprintf(TAC, "int main() \n{\n");
    fprintf(TAC, "\tint R[12];\n");
    fprintf(TAC, "\tint MEM[65536];\n\n");

    yyparse();
    symbolTable();

    fprintf(TAC, "\n\texit(0);");
    fprintf(TAC, "\n}\n");
    fclose(yyin);
    fclose(TAC);
    return 0;
}

void yyerror(const char *s)
{
    fprintf(stderr, "%s\n", s);
}


