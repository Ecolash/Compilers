%{
#include <stdio.h>
#include <string.h>
#include "translator.h"
#include "defs.tab.h"
int linecnt=1;
%}

/* Regular Expression Definitions */

/* Comments */
SINGLE_LINE_COMM           "//".*
SEQUENCE                   [^*]|[*][^/]
MULTI_LINE_COMM            [/][*]{SEQUENCE}*[*][/]



/* Identifiers */
DIGIT                      [0-9]
IDENTIFIER_NONDIGIT        [_a-zA-Z]
IDENTIFIER                 {IDENTIFIER_NONDIGIT}({IDENTIFIER_NONDIGIT}|{DIGIT})*

/* Constants */
NONZERO_DIGIT              [1-9]
NONZERO_INTEGER_CONSTANT   {NONZERO_DIGIT}{DIGIT}*
INTEGER_CONSTANT           "0"|{NONZERO_INTEGER_CONSTANT}
DIGIT_SEQUENCE             {DIGIT}+
SIGN                       [-+]
EXPONENT_PART              [eE]{SIGN}?{DIGIT_SEQUENCE}
FRACTIONAL_CONSTANT        ({DIGIT_SEQUENCE}?"."{DIGIT_SEQUENCE})|({DIGIT_SEQUENCE}".")
FLOATING_CONSTANT          ({DIGIT_SEQUENCE}{EXPONENT_PART})|({FRACTIONAL_CONSTANT}{EXPONENT_PART}?)

ESCAPE_SEQUENCE            "\\"['"\\?abfnrtv]
C_CHAR                     {ESCAPE_SEQUENCE}|[^'\\\n]
C_CHAR_SEQUENCE            {C_CHAR}+
CHARACTER_CONSTANT         \'{C_CHAR_SEQUENCE}\'

/* String Literals */
S_CHAR                     {ESCAPE_SEQUENCE}|[^"\\\n]
S_CHAR_SEQUENCE            {S_CHAR}*
STRING_LITERAL             \"{S_CHAR_SEQUENCE}\"

%%
"auto"                     { return AUTO; } 
"restrict"                 { return RESTRICT; } 
"unsigned"                 { return UNSIGNED; }
"break"                    { return BREAK; }
"extern"                   { return EXTERN; }
"return"                   { return RETURN; }
"void"                     { return VOID; }
"case"                     { return CASE; }
"float"                    { return FLOAT; }
"short"                    { return SHORT; }
"volatile"                 { return VOLATILE; }
"char"                     { return CHAR; }
"for"                      { return FOR; }
"signed"                   { return SIGNED; }
"while"                    { return WHILE; }
"const"                    { return CONST; }
"goto"                     { return GOTO; }
"sizeof"                   { return SIZEOF; }
"_Bool"                    { return BOOL; }
"continue"                 { return CONTINUE; }
"if"                       { return IF; }
"static"                   { return STATIC; }
"_Complex"                 { return COMPLEX; }
"default"                  { return DEFAULT; }
"inline"                   { return INLINE; }
"struct"                   { return STRUCT; }
"_Imaginary"               { return IMAGINARY; }
"do"                       { return DO; }
"int"                      { return INT; }
"switch"                   { return SWITCH; }
"double"                   { return DOUBLE; }
"long"                     { return LONG; }
"typedef"                  { return TYPEDEF; }
"else"                     { return ELSE; }
"register"                 { return REGISTER; }
"union"                    { return UNION; }

{FLOATING_CONSTANT}        { yylval.sval=yytext; return FLOATING_CONSTANT; }
{INTEGER_CONSTANT}         { yylval.ival=atoi(yytext); return INTEGER_CONSTANT; }
{CHARACTER_CONSTANT}       { yylval.sval=yytext; return CHARACTER_CONSTANT; }
{STRING_LITERAL}           { yylval.sval=yytext; return STRING_LITERAL; }
{IDENTIFIER}               { yylval.symb=__CURRENT_SYMBOL_TABLE__->lookup(yytext);; return IDENTIFIER; }

"["                        { return SQRBROPEN; }
"]"                        { return SQRBRCLOSE; }
"("                        { return RORBROPEN; }
")"                        { return RORBRCLOSE; }
"{"                        { return CURBROPEN; }
"}"                        { return CURBRCLOSE; }
"."                        { return DOT; }
"->"                       { return ARWCOM; }
"++"                       { return INCRM; }
"--"                       { return DECRM; }
"&"                        { return AMPSND; }
"|"                        { return PIPE; }
"^"                        { return XOR; }
"*"                        { return MUL; }
"+"                        { return ADD; }
"-"                        { return SUB; }
"~"                        { return NEG; }
"!"                        { return EXCLAIM; }
"/"                        { return DIV; }
"%"                        { return MODULO; }
"<<"                       { return SHL; }
">>"                       { return SHR; }
"<"                        { return LST; }
">"                        { return GRT; }
"<="                       { return LTE; }
">="                       { return GTE; }
"=="                       { return EQL; }
"!="                       { return NEQ; }
"&&"                       { return AND; }
"||"                       { return OR; }
"?"                        { return QUESTION; }
":"                        { return COLON; }
";"                        { return SEMICOLON; }
"..."                      { return DOTS; }
"="                        { return ASSIGN; }
"*="                       { return STAREQ; }
"/="                       { return DIVEQ; }
"%="                       { return MODEQ; }
"+="                       { return PLUSEQ; }
"-="                       { return MINUSEQ; }
"<<="                      { return SHLEQ; }
">>="                      { return SHREQ; }
"&="                       { return BINANDEQ; }
"^="                       { return BINXOREQ; }
"|="                       { return BINOREQ; }
","                        { return COMMA; }
"#"                        { return HASH; }
{SINGLE_LINE_COMM}      { /* Ignore single line comments */ }
{MULTI_LINE_COMM}       { /* Ignore multi-line comments */ }
[\n]                        { linecnt++; }   
[\t ]+                   { /* Ignore whitespace */ }

%%

int yywrap(void){
    return 1;
}