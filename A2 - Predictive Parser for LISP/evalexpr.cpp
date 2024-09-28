#include <iostream>
#include <string>
#include <stack>
#include "lex.yy.c"

using namespace std;

extern int yylex();
extern FILE *yyin;
extern char *yytext;

struct SymbolNode
{
    string id;
    int value;
    SymbolNode *next;
};

struct ConstantNode
{
    int value;
    ConstantNode *next;
};

using ConstantRef = ConstantNode *;
using SymbolRef = SymbolNode *;

using CONST_TABLE = ConstantRef;
using SYMBOL_TABLE = SymbolRef;

CONST_TABLE T0 = NULL;
SYMBOL_TABLE T1 = NULL;

union NodeData
{
    int op_type;
    SymbolNode *symbol_ref;
    ConstantNode *const_ref;
};

struct TokenNode
{
    int type;
    NodeData data;
    TokenNode *left;
    TokenNode *right;

    TokenNode(int operator_type) : type(OP), left(NULL), right(NULL)  { data.op_type = operator_type; }
    TokenNode(SymbolRef symbol)  : type(ID), left(NULL), right(NULL)  { data.symbol_ref = symbol; }
    TokenNode(ConstantRef consv) : type(NUM), left(NULL), right(NULL) { data.const_ref = consv; }
};

using TokenRef = TokenNode*;

void add_symbol(const string& id) {
    SymbolRef current = T1;
    if (current == NULL) 
    {
        T1 = new SymbolNode;
        T1->id = id;
        T1->value = 0;
        T1->next = NULL;
        return;
    }
    while (current->next != NULL) 
    {
        if (current->id == id) return;  
        current = current->next;
    }
    
    if (current->id == id) return;  
    SymbolRef new_node = new SymbolNode;
    new_node->id = id;
    new_node->value = 0;
    new_node->next = NULL;
    current->next = new_node;
}

SymbolRef find_symbol(const string& id) {
    SymbolRef current = T1;
    while (current != NULL) 
    {
        if (current->id == id) return current;
        current = current->next;
    }
    return NULL;
}

void add_constant(int value) {
    ConstantRef current = T0;
    while (current != NULL) 
    {
        if (current->value == value) return;
        current = current->next;
    }
    
    ConstantRef new_node = new ConstantNode;
    new_node->value = value;
    new_node->next = T0;
    T0 = new_node;
}

ConstantRef find_constant(const int value) {
    ConstantRef current = T0;
    while (current != NULL) 
    {
        if (current->value == value) return current;
        current = current->next;
    }
    return NULL;
}

int rules[3][10] = {
/* EXPR */ {0, 0, 0, 0, 0, 0, 0, 0, LPAREN, 0},
/* OP   */ {0, 0, 0, ADD, SUB, MUL, DIV, MOD, 0, 0},
/* ARG  */ {0, ID, NUM, 0, 0, 0, 0, 0, EXPR, 0}};

stack<TokenRef> Parsestack, ParseTree;

bool isTerminal(int symbol)
{
    return (symbol >= ID && symbol <= END);
}

bool parse()
{
    stack<int> st;
    st.push(END);
    st.push(EXPR);
    int token = yylex();
    int level = 0;

    while (!st.empty())
    {
        int top = st.top();
        if (isTerminal(top))
        {
            TokenRef pars;
            SymbolRef id, current;
            ConstantRef num;
            switch (top)
            {
            case ADD:
            case SUB:
            case MUL:
            case DIV:
            case MOD:
                pars = new TokenNode(top);
                Parsestack.push(pars);
                break;
            case ID:
                add_symbol(yytext);
                id = find_symbol(yytext);
                pars = new TokenNode(id);
                Parsestack.push(pars);
                break;
            case NUM:
                add_constant(stoi(yytext));
                num = find_constant(stoi(yytext));
                pars = new TokenNode(num);
                Parsestack.push(pars);
                break;
            case LPAREN:
                level++;
                break;
            case RPAREN:
                if (level <= 0)
                {
                    cerr << "*** Error: Right parenthesis expected in place of " << yytext << endl;
                    return false;
                }
                level--;
                break;
            case END:
                current = T1;
                while (current != NULL)
                {
                    if (token == NUM)
                        current->value = stoi(yytext);
                    else
                    {
                        cerr << "*** ERROR: Invalid input" << endl;
                        return false;
                    }
                    current = current->next;
                    token = yylex();
                }
                return true;
            default:
                break;
            }

            if (top == token)
            {
                st.pop();
                token = yylex();
            }
            else
            {
                if (top == RPAREN) cerr << "*** Error: Right parenthesis expected in place of " << yytext << endl;
                else if (top == ID || top == NUM || top == LPAREN) cerr << "*** Error: ID/NUM/LPAREN expected in place of " << yytext << endl;
                else cerr << "*** Syntax error: expected " << top << " but got " << token << endl;
                return false;
            }
        }
        else
        {
            int entry = rules[top - EXPR][token];
            if (entry == 0)
            {
                if (top == OTHER) cerr << "*** Error: Invalid operator " << yytext << " found" << endl;
                else if (top == OP) cerr << "*** Error: Operator expected in place of " << yytext << endl;
                else if (top == ARG) cerr << "*** Error: ID/NUM/LPAREN expected in place of " << yytext << endl;
                else cerr << "*** Syntax error: expected " << top << " but got " << token << endl;
                return false;
            }
            else
            {
                st.pop();
                switch (entry)
                {
                    case LPAREN:
                        st.push(RPAREN);
                        st.push(ARG);
                        st.push(ARG);
                        st.push(OP);
                        st.push(LPAREN);
                        break;

                    case ADD:
                    case SUB:
                    case MUL:
                    case DIV:
                    case MOD:
                        st.push(entry);
                        break;

                    case ID:
                    case NUM:
                    case EXPR:
                        st.push(entry);
                        break;
                }
            }
        }
    }
    return true;
}

TokenRef makeParseTree()
{
    while (!Parsestack.empty())
    {
        TokenRef node = Parsestack.top();
        Parsestack.pop();
        if (node->type == OP)
        {
            TokenRef l = ParseTree.top();
            ParseTree.pop();
            TokenRef r = ParseTree.top();
            ParseTree.pop();
            node->left = l;
            node->right = r;
        }
        ParseTree.push(node);
    }

    return ParseTree.top();
}

void printParseTree(TokenRef root, int level)
{
    if (root == NULL) return;
    for (int i = 0; i < level - 1; i++) cout << "    ";
    if (level > 0) cout << "--->";
    if (root->type == OP)
    {
        if(root->data.op_type == ADD) cout << "OP(+)\n";
        else if(root->data.op_type == SUB) cout << "OP(-)\n";
        else if(root->data.op_type == MUL) cout << "OP(*)\n";
        else if(root->data.op_type == DIV) cout << "OP(/)\n";
        else if(root->data.op_type == MOD) cout << "OP(%)\n";
    }
    else if (root->type == NUM) cout << "NUM(" << root->data.const_ref->value << ")\n";
    else cout << "ID(" << root->data.symbol_ref->id << ")\n";
    printParseTree(root->left, level + 1);
    printParseTree(root->right, level + 1);
}

int evaluate(TokenRef root)
{
    int ans = 0;
    if (root == NULL) return 0;
    if (root->type == NUM) return root->data.const_ref->value;
    else if (root->type == ID) return root->data.symbol_ref->value;
    else if (root->type == OP)
    {
        int x = evaluate(root->left);
        int y = evaluate(root->right);
        switch (root->data.op_type)
        {
            case ADD:
                ans = x + y;
                break;
            case SUB:
                ans = x - y;
                break;
            case MUL:
                ans = x * y;
                break;
            case DIV:
                ans = x / y;
                break;
            case MOD:
                ans = x % y;
                break;
            default:
                cout << "Operand type not supported" << endl;
                break;
        }
    }
    return ans;
}


int main()
{
    if (!parse())
    {
        cerr << "Parsing failed due to syntax errors.\n";
        exit(EXIT_FAILURE);
    }

    TokenRef root = makeParseTree();
    cout << "Parsing successful!\n";
    printParseTree(root, 0);
    SymbolRef current = T1;
    if (current != NULL) cout << "\nReading variable values from the input" << endl;
    while (current != NULL)
    {
        cout << current->id << " = " << current->value << endl;
        current = current->next;
    }
    cout << "The expression evaluates to " << evaluate(root) << endl;
    return 0;
}
