%{
    #include <stdio.h>
    #include "defs.h"
    extern int yylex();
    void yyerror(char* s);
    extern struct ParseTreeNode* root;
%}

%union{
    int num;
    double decimal_num;
    char* string;
    struct ParseTreeNode* X;
}

%token PTR_OP
%token INCREMENT
%token DECREMENT
%token SIZEOF
%token LSHIFT
%token RSHIFT
%token LE_OP
%token GE_OP
%token EQ_OP
%token NE_OP
%token BINARY_AND
%token BINARY_OR
%token MUL_ASSIGN
%token DIV_ASSIGN
%token MOD_ASSIGN
%token ADD_ASSIGN
%token SUB_ASSIGN
%token LEFT_ASSIGN
%token RIGHT_ASSIGN
%token AND_ASSIGN
%token XOR_ASSIGN
%token OR_ASSIGN
%token EXTERN
%token STATIC
%token AUTO
%token REGISTER
%token VOID
%token CHAR
%token SHORT
%token INT
%token LONG
%token FLOAT
%token DOUBLE
%token SIGNED
%token UNSIGNED
%token BOOL
%token IMAGINARY
%token COMPLEX
%token CONST
%token RESTRICT
%token VOLATILE
%token INLINE
%token ELLIPSIS
%token IF
%token SWITCH
%token CASE
%token DEFAULT
%token WHILE
%token DO
%token FOR
%token GOTO
%token CONTINUE
%token BREAK
%token RETURN

%start program
%token<string> IDENTIFIER
%token<num> INTEGER_VAL
%token<decimal_num> FLOAT_VAL
%token<string> CHAR_VAL
%token<string> STRING

%type<X> primary_expression postfix_expression argument_expression_list
%type<X> unary_expression unary_operator cast_expression
%type<X> multiplicative_expression additive_expression shift_expression
%type<X> relational_expression equality_expression AND_expression
%type<X> exclusive_OR_expression inclusive_OR_expression logical_AND_expression
%type<X> logical_OR_expression conditional_expression assignment_expression
%type<X> assignment_expression_optional assignment_operator expression
%type<X> expression_optional constant_expression declaration
%type<X> declaration_specifiers init_declarator_list init_declarator
%type<X> storage_class_specifier type_specifier specifier_qualifier_list
%type<X> type_qualifier function_specifier declarator
%type<X> direct_declarator pointer type_qualifier_list
%type<X> type_qualifier_list_optional parameter_type_list parameter_list
%type<X> parameter_declaration identifier_list identifier_list_optional
%type<X> type_name initializer initializer_list
%type<X> designation designation_optional designator_list
%type<X> designator expression_statement selection_statement
%type<X> iteration_statement jump_statement statement
%type<X> labeled_statement compound_statement block_item_list
%type<X> block_item_list_optional block_item translation_unit
%type<X> external_declaration function_definition declaration_list
%type<X> declaration_list_optional program

%nonassoc LOWER_THAN_ELSE
%nonassoc ELSE

%%
primary_expression: IDENTIFIER {
    printf("primary_expression -> IDENTIFIER\n");
}
| INTEGER_VAL {
    printf("primary_expression -> INTEGER_VAL\n");
}
| FLOAT_VAL {
    printf("primary_expression -> FLOAT_VAL\n");
}
| CHAR_VAL {
    printf("primary_expression -> CHAR_VAL\n");
}
| STRING {
    printf("primary_expression -> STRING\n");
}
| '(' expression ')' {
    printf("primary_expression -> '(' expression ')'\n");
    $$ = createNode("primary_expression");
    addChild($$, createNode("("));
    addChild($$, $2);
    addChild($$, createNode(")"));
};

postfix_expression : primary_expression {
    printf("postfix_expression -> primary_expression\n");
    $$ = createNode("primary_expression");
    addChild($$, $1);
}
| postfix_expression '[' expression ']' {
    printf("postfix_expression -> postfix_expression '[' expression ']'\n");
    $$ = createNode("postfix_expression");
    addChild($$, $1);
    addChild($$, createNode("["));
    addChild($$, $3);
    addChild($$, createNode("]"));
}
| postfix_expression '(' ')' {
    printf("postfix_expression -> postfix_expression '(' ')'\n");
    $$ = createNode("postfix_expression");
    addChild($$, $1);
    addChild($$, createNode("("));
    addChild($$, createNode(")"));
}
| postfix_expression '(' argument_expression_list ')' {
    printf("postfix_expression -> postfix_expression '(' "
           "argument_expression_list ')'\n");
    $$ = createNode("postfix_expression");
    addChild($$, $1);
    addChild($$, createNode("("));
    addChild($$, $3);
    addChild($$, createNode(")"));
}
| postfix_expression '.' IDENTIFIER {
    printf("postfix_expression -> postfix_expression '.' IDENTIFIER\n");
    $$ = createNode("postfix_expression");
    addChild($$, $1);
    addChild($$, createNode("."));
    addChild($$, createNode($3));
}
| postfix_expression PTR_OP IDENTIFIER {
    printf("postfix_expression -> postfix_expression PTR_OP IDENTIFIER\n");
    $$ = createNode("postfix_expression");
    addChild($$, $1);
    addChild($$, createNode("->"));
    addChild($$, createNode($3));
}
| postfix_expression INCREMENT {
    printf("postfix_expression -> postfix_expression INCREMENT\n");
    $$ = createNode("postfix_expression");
    addChild($$, $1);
    addChild($$, createNode("++"));
}
| postfix_expression DECREMENT {
    printf("postfix_expression -> postfix_expression DECREMENT\n");
    $$ = createNode("postfix_expression");
    addChild($$, $1);
    addChild($$, createNode("--"));
}
| '(' type_name ')' '{' initializer_list '}' {
    printf(
        "postfix_expression -> '(' type_name ')' '{' initializer_list '}'\n");
    $$ = createNode("postfix_expression");
    addChild($$, createNode("("));
    addChild($$, createNode("type_name"));
    addChild($$, createNode(")"));
    addChild($$, createNode("{"));
    addChild($$, $5);
    addChild($$, createNode("}"));
}
| '(' type_name ')' '{' initializer_list ',' '}' {
    printf("postfix_expression -> '(' type_name ')' '{' initializer_list ',' "
           "'}'\n");
    $$ = createNode("postfix_expression");
    addChild($$, createNode("("));
    addChild($$, createNode("type_name"));
    addChild($$, createNode(")"));
    addChild($$, createNode("{"));
    addChild($$, $5);
    addChild($$, createNode(","));
    addChild($$, createNode("}"));
};

argument_expression_list : assignment_expression {
    printf("argument_expression_list -> assignment_expression\n");
    $$ = createNode("argument_expression_list");
    addChild($$, $1);
}
| argument_expression_list ',' assignment_expression {
    printf("argument_expression_list -> argument_expression_list ',' "
           "assignment_expression\n");
    $$ = createNode("argument_expression_list");
    addChild($$, $1);
    addChild($$, createNode(","));
    addChild($$, $3);
};

unary_expression : postfix_expression {
    printf("unary_expression -> postfix_expression\n");
    $$ = createNode("unary_expression");
    addChild($$, $1);
}
| INCREMENT unary_expression {
    printf("unary_expression -> INCREMENT unary_expression\n");
    $$ = createNode("unary_expression");
    addChild($$, createNode("++"));
    addChild($$, $2);
}
| DECREMENT unary_expression {
    printf("unary_expression -> DECREMENT unary_expression\n");
    $$ = createNode("unary_expression");
    addChild($$, createNode("--"));
    addChild($$, $2);
}
| unary_operator cast_expression {
    printf("unary_expression -> unary_operator cast_expression\n");
    $$ = createNode("unary_expression");
    addChild($$, $1);
    addChild($$, $2);
}
| SIZEOF unary_expression {
    printf("unary_expression -> SIZEOF unary_expression\n");
    $$ = createNode("unary_expression");
    addChild($$, createNode("SIZEOF"));
    addChild($$, $2);
}
| SIZEOF '(' type_name ')' {
    printf("unary_expression -> SIZEOF '(' type_name ')'\n");
    $$ = createNode("unary_expression");
    addChild($$, createNode("SIZEOF"));
    addChild($$, createNode("("));
    addChild($$, createNode("type_name"));
    addChild($$, createNode(")"));
};

unary_operator : '&' {
    printf("unary_operator -> '&'\n");
    $$ = createNode("&");
}
| '*' {
    printf("unary_operator -> '*'\n");
    $$ = createNode("*");
}
| '+' {
    printf("unary_operator -> '+'\n");
    $$ = createNode("+");
}
| '-' {
    printf("unary_operator -> '-'\n");
    $$ = createNode("-");
}
| '~' {
    printf("unary_operator -> '~'\n");
    $$ = createNode("~");
}
| '!' {
    printf("unary_operator -> '!'\n");
    $$ = createNode("!");
};

cast_expression : unary_expression {
    printf("cast_expression -> unary_expression\n");
    $$ = createNode("cast_expression");
    addChild($$, $1);
}
| '(' type_name ')' cast_expression {
    printf("cast_expression -> '(' type_name ')' cast_expression\n");
    $$ = createNode("cast_expression");
    addChild($$, createNode("("));
    addChild($$, createNode("type_name"));
    addChild($$, createNode(")"));
    addChild($$, $4);
};

multiplicative_expression : cast_expression {
    printf("multiplicative_expression -> cast_expression\n");
    $$ = createNode("multiplicative_expression");
    addChild($$, $1);
}
| multiplicative_expression '*' cast_expression {
    printf("multiplicative_expression -> multiplicative_expression '*' "
           "cast_expression\n");
    $$ = createNode("multiplicative_expression");
    addChild($$, $1);
    addChild($$, createNode("*"));
    addChild($$, $3);
}
| multiplicative_expression '/' cast_expression {
    printf("multiplicative_expression -> multiplicative_expression '/' "
           "cast_expression\n");
    $$ = createNode("multiplicative_expression");
    addChild($$, $1);
    addChild($$, createNode("/"));
    addChild($$, $3);
}
| multiplicative_expression '%' cast_expression {
    printf("multiplicative_expression -> multiplicative_expression '%%' "
           "cast_expression\n");
    $$ = createNode("multiplicative_expression");
    addChild($$, $1);
    addChild($$, createNode("%"));
    addChild($$, $3);
};

additive_expression : multiplicative_expression {
    printf("additive_expression -> multiplicative_expression\n");
    $$ = createNode("additive_expression");
    addChild($$, $1);
}
| additive_expression '+' multiplicative_expression {
    printf("additive_expression -> additive_expression '+' "
           "multiplicative_expression\n");
    $$ = createNode("additive_expression");
    addChild($$, $1);
    addChild($$, createNode("+"));
    addChild($$, $3);
}
| additive_expression '-' multiplicative_expression {
    printf("additive_expression -> additive_expression '-' "
           "multiplicative_expression\n");
    $$ = createNode("additive_expression");
    addChild($$, $1);
    addChild($$, createNode("-"));
    addChild($$, $3);
};

shift_expression : additive_expression {
    printf("shift_expression -> additive_expression\n");
    $$ = createNode("shift_expression");
    addChild($$, $1);
}
| shift_expression LSHIFT additive_expression {
    printf("shift_expression -> shift_expression LSHIFT additive_expression\n");
    $$ = createNode("shift_expression");
    addChild($$, $1);
    addChild($$, createNode("<<"));
    addChild($$, $3);
}
| shift_expression RSHIFT additive_expression {
    printf("shift_expression -> shift_expression RSHIFT additive_expression\n");
    $$ = createNode("shift_expression");
    addChild($$, $1);
    addChild($$, createNode(">>"));
    addChild($$, $3);
};

relational_expression : shift_expression {
    printf("relational_expression -> shift_expression\n");
}
| relational_expression '<' shift_expression {
    printf("relational_expression -> relational_expression '<' "
           "shift_expression\n");
    $$ = createNode("relational_expression");
    addChild($$, $1);
    addChild($$, createNode("<"));
    addChild($$, $3);
}
| relational_expression '>' shift_expression {
    printf("relational_expression -> relational_expression '>' "
           "shift_expression\n");
    $$ = createNode("relational_expression");
    addChild($$, $1);
    addChild($$, createNode(">"));
    addChild($$, $3);
}
| relational_expression LE_OP shift_expression {
    printf("relational_expression -> relational_expression LE_OP "
           "shift_expression\n");
    $$ = createNode("relational_expression");
    addChild($$, $1);
    addChild($$, createNode("<="));
    addChild($$, $3);
}
| relational_expression GE_OP shift_expression {
    printf("relational_expression -> relational_expression GE_OP "
           "shift_expression\n");
    $$ = createNode("relational_expression");
    addChild($$, $1);
    addChild($$, createNode(">="));
    addChild($$, $3);
};

equality_expression : relational_expression {
    printf("equality_expression -> relational_expression\n");
    $$ = createNode("equality_expression");
    addChild($$, $1);
}
| equality_expression EQ_OP relational_expression {
    printf("equality_expression -> equality_expression EQ_OP "
           "relational_expression\n");
    $$ = createNode("equality_expression");
    addChild($$, $1);
    addChild($$, createNode("=="));
    addChild($$, $3);
}
| equality_expression NE_OP relational_expression {
    printf("equality_expression -> equality_expression NE_OP "
           "relational_expression\n");
    $$ = createNode("equality_expression");
    addChild($$, $1);
    addChild($$, createNode("!="));
    addChild($$, $3);
};

AND_expression : equality_expression {
    printf("AND_expression -> equality_expression\n");
    $$ = createNode("AND_expression");
    addChild($$, $1);
}
| AND_expression '&' equality_expression {
    printf("AND_expression -> AND_expression '&' equality_expression\n");
    $$ = createNode("AND_expression");
    addChild($$, $1);
    addChild($$, createNode("&"));
    addChild($$, $3);
};

exclusive_OR_expression : AND_expression {
    printf("exclusive_OR_expression -> AND_expression\n");
    $$ = createNode("exclusive_OR_expression");
    addChild($$, $1);
}
| exclusive_OR_expression '^' AND_expression {
    printf("exclusive_OR_expression -> exclusive_OR_expression '^' "
           "AND_expression\n");
    $$ = createNode("exclusive_OR_expression");
    addChild($$, $1);
    addChild($$, createNode("^"));
    addChild($$, $3);
};

inclusive_OR_expression : exclusive_OR_expression {
    printf("inclusive_OR_expression -> exclusive_OR_expression\n");
    $$ = createNode("inclusive_OR_expression");
    addChild($$, $1);
}
| inclusive_OR_expression '|' exclusive_OR_expression {
    printf("inclusive_OR_expression -> inclusive_OR_expression '|' "
           "exclusive_OR_expression\n");
    $$ = createNode("inclusive_OR_expression");
    addChild($$, $1);
    addChild($$, createNode("|"));
    addChild($$, $3);
};

logical_AND_expression : inclusive_OR_expression {
    printf("logical_AND_expression -> inclusive_OR_expression\n");
    $$ = createNode("logical_AND_expression");
    addChild($$, $1);
}
| logical_AND_expression BINARY_AND inclusive_OR_expression {
    printf("logical_AND_expression -> logical_AND_expression BINARY_AND "
           "inclusive_OR_expression\n");
    $$ = createNode("logical_AND_expression");
    addChild($$, $1);
    addChild($$, createNode("&&"));
    addChild($$, $3);
};

logical_OR_expression : logical_AND_expression {
    printf("logical_OR_expression -> logical_AND_expression\n");
    $$ = createNode("logical_OR_expression");
    addChild($$, $1);
}
| logical_OR_expression BINARY_OR logical_AND_expression {
    printf("logical_OR_expression -> logical_OR_expression BINARY_OR "
           "logical_AND_expression\n");
    $$ = createNode("logical_OR_expression");
    addChild($$, $1);
    addChild($$, createNode("||"));
    addChild($$, $3);
};

conditional_expression : logical_OR_expression {
    printf("conditional_expression -> logical_OR_expression\n");
}
| logical_OR_expression '?' expression ':' conditional_expression {
    printf("conditional_expression -> logical_OR_expression '?' expression ':' "
           "conditional_expression\n");
    $$ = createNode("conditional_expression");
    addChild($$, $1);
    addChild($$, createNode("?"));
    addChild($$, $3);
    addChild($$, createNode(":"));
    addChild($$, $5);
};

assignment_expression : conditional_expression {
    printf("assignment_expression -> conditional_expression\n");
    $$ = createNode("assignment_expression");
    addChild($$, $1);
}
| unary_expression assignment_operator assignment_expression {
    printf("assignment_expression -> unary_expression assignment_operator "
           "assignment_expression\n");
    $$ = createNode("assignment_expression");
    addChild($$, $1);
    addChild($$, $2);
    addChild($$, $3);
};

assignment_expression_optional : assignment_expression {
    printf("assignment_expression_optional -> assignment_expression\n");
    $$ = createNode("assignment_expression_optional");
    addChild($$, $1);
}
| {
    printf("assignment_expression_optional -> ε\n");
    $$ = createNode("assignment_expression_optional");
    addChild($$, createNode("ε"));
};

assignment_operator : '=' {
    printf("assignment_operator -> '='\n");
    $$ = createNode("=");
}
| MUL_ASSIGN {
    printf("assignment_operator -> MUL_ASSIGN\n");
    $$ = createNode("*=");
}
| DIV_ASSIGN {
    printf("assignment_operator -> DIV_ASSIGN\n");
    $$ = createNode("/=");
}
| MOD_ASSIGN {
    printf("assignment_operator -> MOD_ASSIGN\n");
    $$ = createNode("%=");
}
| ADD_ASSIGN {
    printf("assignment_operator -> ADD_ASSIGN\n");
    $$ = createNode("+=");
}
| SUB_ASSIGN {
    printf("assignment_operator -> SUB_ASSIGN\n");
    $$ = createNode("-=");
}
| LEFT_ASSIGN {
    printf("assignment_operator -> LEFT_ASSIGN\n");
    $$ = createNode("<<=");
}
| RIGHT_ASSIGN {
    printf("assignment_operator -> RIGHT_ASSIGN\n");
    $$ = createNode(">>=");
}
| AND_ASSIGN {
    printf("assignment_operator -> AND_ASSIGN\n");
    $$ = createNode("&=");
}
| XOR_ASSIGN {
    printf("assignment_operator -> XOR_ASSIGN\n");
    $$ = createNode("^=");
}
| OR_ASSIGN {
    printf("assignment_operator -> OR_ASSIGN\n");
    $$ = createNode("|=");
};

expression : assignment_expression {
    printf("expression -> assignment_expression\n");
    $$ = createNode("expression");
    addChild($$, $1);
}
| expression ',' assignment_expression {
    printf("expression -> expression ',' assignment_expression\n");
    $$ = createNode("expression");
    addChild($$, $1);
    addChild($$, createNode(","));
    addChild($$, $3);
};

expression_optional : expression {
    printf("expression_optional -> expression\n");
    $$ = createNode("expression_optional");
    addChild($$, $1);
}
| {
    printf("expression_optional -> ε\n");
    $$ = createNode("expression_optional");
    addChild($$, createNode("ε"));
};

constant_expression : conditional_expression {
    printf("constant_expression -> conditional_expression\n");
    $$ = createNode("constant_expression");
    addChild($$, $1);
};

// Declarations
declaration : declaration_specifiers ';' {
    printf("declaration -> declaration_specifiers ';'\n");
    $$ = createNode("declaration");
    addChild($$, $1);
}
| declaration_specifiers init_declarator_list ';' {
    printf("declaration -> declaration_specifiers init_declarator_list ';'\n");
    $$ = createNode("declaration");
    addChild($$, $1);
    addChild($$, $2);
};

declaration_specifiers : storage_class_specifier {
    printf("declaration_specifiers -> storage_class_specifier\n");
    $$ = createNode("declaration_specifiers");
    addChild($$, $1);
}
| storage_class_specifier declaration_specifiers {
    printf("declaration_specifiers -> storage_class_specifier "
           "declaration_specifiers\n");
    $$ = createNode("declaration_specifiers");
    addChild($$, $1);
    addChild($$, $2);
}
| type_specifier {
    printf("declaration_specifiers -> type_specifier\n");
    $$ = createNode("declaration_specifiers");
    addChild($$, $1);
}
| type_specifier declaration_specifiers {
    printf("declaration_specifiers -> type_specifier declaration_specifiers\n");
    $$ = createNode("declaration_specifiers");
    addChild($$, $1);
    addChild($$, $2);
}
| type_qualifier {
    printf("declaration_specifiers -> type_qualifier\n");
    $$ = createNode("declaration_specifiers");
    addChild($$, $1);
}
| type_qualifier declaration_specifiers {
    printf("declaration_specifiers -> type_qualifier declaration_specifiers\n");
    $$ = createNode("declaration_specifiers");
    addChild($$, $1);
    addChild($$, $2);
}
| function_specifier {
    printf("declaration_specifiers -> function_specifier\n");
    $$ = createNode("declaration_specifiers");
    addChild($$, $1);
}
| function_specifier declaration_specifiers {
    printf("declaration_specifiers -> function_specifier "
           "declaration_specifiers\n");
    $$ = createNode("declaration_specifiers");
    addChild($$, $1);
    addChild($$, $2);
};

init_declarator_list : init_declarator {
    printf("init_declarator_list -> init_declarator\n");
    $$ = createNode("init_declarator_list");
    addChild($$, $1);
}
| init_declarator_list ',' init_declarator {
    printf(
        "init_declarator_list -> init_declarator_list ',' init_declarator\n");
    $$ = createNode("init_declarator_list");
    addChild($$, $1);
    addChild($$, createNode(","));
    addChild($$, $3);
};

init_declarator : declarator {
    printf("init_declarator -> declarator\n");
    $$ = createNode("init_declarator");
    addChild($$, $1);
}
| declarator '=' initializer {
    printf("init_declarator -> declarator '=' initializer\n");
    $$ = createNode("init_declarator");
    addChild($$, $1);
    addChild($$, createNode("="));
    addChild($$, $3);
};

storage_class_specifier : EXTERN {
    printf("storage_class_specifier -> EXTERN\n");
    $$ = createNode("storage_class_specifier");
    addChild($$, createNode("EXTERN"));
}
| STATIC {
    printf("storage_class_specifier -> STATIC\n");
    $$ = createNode("storage_class_specifier");
    addChild($$, createNode("STATIC"));
}
| AUTO {
    printf("storage_class_specifier -> AUTO\n");
    $$ = createNode("storage_class_specifier");
    addChild($$, createNode("AUTO"));
}
| REGISTER {
    printf("storage_class_specifier -> REGISTER\n");
    $$ = createNode("storage_class_specifier");
    addChild($$, createNode("REGISTER"));
};

type_specifier : VOID {
    printf("type_specifier -> VOID\n");
    $$ = createNode("type_specifier");
    addChild($$, createNode("VOID"));
}
| CHAR {
    printf("type_specifier -> CHAR\n");
    $$ = createNode("type_specifier");
    addChild($$, createNode("CHAR"));
}
| SHORT {
    printf("type_specifier -> SHORT\n");
    $$ = createNode("type_specifier");
    addChild($$, createNode("SHORT"));
}
| INT {
    printf("type_specifier -> INT\n");
    $$ = createNode("type_specifier");
    addChild($$, createNode("INT"));
}
| LONG {
    printf("type_specifier -> LONG\n");
    $$ = createNode("type_specifier");
    addChild($$, createNode("LONG"));
}
| FLOAT {
    printf("type_specifier -> FLOAT\n");
    $$ = createNode("type_specifier");
    addChild($$, createNode("FLOAT"));
}
| DOUBLE {
    printf("type_specifier -> DOUBLE\n");
    $$ = createNode("type_specifier");
    addChild($$, createNode("DOUBLE"));
}
| SIGNED {
    printf("type_specifier -> SIGNED\n");
    $$ = createNode("type_specifier");
    addChild($$, createNode("SIGNED"));
}
| UNSIGNED {
    printf("type_specifier -> UNSIGNED\n");
    $$ = createNode("type_specifier");
    addChild($$, createNode("UNSIGNED"));
}
| BOOL {
    printf("type_specifier -> BOOL\n");
    $$ = createNode("type_specifier");
    addChild($$, createNode("BOOL"));
}
| IMAGINARY {
    printf("type_specifier -> IMAGINARY\n");
    $$ = createNode("type_specifier");
    addChild($$, createNode("IMAGINARY"));
}
| COMPLEX {
    printf("type_specifier -> COMPLEX\n");
    $$ = createNode("type_specifier");
    addChild($$, createNode("COMPLEX"));
};

specifier_qualifier_list : type_specifier {
    printf("specifier_qualifier_list -> type_specifier\n");
    $$ = createNode("specifier_qualifier_list");
    addChild($$, $1);
}
| type_specifier specifier_qualifier_list {
    printf("specifier_qualifier_list -> type_specifier "
           "specifier_qualifier_list\n");
    $$ = createNode("specifier_qualifier_list");
    addChild($$, $1);
    addChild($$, $2);
}
| type_qualifier {
    printf("specifier_qualifier_list -> type_qualifier\n");
    $$ = createNode("specifier_qualifier_list");
    addChild($$, $1);
}
| type_qualifier specifier_qualifier_list {
    printf("specifier_qualifier_list -> type_qualifier "
           "specifier_qualifier_list\n");
    $$ = createNode("specifier_qualifier_list");
    addChild($$, $1);
    addChild($$, $2);
};

type_qualifier : CONST {
    printf("type_qualifier -> CONST\n");
    $$ = createNode("type_qualifier");
    addChild($$, createNode("CONST"));
}
| RESTRICT {
    printf("type_qualifier -> RESTRICT\n");
    $$ = createNode("type_qualifier");
    addChild($$, createNode("RESTRICT"));
}
| VOLATILE {
    printf("type_qualifier -> VOLATILE\n");
    $$ = createNode("type_qualifier");
    addChild($$, createNode("VOLATILE"));
};

function_specifier : INLINE {
    printf("function_specifier -> INLINE\n");
    $$ = createNode("function_specifier");
    addChild($$, createNode("INLINE"));
};

declarator : pointer direct_declarator {
    printf("declarator -> pointer direct_declarator\n");
    $$ = createNode("declarator");
    addChild($$, $1);
    addChild($$, $2);
}
| direct_declarator {
    printf("declarator -> direct_declarator\n");
    $$ = createNode("declarator");
    addChild($$, $1);
};

direct_declarator : IDENTIFIER {
    printf("direct_declarator -> IDENTIFIER\n");
    $$ = createNode("direct_declarator");
    addChild($$, createNode($1));
}
| '(' declarator ')' {
    printf("direct_declarator -> '(' declarator ')'\n");
    $$ = createNode("direct_declarator");
    addChild($$, createNode("("));
    addChild($$, $2);
    addChild($$, createNode(")"));
}
| direct_declarator '[' type_qualifier_list_optional
        assignment_expression_optional ']' {
    printf("direct_declarator -> direct_declarator '[' "
           "type_qualifier_list_optional assignment_expression_optional']'\n");
    $$ = createNode("direct_declarator");
    addChild($$, $1);
    addChild($$, createNode("["));
    addChild($$, $3);
    addChild($$, $4);
    addChild($$, createNode("]"));
}

| direct_declarator '[' STATIC type_qualifier_list_optional
        assignment_expression ']' {
    printf("direct_declarator -> direct_declarator '[' STATIC "
           "type_qualifier_list_optional assignment_expression ']'\n");
    $$ = createNode("direct_declarator");
    addChild($$, $1);
    addChild($$, createNode("["));
    addChild($$, createNode("STATIC"));
    addChild($$, $4);
    addChild($$, $5);
    addChild($$, createNode("]"));
}
| direct_declarator '[' type_qualifier_list STATIC assignment_expression ']' {
    printf("direct_declarator -> direct_declarator '[' type_qualifier_list "
           "STATIC assignment_expression ']'\n");
    $$ = createNode("direct_declarator");
    addChild($$, $1);
    addChild($$, createNode("["));
    addChild($$, $3);
    addChild($$, createNode("STATIC"));
    addChild($$, $5);
    addChild($$, createNode("]"));
}
| direct_declarator '[' type_qualifier_list_optional '*' ']' {
    printf("direct_declarator -> direct_declarator '[' "
           "type_qualifier_list_optional '*' ']'\n");
    $$ = createNode("direct_declarator");
    addChild($$, $1);
    addChild($$, createNode("["));
    addChild($$, $3);
    addChild($$, createNode("*"));
    addChild($$, createNode("]"));
}
| direct_declarator '(' parameter_type_list ')' {
    printf(
        "direct_declarator -> direct_declarator '(' parameter_type_list ')'\n");
    $$ = createNode("direct_declarator");
    addChild($$, $1);
    addChild($$, createNode("("));
    addChild($$, $3);
    addChild($$, createNode(")"));
}
| direct_declarator '(' identifier_list_optional ')' {
    printf("direct_declarator -> direct_declarator '(' "
           "identifier_list_optional ')'\n");
    $$ = createNode("direct_declarator");
    addChild($$, $1);
    addChild($$, createNode("("));
    addChild($$, $3);
    addChild($$, createNode(")"));
};

pointer : '*' type_qualifier_list_optional {
    printf("pointer -> '*' type_qualifier_list_optional\n");
    $$ = createNode("pointer");
    addChild($$, createNode("*"));
    addChild($$, $2);
}
| '*' type_qualifier_list_optional pointer {
    printf("pointer -> '*' type_qualifier_list_optional pointer\n");
    $$ = createNode("pointer");
    addChild($$, createNode("*"));
    addChild($$, $2);
    addChild($$, $3);
};

type_qualifier_list : type_qualifier {
    printf("type_qualifier_list -> type_qualifier\n");
    $$ = createNode("type_qualifier_list");
    addChild($$, $1);
}
| type_qualifier_list type_qualifier {
    printf("type_qualifier_list -> type_qualifier_list type_qualifier\n");
    $$ = createNode("type_qualifier_list");
    addChild($$, $1);
    addChild($$, $2);
};

type_qualifier_list_optional : type_qualifier_list {
    printf("type_qualifier_list_optional -> type_qualifier_list\n");
    $$ = createNode("type_qualifier_list_optional");
    addChild($$, $1);
}
| {
    printf("type_qualifier_list_optional -> ε\n");
    $$ = createNode("type_qualifier_list_optional");
    addChild($$, createNode("ε"));
};

parameter_type_list : parameter_list {
    printf("parameter_type_list -> parameter_list\n");
}
| parameter_list ',' ELLIPSIS {
    printf("parameter_type_list -> parameter_list ',' ELLIPSIS\n");
};

parameter_list : parameter_declaration {
    printf("parameter_list -> parameter_declaration\n");
    $$ = createNode("parameter_list");
    addChild($$, $1);
}
| parameter_list ',' parameter_declaration {
    printf("parameter_list -> parameter_list ',' parameter_declaration\n");
    $$ = createNode("parameter_list");
    addChild($$, $1);
    addChild($$, createNode(","));
    addChild($$, $3);
};

parameter_declaration : declaration_specifiers declarator {
    printf("parameter_declaration -> declaration_specifiers declarator\n");
    $$ = createNode("parameter_declaration");
    addChild($$, $1);
    addChild($$, $2);
}
| declaration_specifiers {
    printf("parameter_declaration -> declaration_specifiers\n");
    $$ = createNode("parameter_declaration");
    addChild($$, $1);
};

identifier_list : IDENTIFIER {
    printf("identifier_list -> IDENTIFIER\n");
    $$ = createNode("identifier_list");
    addChild($$, createNode($1));
}
| identifier_list ',' IDENTIFIER {
    printf("identifier_list -> identifier_list ',' IDENTIFIER\n");
    $$ = createNode("identifier_list");
    addChild($$, $1);
    addChild($$, createNode(","));
    addChild($$, createNode($3));
};

identifier_list_optional : identifier_list {
    printf("identifier_list_optional -> identifier_list\n");
    $$ = createNode("identifier_list_optional");
    addChild($$, $1);
}
| {
    printf("identifier_list_optional -> ε\n");
    $$ = createNode("identifier_list_optional");
    addChild($$, createNode("ε"));
};

type_name : specifier_qualifier_list {
    printf("type_name -> specifier_qualifier_list\n");
    $$ = createNode("type_name");
    addChild($$, $1);
};

initializer : assignment_expression {
    printf("initializer -> assignment_expression\n");
    $$ = createNode("initializer");
    addChild($$, $1);
}
| '{' initializer_list '}' {
    printf("initializer -> '{' initializer_list '}'\n");
    $$ = createNode("initializer");
    addChild($$, createNode("{"));
    addChild($$, $2);
    addChild($$, createNode("}"));
}
| '{' initializer_list ',' '}' {
    printf("initializer -> '{' initializer_list ',' '}'\n");
    $$ = createNode("initializer");
    addChild($$, createNode("{"));
    addChild($$, $2);
    addChild($$, createNode(","));
    addChild($$, createNode("}"));
};

initializer_list : designation_optional initializer {
    printf("initializer_list -> designation_optional initializer\n");
    $$ = createNode("initializer_list");
    addChild($$, $1);
    addChild($$, $2);
}
| initializer_list ',' designation_optional initializer {
    printf("initializer_list -> initializer_list ',' designation_optional "
           "initializer\n");
    $$ = createNode("initializer_list");
    addChild($$, $1);
    addChild($$, createNode(","));
    addChild($$, $3);
    addChild($$, $4);
};

designation : designator_list '=' {
    printf("designation -> designator_list '='\n");
    $$ = createNode("designation");
    addChild($$, $1);
    addChild($$, createNode("="));
};

designation_optional : designation {
    printf("designation_optional -> designation\n");
    $$ = createNode("designation_optional");
    addChild($$, $1);
}
| {
    printf("designation_optional -> ε\n");
    $$ = createNode("designation_optional");
    addChild($$, createNode("ε"));
};

designator_list : designator {
    printf("designator_list -> designator\n");
    $$ = createNode("designator_list");
    addChild($$, $1);
}
| designator_list designator {
    printf("designator_list -> designator_list designator\n");
    $$ = createNode("designator_list");
    addChild($$, $1);
    addChild($$, $2);
};

designator : '[' constant_expression ']' {
    printf("designator -> '[' constant_expression ']'\n");
    $$ = createNode("designator");
    addChild($$, createNode("["));
    addChild($$, $2);
    addChild($$, createNode("]"));
}
| '.' IDENTIFIER {
    printf("designator -> '.' IDENTIFIER\n");
    $$ = createNode("designator");
    addChild($$, createNode("."));
    addChild($$, createNode($2));
};

// Statements
statement : labeled_statement {
    printf("statement -> labeled_statement\n");
    $$ = createNode("statement");
    addChild($$, $1);
}
| compound_statement {
    printf("statement -> compound_statement\n");
    $$ = createNode("statement");
    addChild($$, $1);
}
| expression_statement {
    printf("statement -> expression_statement\n");
    $$ = createNode("statement");
    addChild($$, $1);
}
| selection_statement {
    printf("statement -> selection_statement\n");
    $$ = createNode("statement");
    addChild($$, $1);
}
| iteration_statement {
    printf("statement -> iteration_statement\n");
    $$ = createNode("statement");
    addChild($$, $1);
}
| jump_statement {
    printf("statement -> jump_statement\n");
    $$ = createNode("statement");
    addChild($$, $1);
};

labeled_statement : IDENTIFIER ':' statement {
    printf("labeled_statement -> IDENTIFIER ':' statement\n");
    $$ = createNode("labeled_statement");
    addChild($$, createNode($1));
    addChild($$, createNode(":"));
    addChild($$, $3);
}
| CASE constant_expression ':' statement {
    printf("labeled_statement -> CASE constant_expression ':' statement\n");
    $$ = createNode("labeled_statement");
    addChild($$, createNode("CASE"));
    addChild($$, $2);
    addChild($$, createNode(":"));
    addChild($$, $4);
}
| DEFAULT ':' statement {
    printf("labeled_statement -> DEFAULT ':' statement\n");
    $$ = createNode("labeled_statement");
    addChild($$, createNode("DEFAULT"));
    addChild($$, createNode(":"));
    addChild($$, $3);
};

compound_statement : '{' block_item_list_optional '}' {
    printf("compound_statement -> '{' block_item_list_optional '}'\n");
    $$ = createNode("compound_statement");
    addChild($$, createNode("{"));
    addChild($$, $2);
    addChild($$, createNode("}"));
};

block_item_list : block_item {
    printf("block_item_list -> block_item\n");
    $$ = createNode("block_item_list");
    addChild($$, $1);
}
| block_item_list block_item {
    printf("block_item_list -> block_item_list block_item\n");
    $$ = createNode("block_item_list");
    addChild($$, $1);
    addChild($$, $2);
};

block_item_list_optional : block_item_list {
    printf("block_item_list_optional -> block_item_list\n");
    $$ = createNode("block_item_list_optional");
    addChild($$, $1);
}
| {
    printf("block_item_list_optional -> ε\n");
    $$ = createNode("block_item_list_optional");
    addChild($$, createNode("ε"));
};

block_item : declaration {
    printf("block_item -> declaration\n");
    $$ = createNode("block_item");
    addChild($$, $1);
}
| statement {
    printf("block_item -> statement\n");
    $$ = createNode("block_item");
    addChild($$, $1);
};

expression_statement : expression_optional ';' {
    printf("expression_statement -> expression_optional ';'\n");
    $$ = createNode("expression_statement");
    addChild($$, $1);
    addChild($$, createNode(";"));
};

selection_statement : IF '(' expression ')' statement %prec LOWER_THAN_ELSE {
    printf("selection_statement -> IF '(' expression ')' statement\n");
    $$ = createNode("selection_statement");
    addChild($$, createNode("IF"));
    addChild($$, createNode("("));
    addChild($$, $3);
    addChild($$, createNode(")"));
    addChild($$, $5);
}
| IF '(' expression ')' statement ELSE statement {
    printf("selection_statement -> IF '(' expression ')' statement ELSE "
           "statement\n");
    $$ = createNode("selection_statement");
    addChild($$, createNode("IF"));
    addChild($$, createNode("("));
    addChild($$, $3);
    addChild($$, createNode(")"));
    addChild($$, $5);
    addChild($$, createNode("ELSE"));
    addChild($$, $7);
}
| SWITCH '(' expression ')' statement {
    printf("selection_statement -> SWITCH '(' expression ')' statement\n");
    $$ = createNode("selection_statement");
    addChild($$, createNode("SWITCH"));
    addChild($$, createNode("("));
    addChild($$, $3);
    addChild($$, createNode(")"));
    addChild($$, $5);
};

iteration_statement : WHILE '(' expression ')' statement {
    printf("iteration_statement -> WHILE '(' expression ')' statement\n");
    $$ = createNode("iteration_statement");
    addChild($$, createNode("WHILE"));
    addChild($$, createNode("("));
    addChild($$, $3);
    addChild($$, createNode(")"));
    addChild($$, $5);
}
| DO statement WHILE '(' expression ')' ';' {
    printf(
        "iteration_statement -> DO statement WHILE '(' expression ')' ';'\n");
    $$ = createNode("iteration_statement");
    addChild($$, createNode("DO"));
    addChild($$, $2);
    addChild($$, createNode("WHILE"));
    addChild($$, createNode("("));
    addChild($$, $5);
    addChild($$, createNode(")"));
    addChild($$, createNode(";"));
}
| FOR '(' expression_optional ';' expression_optional ';' expression_optional ')' statement {
    printf("iteration_statement -> FOR '(' expression_optional ';' "
           "expression_optional ';' expression_optional ')' statement\n");
    $$ = createNode("iteration_statement");
    addChild($$, createNode("FOR"));
    addChild($$, createNode("("));
    addChild($$, $3);
    addChild($$, createNode(";"));
    addChild($$, $5);
    addChild($$, createNode(";"));
    addChild($$, $7);
    addChild($$, createNode(")"));
    addChild($$, $9);
}
| FOR '(' declaration
        expression_optional ';' expression_optional ')' statement {
    printf("iteration_statement -> FOR '(' declaration expression_optional ';' "
           "expression_optional ')' statement\n");
    $$ = createNode("iteration_statement");
    addChild($$, createNode("FOR"));
    addChild($$, createNode("("));
    addChild($$, $3);
    addChild($$, $4);
    addChild($$, createNode(";"));
    addChild($$, $6);
    addChild($$, createNode(")"));
    addChild($$, $8);
};

jump_statement : GOTO IDENTIFIER ';' {
    printf("jump_statement -> GOTO IDENTIFIER ';'\n");
    $$ = createNode("jump_statement");
    addChild($$, createNode("GOTO"));
    addChild($$, createNode($2));
    addChild($$, createNode(";"));
}
| CONTINUE ';' {
    printf("jump_statement -> CONTINUE ';'\n");
    $$ = createNode("jump_statement");
    addChild($$, createNode("CONTINUE"));
    addChild($$, createNode(";"));
}
| BREAK ';' {
    printf("jump_statement -> BREAK ';'\n");
    $$ = createNode("jump_statement");
    addChild($$, createNode("BREAK"));
    addChild($$, createNode(";"));
}
| RETURN expression_optional ';' {
    printf("jump_statement -> RETURN expression_optional ';'\n");
    $$ = createNode("jump_statement");
    addChild($$, createNode("RETURN"));
    addChild($$, $2);
    addChild($$, createNode(";"));
};

// External Definitions
translation_unit : external_declaration {
    printf("translation_unit -> external_declaration\n");
    $$ = createNode("translation_unit");
    addChild($$, $1);
}
| translation_unit external_declaration {
    printf("translation_unit -> translation_unit external_declaration\n");
    $$ = createNode("translation_unit");
    addChild($$, $1);
    addChild($$, $2);
};

external_declaration : function_definition {
    printf("external_declaration -> function_definition\n");
    $$ = createNode("external_declaration");
    addChild($$, $1);
}
| declaration {
    printf("external_declaration -> declaration\n");
    $$ = createNode("external_declaration");
    addChild($$, $1);
};

function_definition : declaration_specifiers declarator
                          declaration_list_optional compound_statement {
    printf("function_definition -> declaration_specifiers declarator "
           "declaration_list_optional compound_statement\n");
    $$ = createNode("function_definition");
    addChild($$, $1);
    addChild($$, $2);
    addChild($$, $3);
    addChild($$, $4);
};

declaration_list : declaration {
    printf("declaration_list -> declaration\n");
    $$ = createNode("declaration_list");
    addChild($$, $1);
}
| declaration_list declaration {
    printf("declaration_list -> declaration_list declaration\n");
    $$ = createNode("declaration_list");
    addChild($$, $1);
    addChild($$, $2);
};

declaration_list_optional : declaration_list {
    printf("declaration_list_optional -> declaration_list\n");
    $$ = createNode("declaration_list_optional");
    addChild($$, $1);
}
| {
    printf("declaration_list_optional -> ε\n");
    $$ = createNode("declaration_list_optional");
    addChild($$, createNode("ε"));
};

program : translation_unit {
    printf("program -> translation_unit\n");
    $$ = createNode("program");
    addChild($$, $1);
    root = $$;
    return 0;
};