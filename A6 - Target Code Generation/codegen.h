#ifndef __CODEGEN_H__
#define __CODEGEN_H__

#include <iostream>
#include <fstream>
#include <cstring>
#include <iomanip>
#include "y.tab.c"
#include "lex.yy.c"

using namespace std;

const string sep = string(50, '=');
const string sep2 = string(50, '-');

extern FILE *yyin;
extern int yylineno;

int block[1 << 10];
int CONTROL_FLOW[1 << 10][100];
int __MAP__[1 << 10];

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

void load_reg(int reg, const char *arg, int isT, int idx)
{
    ofstream log("register_log.out", ios::app);
    log << "| >> | LOADED R[" << reg + 1 << "] with value " << arg << endl;
    log.close();
    char *rn = new char[10];
    sprintf(rn, "R%d", reg + 1);
    if (isT == false)
    {
        const char *op = constant(arg) ? "LDI" : "LD";
        int start = emit2(const_cast<char*>(op), rn, NULL, const_cast<char*>(arg));
        if (__MAP__[idx] == -1) __MAP__[idx] = start + 1;
    }

    if (constant(arg)) return;
    sPtr symb = find(const_cast<char*>(arg));
    char* RT = new char[10];
    sprintf(RT, "%d", reg + 1);
    symb->locations[1] = RT;
    REG_DESCRIPTOR[reg][0] = symb;
}

int spill()
{
    int mini = 0, min_score = 1e9, score = 0;
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 10; j++) 
        {
            bool updated = false;
            if (REG_DESCRIPTOR[i][j] != NULL) {
                sPtr symb = find(REG_DESCRIPTOR[i][j]->name);
                if (symb->locations[0] && !strcmp(symb->locations[0], REG_DESCRIPTOR[i][j]->name)) updated = true;
                if (symb->locations[1] && !strcmp(symb->locations[1], REG_DESCRIPTOR[i][j]->name)) updated = true;
                score += !updated;
            }
        }   
        score = min(score, min_score);
        if (score == min_score) mini = i;
        score = 0;
    }

    for (int j = 0; j < 10; j++) {
        bool updated = false;
        if (REG_DESCRIPTOR[mini][j] != NULL) {
            sPtr symb = find(REG_DESCRIPTOR[mini][j]->name);
            if (symb->locations[0] && !strcmp(symb->locations[0], REG_DESCRIPTOR[mini][j]->name)) updated = true;
            if (symb->locations[1] && !strcmp(symb->locations[1], REG_DESCRIPTOR[mini][j]->name)) updated = true;
            if (updated == false) {
                char RT[10];
                sprintf(RT, "R%d", mini + 1);
                emit2("ST", RT, NULL, symb->name);
                symb->locations[0] = symb->name;
                ofstream log("register_log.out", ios::app);
                log << "| << | STORED R[" << mini + 1 << "] to memory value " << symb->name << endl;
                log.close();
            }
        }
    }
    return mini;
}

int getReg(const char *arg, const char *res, int t, int idx)
{
    // CHECK - 1
    // ----------------------------------------
    for (int i = 0; i < 5; i++)
    for (int j = 0; j < 10; j++)
    if (REG_DESCRIPTOR[i][j] && !strcmp(REG_DESCRIPTOR[i][j]->name, arg))
        return i;

    // CHECK - 2
    // ----------------------------------------
    for (int i = 0; i < 5; i++)
    if (!REG_DESCRIPTOR[i][0])
    {
        load_reg(i, arg, t, idx);
        return i;
    }

    // CHECK - 3
    // ----------------------------------------
    int updated_reg = 0;
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            updated_reg += (REG_DESCRIPTOR[i][j] == NULL);
            if (REG_DESCRIPTOR[i][j])
            {
                sPtr symb = find(REG_DESCRIPTOR[i][j]->name);
                if (symb->locations[0] && !strcmp(symb->locations[0], symb->name)) { updated_reg++; }
                else if (symb->locations[1] && !strcmp(symb->locations[1], symb->name)) { updated_reg++; }
            } 
        }
        if (updated_reg == 10) { load_reg(i, arg, t, idx); return i;}
        updated_reg = 0;
    }

    // CHECK - 4
    // ----------------------------------------
    if (!strcmp(arg, res))
    {
        for (int i = 0; i < 5; i++)
        {
            for (int j = 0; j < 10; j++)
            if (REG_DESCRIPTOR[i][j])
            {
                sPtr symb = find(REG_DESCRIPTOR[i][j]->name);
                if (strcmp(symb->name, arg) != 0) break;
            }
            load_reg(i, arg, t, idx); return i; 
        }
    }
    // CHECK - 5 (Implicitly done)


    // CHECK - 6
    // ----------------------------------------
    int x = spill();
    load_reg(x, arg, t, idx);
    return x;
}

void clean(bool log = 1)
{
    sPtr temp = __GLOBAL_SYMBOL_TABLE__->head;
    while (temp != NULL)
    {
        if (constant(temp->locations[0]))
        {
            int reg_num = atoi(temp->locations[0]);
            char *treg = (char *)malloc(sizeof(char) * 10);
            sprintf(treg, "R%d", reg_num);
            emit2("ST", treg, NULL, temp->name);
            temp->locations[0] = temp->name;
            ofstream log("register_log.out", ios::app);
            log << "| << | STORED R[" << reg_num << "] to memory value " << temp->name << endl;
            log.close();
        }
        temp = temp->next;
    }
    if (log) {
        ofstream log("register_log.out", ios::app);
        log << sep << "\nBLOCK " << ++BLOCK_NUM << endl;
        log << sep2 << endl;
        log.close();
    }
}

void target_code_generator(qPtr quad = __GLOBAL_QUAD_TABLE__->head, int cnt = 1) 
{
    int x, y, z;
    Rx = Ry = Rz = 0;
    if (!quad) return;
    if (cnt == 1 || block[cnt] == 1)
    {
        if (cnt != 1) clean();
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

        if (__MAP__[cnt] == -1) __MAP__[cnt] = x + 1;
        for (int i = 0; i < 10; i++)
        {
            if (CONTROL_FLOW[atoi(quad->next->result)][i] == 0)
            {
                CONTROL_FLOW[atoi(quad->next->result)][i] = x + 1;
                break;
            }
        }

        clean();
        clear_reg();
        emit2("Block", NULL, NULL, NULL);
        target_code_generator(quad->next->next, cnt + 1);
    }
    else if (!strcmp(quad->op, "goto"))
    {
        clean(0);
        int x = emit2("JMP", NULL, NULL, NULL);
        if (__MAP__[cnt] == -1)  __MAP__[cnt] = x + 1;
        for (int i = 0; i < 10; i++)
        {
            if (CONTROL_FLOW[atoi(quad->result)][i] == 0)
            {
                CONTROL_FLOW[atoi(quad->result)][i] = x + 1;
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
                sPtr symb = find(const_cast<char*>(quad->result));
                char *treg = new char[10];
                sprintf(treg, "%d", reg_idx + 1);
                symb->locations[0] = treg;
                REG_DESCRIPTOR[reg_idx][i] = symb;
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
        sPtr symb = find(const_cast<char*>(quad->result));
        REG_DESCRIPTOR[reg_idx][0] = symb;
        for (int i = 1; i < 10; i++) REG_DESCRIPTOR[reg_idx][i] = NULL;

        char *c = new char[10];
        sprintf(c, "R%d", reg_idx + 1);
        symb->locations[0] = c;
        symb->locations[1] = NULL;
        if (!strcmp(quad->op, "+") || !strcmp(quad->op, "-") || !strcmp(quad->op, "*") || !strcmp(quad->op, "/") || !strcmp(quad->op, "%"))
        {
            char* ops[] = {"ADD", "SUB", "MUL", "DIV", "REM"};
            char* op = ops[strchr("+-*/%", quad->op[0]) - "+-*/%"];
            x = emit2(op, a, b, c);
            if (__MAP__[cnt] == -1) __MAP__[cnt] = x + 1;
            ofstream log("register_log.out", ios::app);
            log << "| == | R[" << reg_idx + 1 << "] = " << a << " " << quad->op << " " << b << endl;
        }

        target_code_generator(quad->next, cnt + 1);
    }
}


#endif