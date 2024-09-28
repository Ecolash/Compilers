#include "lex.yy.c"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
extern int yylex();
extern char* yytext;
extern int linecnt;


typedef struct KeyWordNode{
  char *keyword;
  struct KeyWordNode *next;
}KeyWordNode;

typedef struct IDNode {
  char *id;
  struct IDNode *next;
} IDNode;

typedef struct ConstNode {
  char charValue;
  int intValue;
  float floatValue;
  struct ConstNode *next;
} ConstNode;

typedef struct StringLiteralNode {
  char *stringValue;
  struct StringLiteralNode *next;
} StringLiteralNode;

typedef KeyWordNode *KeyWordNodePtr;
typedef IDNode *IDNodePtr;
typedef ConstNode *ConstNodePtr;
typedef StringLiteralNode *StringLiteralNodePtr;


/* Global Symbol Tables */
KeyWordNodePtr keyWordTableHead = NULL;      // Head of the keyword table
IDNodePtr idTableHead = NULL;                // Head of the identifier table
ConstNodePtr constTableHead = NULL;          // Head of the constant table
StringLiteralNodePtr strLitTableHead = NULL; // Head of the string literal table

/* Function Declarations for Table Management (for reference) */
void addKeyword(const char *keyword);
void addIdentifier(const char *id);
void addConstant(int intValue, float floatValue,char charValue);
void addStringLiteral(const char *stringValue);
void freeSymbolTables();
int identifierExists(const char *id);
void printSymbolTables();

int main(){
    int token;
    int prev=0;
    while((token=yylex())){
      if(prev!=linecnt){
        printf("\n\n");
        prev=linecnt;
      }
      switch(token){
        case SINGLE_LINE_COMM:
          printf("<SINGLE_LINE_COMM, %d, %s>\n", token, yytext);
          break;
        case MULTI_LINE_COMM:
          printf("<MULTI_LINE_COMM, %d, %s>\n", token, yytext);
          break;

        // Keywords
        case AUTO:
          addKeyword(yytext);
          printf("<AUTO, %d, %s>\n", token, yytext);
          break;
        case ENUM:
          addKeyword(yytext);
          printf("<ENUM, %d, %s>\n", token, yytext);
          break;
        case RESTRICT:
          addKeyword(yytext);
          printf("<RESTRICT, %d, %s>\n", token, yytext);
          break;
        case UNSIGNED:
          addKeyword(yytext);
          printf("<UNSIGNED, %d, %s>\n", token, yytext);
          break;
        case BREAK:
          addKeyword(yytext);
          printf("<BREAK, %d, %s>\n", token, yytext);
          break;
        case EXTERN:
          addKeyword(yytext);
          printf("<EXTERN, %d, %s>\n", token, yytext);
          break;
        case RETURN:
          addKeyword(yytext);
          printf("<RETURN, %d, %s>\n", token, yytext);
          break;
        case VOID:
          addKeyword(yytext);
          printf("<VOID, %d, %s>\n", token, yytext);
          break;
        case CASE:
          addKeyword(yytext);
          printf("<CASE, %d, %s>\n", token, yytext);
          break;
        case FLOAT:
          addKeyword(yytext);
          printf("<FLOAT, %d, %s>\n", token, yytext);
          break;
        case SHORT:
          addKeyword(yytext);
          printf("<SHORT, %d, %s>\n", token, yytext);
          break;
        case VOLATILE:
          addKeyword(yytext);
          printf("<VOLATILE, %d, %s>\n", token, yytext);
          break;
        case CHAR:
          addKeyword(yytext);
          printf("<CHAR, %d, %s>\n", token, yytext);
          break;
        case FOR:
          addKeyword(yytext);  
          printf("<FOR, %d, %s>\n", token, yytext);
          break;
        case SIGNED:
          addKeyword(yytext);
          printf("<SIGNED, %d, %s>\n", token, yytext);
          break;
        case WHILE:
          addKeyword(yytext);
          printf("<WHILE, %d, %s>\n", token, yytext);
          break;
        case CONST:
          addKeyword(yytext);
          printf("<CONST, %d, %s>\n", token, yytext);
          break;
        case GOTO:
          addKeyword(yytext);
          printf("<GOTO, %d, %s>\n", token, yytext);
          break;
        case SIZEOF:
          addKeyword(yytext);
          printf("<SIZEOF, %d, %s>\n", token, yytext);
          break;
        case _BOOL:
          addKeyword(yytext);
          printf("<_BOOL, %d, %s>\n", token, yytext);
          break;
        case CONTINUE:
          addKeyword(yytext);
          printf("<CONTINUE, %d, %s>\n", token, yytext);
          break;
        case IF:
          addKeyword(yytext);
          printf("<IF, %d, %s>\n", token, yytext);
          break;
        case STATIC:
          addKeyword(yytext);
          printf("<STATIC, %d, %s>\n", token, yytext);
          break;
        case _COMPLEX:
          addKeyword(yytext);
          printf("<_COMPLEX, %d, %s>\n", token, yytext);
          break;
        case DEFAULT:
          addKeyword(yytext);
          printf("<DEFAULT, %d, %s>\n", token, yytext);
          break;
        case INLINE:
          addKeyword(yytext);
          printf("<INLINE, %d, %s>\n", token, yytext);
          break;
        case STRUCT:
          addKeyword(yytext);
          printf("<STRUCT, %d, %s>\n", token, yytext);
          break;
        case _IMAGINARY:
          addKeyword(yytext);
          printf("<_IMAGINARY, %d, %s>\n", token, yytext);
          break;
        case DO:
          addKeyword(yytext);
          printf("<DO, %d, %s>\n", token, yytext);
          break;
        case INT:
          addKeyword(yytext);
          printf("<INT, %d, %s>\n", token, yytext);
          break;
        case SWITCH:
          addKeyword(yytext);
          printf("<SWITCH, %d, %s>\n", token, yytext);
          break;
        case DOUBLE:
          addKeyword(yytext);
          printf("<DOUBLE, %d, %s>\n", token, yytext);
          break;
        case LONG:
          addKeyword(yytext);
          printf("<LONG, %d, %s>\n", token, yytext);
          break;
        case TYPEDEF:
          addKeyword(yytext);
          printf("<TYPEDEF, %d, %s>\n", token, yytext);
          break;
        case ELSE:
          addKeyword(yytext);
          printf("<ELSE, %d, %s>\n", token, yytext);
          break;
        case REGISTER:
          addKeyword(yytext);
          printf("<REGISTER, %d, %s>\n", token, yytext);
          break;
        case UNION:
          addKeyword(yytext);
          printf("<UNION, %d, %s>\n", token, yytext);
          break;

        // Identifiers
        case IDENTIFIER:
          if (!identifierExists(yytext)) {
              addIdentifier(yytext);
          }
          printf("<IDENTIFIER, %s>\n", yytext);
          break;
        case INTEGER_CONSTANT:
          addConstant(atoi(yytext), 0.0, ' ');
          printf("<INTEGER_CONSTANT, %s>\n", yytext);
          break;
        case FLOATING_CONSTANT:
          addConstant(0, atof(yytext), ' ');
          printf("<FLOATING_CONSTANT, %s>\n", yytext);
          break;
        case CHARACTER_CONSTANT:
          addConstant(0.0, 0.0,yytext[1]); 
          printf("<CHARACTER_CONSTANT, %s>\n", yytext);
          break;
        case STRING_LITERAL:
          addStringLiteral(yytext);
          printf("<STRING_LITERAL, %s>\n", yytext);
          break;
        
        // Punctuators
        case SQRBROPEN:
            printf("<SQRBROPEN, %d, %s>\n", token, yytext);
            break;
        case SQRBRCLOSE:
            printf("<SQRBRCLOSE, %d, %s>\n", token, yytext);
            break;
        case RORBROPEN:
            printf("<RORBROPEN, %d, %s>\n", token, yytext);
            break;
        case RORBRCLOSE:
            printf("<RORBRCLOSE, %d, %s>\n", token, yytext);
            break;
        case CURBROPEN:
            printf("<CURBROPEN, %d, %s>\n", token, yytext);
            break;
        case CURBRCLOSE:
            printf("<CURBRCLOSE, %d, %s>\n", token, yytext);
            break;
        case DOT:
            printf("<DOT, %d, %s>\n", token, yytext);
            break;
        case ARWCOM:
            printf("<ARWCOM, %d, %s>\n", token, yytext);
            break;
        case INCRM:
            printf("<INCRM, %d, %s>\n", token, yytext);
            break;
        case DECRM:
            printf("<DECRM, %d, %s>\n", token, yytext);
            break;
        case AMPSND:
            printf("<AMPSND, %d, %s>\n", token, yytext);
            break;
        case MUL:
            printf("<MUL, %d, %s>\n", token, yytext);
            break;
        case ADD:
            printf("<ADD, %d, %s>\n", token, yytext);
            break;
        case SUB:
            printf("<SUB, %d, %s>\n", token, yytext);
            break;
        case NEG:
            printf("<NEG, %d, %s>\n", token, yytext);
            break;
        case EXCLAIM:
            printf("<EXCLAIM, %d, %s>\n", token, yytext);
            break;
        case DIV:
            printf("<DIV, %d, %s>\n", token, yytext);
            break;
        case MODULO:
            printf("<MODULO, %d, %s>\n", token, yytext);
            break;
        case SHL:
            printf("<SHL, %d, %s>\n", token, yytext);
            break;
        case SHR:
            printf("<SHR, %d, %s>\n", token, yytext);
            break;
        case LST:
            printf("<LST, %d, %s>\n", token, yytext);
            break;
        case GRT:
            printf("<GRT, %d, %s>\n", token, yytext);
            break;
        case LTE:
            printf("<LTE, %d, %s>\n", token, yytext);
            break;
        case GTE:
            printf("<GTE, %d, %s>\n", token, yytext);
            break;
        case EQL:
            printf("<EQL, %d, %s>\n", token, yytext);
            break;
        case NEQ:
            printf("<NEQ, %d, %s>\n", token, yytext);
            break;
        case AND:
            printf("<AND, %d, %s>\n", token, yytext);
            break;
        case OR:
            printf("<OR, %d, %s>\n", token, yytext);
            break;
        case QUESTION:
            printf("<QUESTION, %d, %s>\n", token, yytext);
            break;
        case COLON:
            printf("<COLON, %d, %s>\n", token, yytext);
            break;
        case SEMICOLON:
            printf("<SEMICOLON, %d, %s>\n", token, yytext);
            break;
        case DOTS:
            printf("<DOTS, %d, %s>\n", token, yytext);
            break;
        case ASSIGN:
            printf("<ASSIGN, %d, %s>\n", token, yytext);
            break;
        case STAREQ:
            printf("<STAREQ, %d, %s>\n", token, yytext);
            break;
        case DIVEQ:
            printf("<DIVEQ, %d, %s>\n", token, yytext);
            break;
        case MODEQ:
            printf("<MODEQ, %d, %s>\n", token, yytext);
            break;
        case PLUSEQ:
            printf("<PLUSEQ, %d, %s>\n", token, yytext);
            break;
        case MINUSEQ:
            printf("<MINUSEQ, %d, %s>\n", token, yytext);
            break;
        case SHLEQ:
            printf("<SHLEQ, %d, %s>\n", token, yytext);
            break;
        case SHREQ:
            printf("<SHREQ, %d, %s>\n", token, yytext);
            break;
        case BINANDEQ:
            printf("<BINANDEQ, %d, %s>\n", token, yytext);
            break;
        case BINXOREQ:
            printf("<BINXOREQ, %d, %s>\n", token, yytext);
            break;
        case BINOREQ:
            printf("<BINOREQ, %d, %s>\n", token, yytext);
            break;
        case COMMA:
            printf("<COMMA, %d, %s>\n", token, yytext);
            break;
        case HASH:
            printf("<HASH, %d, %s>\n", token, yytext);
            break;

        default:
          printf("Unknown token: %d, %s\n", token, yytext);
          break;
      }
    }
    printSymbolTables();
    freeSymbolTables();
    return 0;
}

void addKeyword(const char *keyword) {
    KeyWordNodePtr newNode = (KeyWordNodePtr)malloc(sizeof(KeyWordNode));
    newNode->keyword = strdup(keyword);
    newNode->next = keyWordTableHead;
    keyWordTableHead = newNode;
}
void addIdentifier(const char *id) {
    IDNodePtr newNode = (IDNodePtr)malloc(sizeof(IDNode));
    newNode->id = strdup(id);
    newNode->next = idTableHead;
    idTableHead = newNode;
}

void addConstant(int intValue, float floatValue,char charValue) {
    ConstNodePtr newNode = (ConstNodePtr)malloc(sizeof(ConstNode));
    newNode->intValue = intValue;
    newNode->floatValue = floatValue;
    newNode->charValue = charValue;
    newNode->next = constTableHead;
    constTableHead = newNode;
}

void addStringLiteral(const char *stringValue) {
    StringLiteralNodePtr newNode = (StringLiteralNodePtr)malloc(sizeof(StringLiteralNode));
    newNode->stringValue = strdup(stringValue);
    newNode->next = strLitTableHead;
    strLitTableHead = newNode;
}

int identifierExists(const char *id) {
    IDNodePtr current = idTableHead;
    while (current != NULL) {
        if (strcmp(current->id, id) == 0) {
            return 1;
        }
        current = current->next;
    }
    return 0;
}

void printKeywords(KeyWordNodePtr node) {
    if (node == NULL) return;
    printKeywords(node->next);
    printf("Keyword: %s\n", node->keyword);
}

void printIdentifiers(IDNodePtr node) {
    if (node == NULL) return;
    printIdentifiers(node->next);
    printf("Identifier: %s\n", node->id);
}

void printStringLiterals(StringLiteralNodePtr node) {
    if (node == NULL) return;
    printStringLiterals(node->next);
    printf("String Literal: %s\n", node->stringValue);
}

void printConstants(ConstNodePtr node) {
    if (node == NULL) return;
    printConstants(node->next);
    if (node->intValue != 0)
        printf("Integer: %d\n", node->intValue);
    if (node->floatValue != 0.0)
        printf("Float: %f\n", node->floatValue);
    if(node->charValue != ' ')
        printf("Char: %c\n", node->charValue);
}

void printSymbolTables() {
    printf("\n\t\t\t\t\t==========================SYMBOL TABLE==========================\n");
    printf("\nKeyword Table:\n");
    KeyWordNodePtr keyWordCurrent = keyWordTableHead;
    printKeywords(keyWordCurrent);

    printf("\nIdentifier Table:\n");
    IDNodePtr idCurrent = idTableHead;
    printIdentifiers(idCurrent);

    printf("\nConstant Table:\n");
    ConstNodePtr constCurrent = constTableHead;
    printConstants(constCurrent);

    printf("\nString Literal Table:\n");
    StringLiteralNodePtr strLitCurrent = strLitTableHead;
    printStringLiterals(strLitCurrent);
}



void freeSymbolTables() {
    KeyWordNodePtr keyWordCurrent = keyWordTableHead;
    while (keyWordCurrent != NULL) {
        KeyWordNodePtr temp = keyWordCurrent;
        keyWordCurrent = keyWordCurrent->next;
        free(temp->keyword);
        free(temp);
    }

    IDNodePtr idCurrent = idTableHead;
    while (idCurrent != NULL) {
        IDNodePtr temp = idCurrent;
        idCurrent = idCurrent->next;
        free(temp->id);
        free(temp);
    }

    ConstNodePtr constCurrent = constTableHead;
    while (constCurrent != NULL) {
        ConstNodePtr temp = constCurrent;
        constCurrent = constCurrent->next;
        free(temp);
    }

    StringLiteralNodePtr strLitCurrent = strLitTableHead;
    while (strLitCurrent != NULL) {
        StringLiteralNodePtr temp = strLitCurrent;
        strLitCurrent = strLitCurrent->next;
        free(temp->stringValue);
        free(temp);
    }
}