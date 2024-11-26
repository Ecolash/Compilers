
#ifndef DEFS_H
#define DEFS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct ParseTreeNode
{
    char *name;
    struct ParseTreeNode **children;
    int childCount;
    int capacity;
} ParseTreeNode;

ParseTreeNode *createNode(char *s);
void addChild(ParseTreeNode *parent, ParseTreeNode *child);
void dfs(ParseTreeNode *node, int depth, int last, int *markers);

#endif
