#ifndef __CODEGEN_H__
#define __CODEGEN_H__

#include <iostream>
#include <fstream>
#include <cstring>
#include <iomanip>
#include "y.tab.c"
#include "lex.yy.c"

using namespace std;

extern FILE *yyin;
extern int yylineno;

int block[1 << 10];
int target_code[1 << 10][100];
int correlation[1 << 10];

extern STPtr __GLOBAL_SYMBOL_TABLE__;
extern QTPtr __GLOBAL_QUAD_TABLE__;
extern QTPtr __TARGET_CODE_TABLE__;

extern int BLOCK_NUM;
extern int QUAD_CNT;
extern int OFFSET;

int ASSEMBLY_CNT = 0;
const int MAX_VAR = 10;
int NUM_REG = 5;
int Rx, Ry, Rz;

sPtr REG_DESCRIPTOR[5][10];
sPtr ADDRESS_DESCRIPTOR[1024][10];

void clear_reg()
{
    memset(REG_DESCRIPTOR, 0, sizeof(REG_DESCRIPTOR));
    return;
}

int emit2(char *op, char *arg1, char *arg2, char *result)
{
    qPtr Q0 = init(op, arg1, arg2, result);
    Q0-> idx = (!strcmp(op, "Block"))? ASSEMBLY_CNT : ASSEMBLY_CNT++;
    qPtr *temp = &__TARGET_CODE_TABLE__->head;
    while (*temp != NULL) temp = &(*temp)->next;
    *temp = Q0;
    return Q0->idx;
}

bool constant(const char *str)
{
    if (!str || !*str) return false;
    for (; *str; ++str) if (!isdigit(*str)) return false;
    return true;
}

void load_reg(int reg_num, const char *arg, int t, int idx)
{
    char *rn = new char[10];
    sprintf(rn, "R%d", reg_num + 1);
    if (constant(arg))
    {
        if (!t)
        {
            int nw = emit2("LDI", rn, NULL, const_cast<char*>(arg));
            if (correlation[idx] == -1) correlation[idx] = nw + 1;
        }
    }
    else
    {
        if (!t)
        {
            int nw = emit2("LD", rn, NULL, const_cast<char*>(arg));
            if (correlation[idx] == -1) correlation[idx] = nw + 1;
        }
        Symbol *var = find(const_cast<char*>(arg));
        char reg_num_str[10];
        sprintf(reg_num_str, "%d", reg_num + 1);
        var->locations[1] = reg_num_str;
        REG_DESCRIPTOR[reg_num][0] = var;
    }
}

int getRegHelper()
{
    int mini = 0;
    int min_score = 1e9;
    
    for (int i = 0; i < 5; i++) {
        int score = 0;
        for (int j = 0; j < 10; j++) {
            if (REG_DESCRIPTOR[i][j] != NULL) {
                Symbol *var = find(REG_DESCRIPTOR[i][j]->name);
                bool updated = false;
                for (int k = 0; k < 2; k++) {
                    if (var->locations[k] && !strcmp(var->locations[k], var->name)) {
                        updated = true;
                        break;
                    }
                }
                if (!updated) score++;
            }
        }
        if (score < min_score) {
            min_score = score;
            mini = i;
        }
    }
    for (int j = 0; j < 10; j++) {
        if (REG_DESCRIPTOR[mini][j] != NULL) {
            Symbol *var = find(REG_DESCRIPTOR[mini][j]->name);
            bool updated = false;
            for (int k = 0; k < 2; k++) {
                if (var->locations[k] && !strcmp(var->locations[k], var->name)) {
                    updated = true;
                    break;
                }
            }
            if (!updated) {
                char reg_name[10];
                sprintf(reg_name, "R%d", mini + 1);
                emit2("ST", reg_name, NULL, var->name);
                var->locations[0] = var->name;
            }
        }
    }
    return mini;
}
int getReg(const char *arg, const char *res, int t, int idx)
{
    for (int i = 0; i < 5; i++)
        for (int j = 0; j < 10; j++)
            if (REG_DESCRIPTOR[i][j] && !strcmp(REG_DESCRIPTOR[i][j]->name, arg))
                return i;

    for (int i = 0; i < 5; i++)
        if (!REG_DESCRIPTOR[i][0])
        {
            load_reg(i, arg, t, idx);
            return i;
        }

    for (int i = 0; i < 5; i++)
    {
        int cnt = 0;
        for (int j = 0; j < 10; j++)
            if (REG_DESCRIPTOR[i][j])
            {
                Symbol *var = find(REG_DESCRIPTOR[i][j]->name);
                for (int k = 0; k < 2; k++)
                    if (var->locations[k] && !strcmp(var->locations[k], var->name))
                    {
                        cnt++;
                        break;
                    }
            }
            else cnt++;
        if (cnt == 10)
        {
            load_reg(i, arg, t, idx);
            return i;
        }
    }

    if (!strcmp(arg, res))
    {
        for (int i = 0; i < 5; i++)
        {
            int cnt = 0;
            for (int j = 0; j < 10; j++)
                if (REG_DESCRIPTOR[i][j])
                {
                    Symbol *var = find(REG_DESCRIPTOR[i][j]->name);
                    if (!strcmp(var->name, arg)) cnt++;
                }
                else cnt++;
            if (cnt == 10)
            {
                load_reg(i, arg, t, idx);
                return i;
            }
        }
    }

    int x = getRegHelper();
    load_reg(x, arg, t, idx);
    return x;
}

void spill()
{
    Symbol *temp = __GLOBAL_SYMBOL_TABLE__->head;
    while (temp != NULL)
    {
        if (constant(temp->locations[0]))
        {
            int reg_num = atoi(temp->locations[0]);

            char *reg_name = (char *)malloc(sizeof(char) * 10);
            sprintf(reg_name, "R%d", reg_num);
            emit2("ST", reg_name, NULL, temp->name);
            temp->locations[0] = temp->name;
        }
        temp = temp->next;
    }
}

void target_code_generator(qPtr quad = __GLOBAL_QUAD_TABLE__->head, int cnt = 1) 
{
    int x, y, z;
    Rx = Ry = Rz = 0;
    if (!quad) return;
    if (cnt == 1 || block[cnt] == 1)
    {
        if (cnt != 1) spill();
        clear_reg();
        emit2("Block", NULL, NULL, NULL);
    }

    if (!strcmp(quad->result, "if"))
    {
        char *a = constant(quad->arg1) ? const_cast<char*>(quad->arg1) : new char[10];
        char *b = constant(quad->arg2) ? const_cast<char*>(quad->arg2) : new char[10];
        if (!constant(quad->arg1)) { Rx = getReg(quad->arg1, quad->result, 0, cnt); sprintf(a, "R%d", Rx + 1);}
        if (!constant(quad->arg2)) { Ry = getReg(quad->arg2, quad->result, 0, cnt); sprintf(b, "R%d", Ry + 1);}

        if (!strcmp(quad->op, "=")) x = emit2("JNE", a, b, NULL);
        else if (!strcmp(quad->op, "/=")) x = emit2("JEQ", a, b, NULL);
        else if (!strcmp(quad->op, ">")) x = emit2("JLE", a, b, NULL);
        else if (!strcmp(quad->op, "<")) x = emit2("JGE", a, b, NULL);
        else if (!strcmp(quad->op, ">=")) x = emit2("JLT", a, b, NULL);
        else if (!strcmp(quad->op, "<=")) x = emit2("JGT", a, b, NULL);

        if (correlation[cnt] == -1) correlation[cnt] = x + 1;
        for (int i = 0; i < 10; i++)
        {
            if (target_code[atoi(quad->next->result)][i] == 0)
            {
                target_code[atoi(quad->next->result)][i] = x + 1;
                break;
            }
        }

        spill();
        clear_reg();
        emit2("Block", NULL, NULL, NULL);
        target_code_generator(quad->next->next, cnt + 1);
    }
    else if (!strcmp(quad->op, "goto"))
    {
        spill();
        int x = emit2("JMP", NULL, NULL, NULL);

        if (correlation[cnt] == -1)
        {
            correlation[cnt] = x + 1;
        }

        for (int i = 0; i < 10; i++)
        {
            if (target_code[atoi(quad->result)][i] == 0)
            {
                target_code[atoi(quad->result)][i] = x + 1;
                break;
            }
        }

        target_code_generator(quad->next, cnt + 1);
    }
    else if (!strcmp(quad->op, "="))
    {
        int reg_idx = getReg(quad->arg1, quad->result, 0, cnt);

        for (int i = 0; i < 10; i++)
        {
            if (REG_DESCRIPTOR[reg_idx][i] == NULL)
            {
                Symbol *var = find(const_cast<char*>(quad->result));
                char *reg_name = new char[10];
                sprintf(reg_name, "%d", reg_idx + 1);
                var->locations[0] = reg_name;
                REG_DESCRIPTOR[reg_idx][i] = var;
                break;
            }
        }

        target_code_generator(quad->next, cnt + 1);
    }
    else
    {
        char *a = constant(quad->arg1) ? const_cast<char*>(quad->arg1) : new char[10];
        char *b = constant(quad->arg2) ? const_cast<char*>(quad->arg2) : new char[10];

        if (!constant(quad->arg1))
        {
            int reg_idx1 = getReg(quad->arg1, quad->result, 0, cnt);
            sprintf(a, "R%d", reg_idx1 + 1);
        }

        if (!constant(quad->arg2))
        {
            int reg_idx2 = getReg(quad->arg2, quad->result, 0, cnt);
            sprintf(b, "R%d", reg_idx2 + 1);
        }

        int reg_idx = getReg(quad->result, quad->result, 1, cnt);
        Symbol *var = find(const_cast<char*>(quad->result));
        REG_DESCRIPTOR[reg_idx][0] = var;

        for (int i = 1; i < 10; i++)
        {
            if (REG_DESCRIPTOR[reg_idx][i] != NULL)
            {
                REG_DESCRIPTOR[reg_idx][i] = NULL;
            }
        }

        char *c = new char[10];
        sprintf(c, "R%d", reg_idx + 1);
        var->locations[0] = c;
        var->locations[1] = NULL;

        if (!strcmp(quad->op, "+") || !strcmp(quad->op, "-") || !strcmp(quad->op, "*") || !strcmp(quad->op, "/") || !strcmp(quad->op, "%"))
        {
            char* ops[] = {"ADD", "SUB", "MUL", "DIV", "REM"};
            char* op = ops[strchr("+-*/%", quad->op[0]) - "+-*/%"];
            x = emit2(op, a, b, c);
            if (correlation[cnt] == -1) correlation[cnt] = x + 1;
        }

        target_code_generator(quad->next, cnt + 1);
    }
}


#endif