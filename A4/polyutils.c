#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "y.tab.c"
#include "lex.yy.c"

typedef struct Node Node;
typedef struct Node *NodePtr;
extern NodePtr ROOT;

long long binpow(long long x, int p)
{
    if (p == 0) return 1;
    if (p % 2 == 0)
    {
        long long res = binpow(x, p / 2);
        return res * res;
    }
    return x * binpow(x, p - 1);
}

void yyerror(char *s)
{
    fprintf(stderr, "Error: %s\n", s);
}

typedef struct Attributes
{
    union 
    {
        char inh_sign;
        int inh_val;
    } inh_par;
    long long syn_val;
} ATT;

typedef struct Node
{
    char type;
    NodePtr *children;
    ATT attributes;
    int size;
    int cap;
} Node;

typedef struct Node *NodePtr;

NodePtr createNode(char name)
{
    NodePtr node = (NodePtr)malloc(sizeof(Node));
    node->type = name;
    node->attributes.syn_val = (isdigit(name)) ? name - '0' : 0;
    if (node->type  == '+') node->attributes.inh_par.inh_sign = '+';
    if (node->type  == '-') node->attributes.inh_par.inh_sign = '-';
    if (node->type  == '^') node->attributes.inh_par.inh_sign = '^';

    node->children = NULL;
    node->cap = 0;
    node->size = 0;
    return node;
}

void addChild(NodePtr par, NodePtr child)
{
    if (par->size == par->cap)
    {
        par->children = (NodePtr *)realloc(par->children, 2 * par->cap * sizeof(NodePtr));
        par->cap *= 2;
    }
    par->children[par->size] = child;
    par->size++;
}

void printTree(NodePtr node, int d, int f, int* markers) {
    if (!node) return;
    for (int i = 0; i < d - 1; i++) 
    {
        if (markers[i]) printf("│    ");
        else printf("     ");
    }

    if (d > 0) printf(f ? "└─-> " : "├─-> ");
    printf("%c []\n", node->type);
    if (node->size == 0) return;
    if (d > 0) markers[d - 1] = !f;
    for (int i = 0; i < node->size; i++) printTree(node->children[i], d + 1, i == node->size - 1, markers);
}

void printAnnotatedTree(NodePtr node, int d, int f, int* markers) {
    if (!node) return;

    printf("\t");
    for (int i = 0; i < d - 1; i++) 
    {
        if (markers[i]) printf("│   ");
        else printf("    ");
    }

    if (d > 0) printf(f ? "└─> " : "├─> ");
    char *str = (char *)malloc(1000 * sizeof(char));

    char t = node->type;
    if (t == 'P') sprintf(str, "inh = %c", node->attributes.inh_par.inh_sign);
    else if (t == 'T') sprintf(str, "inh = %c", node->attributes.inh_par.inh_sign);
    else if (t == 'N') sprintf(str, "val = %lld", node->attributes.syn_val);
    else if (t == 'M') sprintf(str, "inh = %d, val = %lld", node->attributes.inh_par.inh_val, node->attributes.syn_val);
    else if (isdigit(t)) sprintf(str, "val = %lld", node->attributes.syn_val);

    printf("%c [%s]\n", node->type, str);
    if (node->size == 0) return;
    if (d > 0) markers[d - 1] = !f;
    for (int i = 0; i < node->size; i++) printAnnotatedTree(node->children[i], d + 1, i == node->size - 1, markers);
}

void setAttr(NodePtr node)
{
    if (!node) return;
    if (node->type == 'S')
    {
        if(node->size == 1)
        {
            NodePtr P = node->children[0];
            if(P->type != 'P') exit(EXIT_FAILURE);
            P->attributes.inh_par.inh_sign = '+';
        }
        else
        {
            NodePtr sign = node->children[0];
            NodePtr P = node->children[1];    
            if(P->type != 'P' || ((sign->type != '+') && (sign->type != '-'))) exit(EXIT_FAILURE);
            P->attributes.inh_par.inh_sign = sign->attributes.inh_par.inh_sign;
        }
    }

    if (node->type == 'P')
    {
        if(node->size == 1)
        {
            NodePtr T = node->children[0];
            if(T->type != 'T') exit(EXIT_FAILURE);
            T->attributes.inh_par.inh_sign = node->attributes.inh_par.inh_sign;
        }
        else if(node->size == 3)
        {
            NodePtr T = node->children[0];
            NodePtr sign = node->children[1];
            NodePtr P = node->children[2];

            if(P->type != 'P' || T->type != 'T' || ((sign->type != '+') && (sign->type != '-'))) exit(EXIT_FAILURE);
            T->attributes.inh_par.inh_sign = node->attributes.inh_par.inh_sign;
            P->attributes.inh_par.inh_sign = sign->attributes.inh_par.inh_sign;
        }
    }

    if (node->type == 'N')
    {
        if(node->size == 2)
        {
            NodePtr num = node->children[0];
            NodePtr M = node->children[1];
            if(M->type != 'M' || !(isdigit(num->type))) exit(EXIT_FAILURE);
            
            int x = num->attributes.syn_val;
            M->attributes.inh_par.inh_val = x;
        }
    }

    if (node->type == 'M')
    {
         if(node->size == 2)
        {
            NodePtr num = node->children[0];
            NodePtr M = node->children[1];
            if(M->type != 'M' || !(isdigit(num->type))) exit(EXIT_FAILURE);

            int x = num->attributes.syn_val;
            M->attributes.inh_par.inh_val = node->attributes.inh_par.inh_val * 10 + x;
        }
    }

    for(int i = 0; i < node->size; i++) setAttr(node->children[i]);

    if(node->type == 'N')
    {
        if(node->size == 1)
        {
            NodePtr num = node->children[0];
            if(!(isdigit(num->type))) exit(EXIT_FAILURE);
            node->attributes.syn_val = num->attributes.syn_val;
        }
        else
        {
            NodePtr num = node->children[0];
            NodePtr M = node->children[1];
            if(!(isdigit(num->type)) || M->type != 'M') exit(EXIT_FAILURE);
            node->attributes.syn_val = M->attributes.syn_val;
        }
    }

    if(node->type == 'M')
    {
        if(node->size == 1)
        {
            NodePtr num = node->children[0];
            if(!(isdigit(num->type))) exit(EXIT_FAILURE);
            int x = num->attributes.syn_val;
            node->attributes.syn_val = node->attributes.inh_par.inh_val * 10 + x;
        }
        else
        {
            NodePtr num = node->children[0];
            NodePtr M = node->children[1];
            if(!(isdigit(num->type)) || M->type != 'M') exit(EXIT_FAILURE);
            node->attributes.syn_val = M->attributes.syn_val;
        }
    }

}

long long evalpoly(NodePtr root, int x)
{
    if (!root) return 0;
    char valid[] = {'S', 'P', 'T', 'X'};
    for(int i = 0; i < 4; i++)
    {
        if(root->type == valid[i]) break;
        if(i == 3) return 0;
    }

    for(int i = 0; i < root->size; i++) evalpoly(root->children[i], x);

    if(root->type == 'S')
    {
        NodePtr P = NULL;
        if(root->size == 1) P = root->children[0];
        else if (root->size == 2) P = root->children[1];
        else exit(EXIT_FAILURE);
        
        root->attributes.syn_val = P->attributes.syn_val;
        return root->attributes.syn_val;
    }

    if(root->type == 'P')
    {
        NodePtr T = NULL;
        NodePtr P = NULL;
        if(root->size == 1) T = root->children[0];
        else if (root->size == 3) T = root->children[0], P = root->children[2];
        else exit(EXIT_FAILURE);

        if(root->size == 1) root->attributes.syn_val = T->attributes.syn_val;
        else root->attributes.syn_val =  T->attributes.syn_val + P->attributes.syn_val; 
        return root->attributes.syn_val;
    }

    if(root->type == 'T')
    {
        NodePtr N = NULL;
        NodePtr X = NULL;
        if(root->size == 1) 
        {
            N = root->children[0];
            if (N->type == '1') root->attributes.syn_val = 1;
            else if (N->type == 'N') root->attributes.syn_val = N->attributes.syn_val;
            else if (N->type == 'X') root->attributes.syn_val = N->attributes.syn_val;
            else exit(EXIT_FAILURE);
        }
        else if (root->size == 2)
        {
            N = root->children[0];
            X = root->children[1];
            if (N->type != 'N' || X->type != 'X') exit(EXIT_FAILURE);
            long long coeff = N->attributes.syn_val;
            long long val = X->attributes.syn_val;
            root->attributes.syn_val = coeff * val;
        }
        else exit(EXIT_FAILURE);

        root->attributes.syn_val = (root->attributes.inh_par.inh_sign == '+') ? root->attributes.syn_val : -root->attributes.syn_val;
        return root->attributes.syn_val;
    }

    if(root->type == 'X')
    {
        if(root->size == 1) 
        {
            NodePtr num = root->children[0];
            if(num->type == 'x') root->attributes.syn_val = x;
            else exit(EXIT_FAILURE);
        }
        else if(root->size == 3)
        {
            NodePtr num = root->children[0];
            NodePtr X = root->children[2];
            int power = X->attributes.syn_val;
            root->attributes.syn_val = binpow(x, power);
        }
        else exit(EXIT_FAILURE);
        return root->attributes.syn_val;
    }

    exit(EXIT_FAILURE);
}

void printDerivative(NodePtr root)
{
    if (!root) return;
    char valid[] = {'S', 'P', 'T', 'X'};
    for(int i = 0; i < 4; i++)
    {
        if(root->type == valid[i]) break;
        if(i == 3) return;
    }

    for(int i = 0; i < root->size; i++) printDerivative(root->children[i]);

    if(root->type == 'T')
    {
        NodePtr N = NULL;
        NodePtr X = NULL;
        char sign = root->attributes.inh_par.inh_sign;

        if(root->size == 1) 
        {
            N = root->children[0];
            if (N->type == '1') return;
            else if (N->type == 'N') return;
            else if (N->type == 'X')
            {
                long long pow = 1;
                if( N->size == 1) pow = 1;
                else if(N->size == 3) pow = N->children[2]->attributes.syn_val;
                else exit(EXIT_FAILURE);

                long long coeff = pow;
                long long new_pow = pow - 1;
                if(coeff == 0) return;

                if (new_pow == 0)printf("%c %lld ", sign, coeff);
                else if (new_pow == 1) printf("%c %lldx ", sign, coeff);
                else printf("%c %lldx^%lld ", sign, coeff, new_pow);
            }
            else exit(EXIT_FAILURE);
            return;
        }
        else if (root->size == 2)
        {
            N = root->children[0];
            X = root->children[1];
            if (N->type != 'N' || X->type != 'X') exit(EXIT_FAILURE);
            long long pow = 1;

            if( X->size == 1) pow = 1;
            else if(X->size == 3) pow = X->children[2]->attributes.syn_val;
            else exit(EXIT_FAILURE);

            long long coeff = N->attributes.syn_val * pow;
            long long new_pow = pow - 1;
            if(coeff == 0) return;

            if (new_pow == 0)printf("%c %lld ", sign, coeff);
            else if (new_pow == 1) printf("%c %lldx ", sign, coeff);
            else printf("%c %lldx^%lld ", sign, coeff, new_pow);
            return;
        }
        else exit(EXIT_FAILURE);
    }
    
}


int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s <input_file>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    FILE *input = fopen(argv[1], "r");
    if (!input)
    {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    yyin = input;
    yyparse();
    int markers[1000] = {0};
    // printTree(root, 0, 1, markers);
    setAttr(ROOT);
    printf("+++ The annotated parse tree is:\n");
    printAnnotatedTree(ROOT, 0, 1, markers);
    fclose(input);

    printf("\n");
    for(int x = -5; x <= 5; x++)
    {
        long long res = evalpoly(ROOT, x);
        printf("+++ f(%2d) = %10lld\n", x, res);
    }
    printf("\n");
    printf("+++ f'(x) = ");
    printDerivative(ROOT);
    printf("\n");
    return 0;
}