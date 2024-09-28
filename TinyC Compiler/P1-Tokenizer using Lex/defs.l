%{
#include <stdio.h>
#include <string.h>
int linecnt=1;

/* Token Definitions */

/* Range for Keywords (200 - 249) */
#define AUTO                   200
#define ENUM                   201
#define RESTRICT               202
#define UNSIGNED               203
#define BREAK                  204
#define EXTERN                 205
#define RETURN                 206
#define VOID                   207
#define CASE                   208
#define FLOAT                  209
#define SHORT                  210
#define VOLATILE               211
#define CHAR                   212
#define FOR                    213
#define SIGNED                 214
#define WHILE                  215
#define CONST                  216
#define GOTO                   217
#define SIZEOF                 218
#define _BOOL                  219  
#define CONTINUE               220
#define IF                     221
#define STATIC                 222
#define _COMPLEX               223
#define DEFAULT                224
#define INLINE                 225
#define STRUCT                 226
#define _IMAGINARY             227
#define DO                     228
#define INT                    229
#define SWITCH                 230
#define DOUBLE                 231
#define LONG                   232
#define TYPEDEF                233
#define ELSE                   234
#define REGISTER               235
#define UNION                  236

/* Range for Identifiers and Constants (300 - 349) */
#define IDENTIFIER             300
#define INTEGER_CONSTANT       301
#define FLOATING_CONSTANT      302
#define CHARACTER_CONSTANT     303
#define STRING_LITERAL         304

/* Range for Punctuators (400 - 449) */
#define SQRBROPEN              400
#define SQRBRCLOSE             401
#define RORBROPEN              402
#define RORBRCLOSE             403
#define CURBROPEN              404
#define CURBRCLOSE             405
#define DOT                    406
#define ARWCOM                 407
#define INCRM                  408
#define DECRM                  409
#define AMPSND                 410
#define MUL                    411
#define ADD                    412
#define SUB                    413
#define NEG                    414
#define EXCLAIM                415
#define DIV                    416
#define MODULO                 417
#define SHL                    418
#define SHR                    419
#define LST                    420
#define GRT                    421
#define LTE                    422
#define GTE                    423
#define EQL                    424
#define NEQ                    425
#define AND                    426
#define OR                     427
#define QUESTION               428
#define COLON                  429
#define SEMICOLON              430
#define DOTS                   431
#define ASSIGN                 432
#define STAREQ                 433
#define DIVEQ                  434
#define MODEQ                  435
#define PLUSEQ                 436
#define MINUSEQ                437
#define SHLEQ                  438
#define SHREQ                  439
#define BINANDEQ               440
#define BINXOREQ               441
#define BINOREQ                442
#define COMMA                  443
#define HASH                   444

#define SINGLE_LINE_COMM       1000
#define MULTI_LINE_COMM        1001
%}

/* Regular Expression Definitions */

/* Comments */
SINGLE_LINE_COMM           "//".*
SEQUENCE                   [^*]|[*][^/]
MULTI_LINE_COMM            [/][*]{SEQUENCE}*[*][/]

/* Keywords */
KEYWORD_SET1         	"auto"|"break"|"case"|"char"|"const"|"continue"|"default"|"do"|"double"
KEYWORD_SET2         	"else"|"enum"|"extern"|"float"|"for"|"goto"|"if"|"inline"|"int"|"long"|"typedef"
KEYWORD_SET3         	"register"|"restrict"|"return"|"short"|"signed"|"sizeof"|"static"|"struct"|"switch"
KEYWORD_SET4         	"union"|"unsigned"|"void"|"volatile"|"while"|"_Bool"|"_Complex"|"_Imaginary"
KEYWORD         	    {KEYWORD_SET1}|{KEYWORD_SET2}|{KEYWORD_SET3}|{KEYWORD_SET4}

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

/* Punctuators */
PUNC_GROUPING               [\(\)\[\]\{\}]
PUNC_ARITHMETIC             [+\-*/%]
PUNC_LOGICAL                [&|^~!]
PUNC_COMPARISON             [<>]
PUNC_ASSIGNMENT             [=]
PUNC_MISC                   [.,?:;#]

PUNC_SIMPLE                 {PUNC_GROUPING}|{PUNC_ARITHMETIC}|{PUNC_LOGICAL}|{PUNC_COMPARISON}|{PUNC_ASSIGNMENT}|{PUNC_MISC}
PUNC_COMPOUND_1             "->"|"++"|"--"|"<<"|">>"|"<="|">="|"=="|"!="
PUNC_COMPOUND_2             "&&"|"||"|"*="|"/="|"%="|"+="|"-="|"&="|"^="|"|="
PUNC_SPECIAL                "..."

PUNCTUATOR                  {PUNC_SIMPLE}|{PUNC_COMPOUND_1}|{PUNC_COMPOUND_2}|{PUNC_SPECIAL}
%%

{MULTI_LINE_COMM}          { return MULTI_LINE_COMM; }
{SINGLE_LINE_COMM}         { return SINGLE_LINE_COMM; }

"auto"                     { return AUTO; } 
"enum"                     { return ENUM; }
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
"_Bool"                    { return _BOOL; }
"continue"                 { return CONTINUE; }
"if"                       { return IF; }
"static"                   { return STATIC; }
"_Complex"                 { return _COMPLEX; }
"default"                  { return DEFAULT; }
"inline"                   { return INLINE; }
"struct"                   { return STRUCT; }
"_Imaginary"               { return _IMAGINARY; }
"do"                       { return DO; }
"int"                      { return INT; }
"switch"                   { return SWITCH; }
"double"                   { return DOUBLE; }
"long"                     { return LONG; }
"typedef"                  { return TYPEDEF; }
"else"                     { return ELSE; }
"register"                 { return REGISTER; }
"union"                    { return UNION; }

{FLOATING_CONSTANT}        { return FLOATING_CONSTANT; }
{INTEGER_CONSTANT}         { return INTEGER_CONSTANT; }
{CHARACTER_CONSTANT}       { return CHARACTER_CONSTANT; }
{STRING_LITERAL}           { return STRING_LITERAL; }
{IDENTIFIER}               { return IDENTIFIER; }

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
[\n]                        { linecnt++; }   
[\t ]+                   { /* Ignore whitespace */ }

%%

int yywrap(void){
    return 1;
}
