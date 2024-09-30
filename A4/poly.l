%{
#include "y.tab.h"
%}

%%
"+"        { yylval.cval = '+'; return PLUS;  }
"-"        { yylval.cval = '-'; return MINUS; }
"x"        { yylval.cval = 'x'; return XVAR;  }
"^"        { yylval.cval = '^'; return EXP;   }
"1"        { yylval.cval = yytext[0]; return ONE;   }
"0"        { yylval.cval = yytext[0]; return ZERO;  }
[2-9]      { yylval.cval = yytext[0]; return DIGIT; }     
[ \t]      { /* Ignore whitespace */ } 
\n         { return 0; }      
.          { fprintf(stderr, "Unrecognized character: %s\n", yytext); exit(1); }  

%%

int yywrap() {
    return 1;
}