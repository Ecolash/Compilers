%{
    #include <stdio.h>
    #include "translator.h"
    #include "defs.tab.h"

    extern int yylineno;
    extern char* yytext;
%}

/* States */
%x SINGLE_LINE_COMM
%x MULTI_LINE_COMM

/* Regular Expressions */
ID_NONDIGIT     [a-zA-Z_]
DIGIT           [0-9]   
IDENTIFIER      {ID_NONDIGIT}({ID_NONDIGIT}|{DIGIT})*

DIG_NONZERO     [1-9]
CONSTANT_INT    0|{DIG_NONZERO}{DIGIT}*
DIG_SEQ         {DIGIT}+
CONSTANT_FRAC   {DIG_SEQ}?\.{DIG_SEQ}|{DIG_SEQ}\.
SIGN            [+-]
EXPO            [eE]{SIGN}?{DIG_SEQ}
CONSTANT_FLOAT  {CONSTANT_FRAC}{EXPO}?|{DIG_SEQ}{EXPO}
CONSTANT_ENUM   {IDENTIFIER}
ESCAPE_SEQ      \\['"?\\abfnrtv]
C_CHAR          [^'\\\n]|{ESCAPE_SEQ}
C_CHAR_SEQ      {C_CHAR}+
CONSTANT_CHAR   \'{C_CHAR_SEQ}\'
CONSTANT        {CONSTANT_INT}|{CONSTANT_FLOAT}|{CONSTANT_ENUM}|{CONSTANT_CHAR}

S_CHAR          [^"\\\n]|{ESCAPE_SEQ}
S_CHAR_SEQ      {S_CHAR}+
LITERAL         \"({S_CHAR_SEQ}?)\"

/* Whitespace recognition */
WHITE_SPACE     [  \t\n]


/* Definitions */
/* Keywords, Identifiers, Constants, Literals, Punctuators */
%%
"//"                        {BEGIN(SINGLE_LINE_COMM);}
<SINGLE_LINE_COMM>.         {}
<SINGLE_LINE_COMM>\n        {BEGIN(INITIAL);}
<SINGLE_LINE_COMM><<EOF>>   {BEGIN(INITIAL);}

"/*"                        {BEGIN(MULTI_LINE_COMM);}
<MULTI_LINE_COMM>"*/"       {BEGIN(INITIAL);}
<MULTI_LINE_COMM>.          {}
<MULTI_LINE_COMM>\n         {}

"auto"                      {return AUTO;}
"enum"                      {return ENUM;}
"restrict"                  {return RESTRICT;}
"unsigned"                  {return UNSIGNED;}
"break"                     {return BREAK;}
"extern"                    {return EXTERN;}
"return"                    {return RETURN;}
"void"                      {return VOID;}
"case"                      {return CASE;}
"float"                     {return FLOAT;}
"short"                     {return SHORT;}
"volatile"                  {return VOLATILE;}
"char"                      {return CHAR;}
"for"                       {return FOR;}
"signed"                    {return SIGNED;}
"while"                     {return WHILE;}
"const"                     {return CONST;}
"goto"                      {return GOTO;}
"sizeof"                    {return SIZEOF;}
"_Bool"                     {return BOOL;}
"continue"                  {return CONTINUE;}
"if"                        {return IF;}
"static"                    {return STATIC;}
"_Complex"                  {return COMPLEX;}
"default"                   {return DEFAULT;}
"inline"                    {return INLINE;}
"struct"                    {return STRUCT;}
"_Imaginary"                {return IMAGINARY;}
"do"                        {return DO;}
"int"                       {return INT;}
"switch"                    {return SWITCH;}
"double"                    {return DOUBLE;}
"long"                      {return LONG;}
"typedef"                   {return TYPEDEF;}
"else"                      {return ELSE;}
"register"                  {return REGISTER;}
"union"                     {return UNION;}

"("                         {return PARANTHESIS_OPEN;}
")"                         {return PARANTHESIS_CLOSE;}
"["                         {return SQ_BRACKET_OPEN;}
"]"                         {return SQ_BRACKET_CLOSE;}
"{"                         {return CURLY_BRACKET_OPEN;}
"}"                         {return CURLY_BRACKET_CLOSE;}
"."                         {return PERIOD;}
"->"                        {return ARROW;}
"++"                        {return INCREMENT;}
"--"                        {return DECREMENT;}
","                         {return COMMA;}
"&"                         {return AMPERSAND;}
"*"                         {return ASTERISK;}
"+"                         {return PLUS;}
"-"                         {return MINUS;}
"~"                         {return TILDE;}
"!"                         {return EXCLAMATION;}
"/"                         {return SLASH;}
"%"                         {return PERCENT;}
"<<"                        {return LEFT_SHIFT;}
">>"                        {return RIGHT_SHIFT;}
"<"                         {return LESS_THAN;}
">"                         {return GREATER_THAN;}
"<="                        {return LESS_THAN_EQUAL;}
">="                        {return GREATER_THAN_EQUAL;}
"=="                        {return EQUAL;}
"!="                        {return NOT_EQUAL;}
"^"                         {return CARET;}
"|"                         {return PIPE;}
"&&"                        {return LOGICAL_AND;}
"||"                        {return LOGICAL_OR;}
"?"                         {return QUESTION;}
":"                         {return COLON;}
";"                         {return SEMICOLON;}
"..."                       {return ELLIPSIS;}
"="                         {return ASSIGN;}
"*="                        {return MULTIPLY_ASSIGN;}
"/="                        {return DIVIDE_ASSIGN;}
"%="                        {return MOD_ASSIGN;}
"+="                        {return PLUS_ASSIGN;}
"-="                        {return MINUS_ASSIGN;}
"<<="                       {return LEFT_SHIFT_ASSIGN;}
">>="                       {return RIGHT_SHIFT_ASSIGN;}
"&="                        {return AND_ASSIGN;}
"^="                        {return XOR_ASSIGN;}
"|="                        {return OR_ASSIGN;}
"#"                         {return HASH;}


{IDENTIFIER}                {yylval.symb = currentSymbolTable->lookup(yytext); return IDENTIFIER;}
{CONSTANT_INT}              {yylval.iValue = atoi(yytext) ;return CONSTANT_INT;}
{CONSTANT_FLOAT}            {yylval.sValue = yytext; return CONSTANT_FLOAT;}
{CONSTANT_CHAR}             {yylval.sValue = yytext ;return CONSTANT_CHAR;}
{LITERAL}                   {yylval.sValue = yytext ;return LITERAL;}
{WHITE_SPACE}               {}
%%

int yywrap() {
    return 1;
}