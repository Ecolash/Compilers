
%{
    #define COMMAND 1
    #define BEGIN_ 2
    #define END 3
    #define MATH_EQN 4
    #define DISPLAY_EQN 5
    #define OPEN_BRACE 6
    #define CLOSE_BRACE 6
    #define STRING 8
    #define OTHERS 9
    #define COMMENTS 10
    #define MATH_MODE 11
    #define INLINE_MODE 12
%}

comment         %[^\n]*\n
command1        \\[a-zA-Z]+
command2        \\[^a-zA-Z~]
command3        "~"
text            [a-zA-Z]+
begin           \\begin\{[^}]+\}
end             \\end\{[^}]+\}
math_mode1      \$\$
math_mode2s     \\\[\n
math_mode2e     \n\\\]

%%

{comment}           { return COMMENTS; }
{begin}             { return BEGIN_; }
{end}               { return END; }
{command1}          { return COMMAND; }
{command2}          { return COMMAND; }
{command3}          { return COMMAND; }
{math_mode1}        { return MATH_MODE; }
{math_mode2s}       { return MATH_MODE; }
{math_mode2e}       { return MATH_MODE; }
"$"                 { return INLINE_MODE; }
"{"                 { return OPEN_BRACE; }
"}"                 { return CLOSE_BRACE; }
[ \t\n]             ;
"\\~"               { return COMMAND; }
{text}              { return STRING; }
.                   { return OTHERS; }

%%

int yywrap(){ }