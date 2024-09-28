#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum ValueType {
    INTEGER,
    DECIMAL,
    STRINGLITERAL,
    NONTERMINAL
};

typedef struct ParseTreeNode {
    char* name;
    struct ParseTreeNode** children;
    int childCount;                 
    int capacity;                 
} ParseTreeNode;

ParseTreeNode* createNode(char* s) {
    ParseTreeNode* node = (ParseTreeNode*)malloc(sizeof(ParseTreeNode));
    node->name = s;
    node->children = NULL; 
    node->childCount = 0;
    node->capacity = 0;    
    return node;
}

void addChild(ParseTreeNode* parent, ParseTreeNode* child) {
    if (parent->childCount == parent->capacity) {
        parent->capacity = parent->capacity == 0 ? 1 : parent->capacity * 2;
        parent->children = (ParseTreeNode**)realloc(parent->children, parent->capacity * sizeof(ParseTreeNode*));
    }
    parent->children[parent->childCount++] = child;
}

void dfs(struct ParseTreeNode* node, int depth) {
    if (!node) return; 
    for (int i = 0; i < depth; i++) printf("  ");
    printf("%s\n", node->name);

    for (int i = 0; i < node->childCount; i++) dfs(node->children[i], depth + 1);
}