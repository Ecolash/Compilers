
%{
    #include <stdio.h>
    #include "defs.tab.h"
%}
/* Comments */
SINGLE_LINE_COMM           "//".*
SEQUENCE                   [^*]|[*][^/]
MULTI_LINE_COMM            [/][*]{SEQUENCE}*[*][/]
IDENTIFIER                 [a-zA-Z_][a-zA-Z0-9_]*
DIGIT                      [0-9]
INTEGER_CONSTANT           [1-9]{DIGIT}*|0
FLOATING_CONST             (((([0-9]+)?\.[0-9]+)|([0-9]+\.))([eE][+-]?[0-9]+)?)|([0-9]+[eE][+-]?[0-9]+)
ESCAPE_SEQUENCE            \\['"?\\abfnrtv0]
C_CHAR                     [^'\\\n]|{ESCAPE_SEQUENCE}
C_CHAR_SEQUENCE            {C_CHAR}+
CHARACTER_CONST            \'{C_CHAR_SEQUENCE}\' 
PUNCTUATOR                 "["|"]"|"."|"&"|"*"|"+"|"-"|"~"|"!"|"/"|"("|")"|"{"|"}"|"%"|","|"<"|">"|"^"|"|"|"="|"?"|":"|";"|"#"
S_CHAR                     [^"\\\n]|{ESCAPE_SEQUENCE}
S_CHAR_SEQUENCE            {S_CHAR}+
STRING_LITERAL             \"{S_CHAR_SEQUENCE}?\"
WS                         [ \t\n]

%%

"->"            { return PTR_OP; }
"++"            { return INCREMENT; }
"--"            { return DECREMENT; }
"sizeof"        { return SIZEOF; }
"<<"            { return LSHIFT; }
">>"            { return RSHIFT; }
"<="            { return LE_OP; }
">="            { return GE_OP; }
"=="            { return EQ_OP; }
"!="            { return NE_OP; }
"&&"            { return BINARY_AND; }
"||"            { return BINARY_OR; }
"*="            { return MUL_ASSIGN; }
"/="            { return DIV_ASSIGN; }
"%="            { return MOD_ASSIGN; }
"+="            { return ADD_ASSIGN; }
"-="            { return SUB_ASSIGN; }
"<<="           { return LEFT_ASSIGN; }
">>="           { return RIGHT_ASSIGN; }
"&="            { return AND_ASSIGN; }
"^="            { return XOR_ASSIGN; }
"|="            { return OR_ASSIGN; }
"extern"        { return EXTERN; }
"static"        { return STATIC; }
"auto"          { return AUTO; }
"register"      { return REGISTER; }
"void"          { return VOID; }
"char"          { return CHAR; }
"short"         { return SHORT; }
"int"           { return INT; }
"long"          { return LONG; }
"float"         { return FLOAT; }
"double"        { return DOUBLE; }
"signed"        { return SIGNED; }
"unsigned"      { return UNSIGNED; }
"_Bool"         { return BOOL; }
"_Imaginary"    { return IMAGINARY; }
"_Complex"      { return COMPLEX; }
"const"         { return CONST; }
"restrict"      { return RESTRICT; }
"volatile"      { return VOLATILE; }
"inline"        { return INLINE; }
"..."           { return ELLIPSIS; }
"if"            { return IF; }
"else"          { return ELSE; }
"switch"        { return SWITCH; }
"case"          { return CASE; }
"default"       { return DEFAULT; }
"while"         { return WHILE; }
"do"            { return DO; }
"for"           { return FOR; }
"goto"          { return GOTO; }
"continue"      { return CONTINUE; }
"break"         { return BREAK; }
"return"        { return RETURN; }

{IDENTIFIER}            { yylval.string = strdup(yytext); return IDENTIFIER; }
{INTEGER_CONSTANT}      { yylval.num = atoi(yytext); return INTEGER_VAL; }
{FLOATING_CONST}        { yylval.decimal_num = atof(yytext); return FLOAT_VAL; }
{CHARACTER_CONST}       { yylval.character = yytext[0]; return CHAR_VAL; }
{STRING_LITERAL}        { yylval.string = strdup(yytext); return STRING; }
{PUNCTUATOR}            { return yytext[0]; }
{SINGLE_LINE_COMM}      { /* Ignore single line comments */ }
{MULTI_LINE_COMM}       { /* Ignore multi-line comments */ }
{WS}                    { /* Ignore whitespace */ }

%%

int yywrap(void) {
    return 1;
}