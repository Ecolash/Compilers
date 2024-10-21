%{
    #include <iostream>
    using namespace std;

    extern int yylex(); // in lex.yy.c : Lexical analyser
    extern int yylineno; // in lex.yy.c : Line number
    extern char *yytext;    // in lex.yy.c : Identified lexeme
    void yyerror(const string &s);  // in lex.yy.c : Error function
    extern string data_type; // in asgn5_21CS10005_21CS30031_translator.cxx : Stores the data type of the current variable
%}

%union {
    int iValue;     // Integer value
    char *sValue;   // String value
    symbol *symb;       // Symbol
    symbolType *symbType;   // Symbol type
    E *expr;   // Expression
    S *statem;  // Statement
    A *arr; // Array
    int instr_ind;  // Keep track of instruction number
    char unary_op;  // Unary operator
    int param_count;   // Parameter count for functions
}

%code requires {
    #include "translator.h"
}

// TOKENS
%token AUTO ENUM RESTRICT UNSIGNED BREAK EXTERN RETURN VOID CASE FLOAT SHORT VOLATILE CHAR FOR SIGNED WHILE CONST GOTO SIZEOF BOOL CONTINUE IF STATIC COMPLEX DEFAULT INLINE STRUCT IMAGINARY DO INT SWITCH DOUBLE LONG TYPEDEF ELSE REGISTER UNION INVALID_TOKEN
%token PARANTHESIS_OPEN PARANTHESIS_CLOSE SQ_BRACKET_OPEN SQ_BRACKET_CLOSE CURLY_BRACKET_OPEN CURLY_BRACKET_CLOSE
%token PERIOD ARROW INCREMENT DECREMENT AMPERSAND ASTERISK PLUS MINUS TILDE EXCLAMATION SLASH PERCENT
%token LEFT_SHIFT RIGHT_SHIFT LESS_THAN GREATER_THAN LESS_THAN_EQUAL GREATER_THAN_EQUAL EQUAL NOT_EQUAL CARET PIPE
%token LOGICAL_AND LOGICAL_OR QUESTION COLON SEMICOLON ELLIPSIS
%token ASSIGN MULTIPLY_ASSIGN DIVIDE_ASSIGN MOD_ASSIGN PLUS_ASSIGN MINUS_ASSIGN LEFT_SHIFT_ASSIGN RIGHT_SHIFT_ASSIGN AND_ASSIGN XOR_ASSIGN OR_ASSIGN COMMA HASH

%token <symb> IDENTIFIER    // Identifier, taken as symbol
%token <iValue> CONSTANT_INT    // Integer constant
%token <sValue> CONSTANT_FLOAT  // Floating point constant
%token <sValue> CONSTANT_CHAR   // Character constant
%token <sValue> LITERAL // String literal

%start translation_unit

%right THEN ELSE    // Checks if Else can be matched with If

/* Types for all non-terminals */
%type <unary_op> unary_operator // Unary operator non-terminals
%type <param_count> argument_expression_list argument_expression_list_opt   // Number of parameters non-terminals
%type <expr> expression primary_expression multiplicative_expression additive_expression shift_expression relational_expression equality_expression AND_expression exclusive_OR_expression inclusive_OR_expression logical_AND_expression logical_OR_expression conditional_expression assignment_expression expression_statement   // Expression type non-terminals
%type <statem> statement labeled_statement compound_statement selection_statement iteration_statement jump_statement loop_statement block_item block_item_list block_item_list_opt  // Statement type non-terminals
%type <symbType> pointer   // Pointer non-terminal
%type <symb> constant initializer direct_declarator init_declarator declarator  // Symbol non-terminals
%type <arr> postfix_expression unary_expression cast_expression // Array non-terminals
%type <instr_ind> M // Augmented non-terminal to help with backpatching by storing next instruction index
%type <statem> N    // Augmented non-terminal to help with control flow

%%


primary_expression  : IDENTIFIER    {
                        $$ = new E();  // New expression
                        $$->addr = $1;      // Store pointer in Symbol Table
                        $$->exprType = "not_bool";   // Non bool expression
                    }
                    | constant      {
                        $$ = new E();  // New expression
                        $$->addr = $1;      // Store pointer in Symbol Table
                    }
                    | LITERAL       {
                        $$ = new E();  // New expression
                        $$->addr = symbolTable::gentemp(new symbolType("ptr"), $1); // Create new temp with type ptr and store value
                        $$->addr->type->arrType = new symbolType("char");
                    }
                    | PARANTHESIS_OPEN expression PARANTHESIS_CLOSE { $$ = $2; } // Assignment
                    ;

constant            : CONSTANT_INT  {
                        $$ = symbolTable::gentemp(new symbolType("int"), convIntToStr($1)); // Create new temp with type int and store value
                        emit("=", $$->name, $1);
                    }
                    | CONSTANT_FLOAT{
                        $$ = symbolTable::gentemp(new symbolType("float"), string($1));  // Create new temp with type double and store value
                        emit("=", $$->name, string($1));
                    }
                    | CONSTANT_CHAR {
                        $$ = symbolTable::gentemp(new symbolType("char"), string($1));   // Create new temp with type char and store value
                        emit("=", $$->name, string($1));
                    }
                    ;

postfix_expression  : primary_expression {
                        $$ = new A();   // New Array
                        $$->location = $1->addr;   // Store pointer in Symbol Table
                        $$->type = $1->addr->type;  // Update type
                        $$->addr = $$->location;   // Update location
                    }
                    | postfix_expression SQ_BRACKET_OPEN expression SQ_BRACKET_CLOSE {
                        $$ = new A();   // New Array
                        $$->type = $1->type->arrType;   // Update type
                        $$->location = $1->location;  // Copy the incoming symbol
                        $$->addr = symbolTable::gentemp(new symbolType("int")); // Create new temp with type int and store in location which will have the address of the array element
                        $$->arrType = "arr"; // A type is array

                        if ($1->arrType == "arr") { // Array of array
                            symbol* temp = symbolTable::gentemp(new symbolType("int")); // Create new temp with type int and store in temp
                            int sz = sizeOfType($$->type);  // Get size of type of current
                            emit("*", temp->name, $3->addr->name, convIntToStr(sz)); // temp = expression * sz
                            emit("+", $$->addr->name, $1->addr->name, temp->name); // post = post1 + temp
                        }
                        else {
                            int sz = sizeOfType($$->type);  // Get size of type of current
                            emit("*", $$->addr->name, $3->addr->name, convIntToStr(sz)); // post = expression * sz
                        }
                    }
                    | postfix_expression PARANTHESIS_OPEN argument_expression_list_opt PARANTHESIS_CLOSE {
                        $$ = new A();   // Make new array
                        $$->location = symbolTable::gentemp($1->type); // Get return type
                        emit("call", $$->location->name, $1->location->name, convIntToStr($3)); // call name param_count
                    }
                    | postfix_expression PERIOD IDENTIFIER {}
                    | postfix_expression ARROW IDENTIFIER {}
                    | postfix_expression INCREMENT {
                        $$ = new A();   // Make new array
                        $$->location = symbolTable::gentemp($1->location->type);    // Make new temp with type of current
                        emit("=", $$->location->name, $1->location->name);    // post = post1
                        emit("+", $1->location->name, $1->location->name, "1");   // post1 = post1 + 1
                    }
                    | postfix_expression DECREMENT {
                        $$ = new A();   // Make new array
                        $$->location = symbolTable::gentemp($1->location->type);    // Make new temp with type of current
                        emit("=", $$->location->name, $1->location->name);    // post = post1
                        emit("-", $1->location->name, $1->location->name, "1");   // post1 = post1 - 1
                    }
                    | PARANTHESIS_OPEN type_name PARANTHESIS_CLOSE CURLY_BRACKET_OPEN initializer_list CURLY_BRACKET_CLOSE {}
                    | PARANTHESIS_OPEN type_name PARANTHESIS_CLOSE CURLY_BRACKET_OPEN initializer_list COMMA CURLY_BRACKET_CLOSE {}
                    ;

argument_expression_list_opt : argument_expression_list {$$ = $1;} // Copy the number of parameters
                            | %empty {$$ = 0;}   // No parameters
                            ;

argument_expression_list    : assignment_expression {
                                $$ = 1;
                                emit("param", $1->addr->name);  // Emit param
                            }
                            | argument_expression_list COMMA assignment_expression {
                                $$ = $1 + 1;
                                emit("param", $3->addr->name);  // Emit param
                            }
                            ;

unary_expression    : postfix_expression { $$ = $1; } // Pass the expression
                    | INCREMENT unary_expression {
                        emit("+", $2->location->name, $2->location->name, "1");   // unary1 = unary1 + 1
                        $$ = $2;    // unary = unary1
                    }
                    | DECREMENT unary_expression {
                        emit("-", $2->location->name, $2->location->name, "1");   // unary1 = unary1 - 1
                        $$ = $2;
                    }
                    | unary_operator cast_expression {
                        $$ = new A();
                        if ($1 == '&') {
                            $$->location = symbolTable::gentemp(new symbolType("ptr")); // Create new temp with type ptr and store in addr
                            $$->location->type->arrType = $2->location->type;
                            emit("= &", $$->location->name, $2->location->name); // unary = &unary1
                        }
                        else if ($1 == '*') {
                            $$->arrType = "ptr"; // Pointer type
                            $$->addr = symbolTable::gentemp($2->location->type->arrType); // Create new temp with type of current and store in location
                            $$->location = $2->location;    // Copy the incoming symbol
                            emit("= *", $$->addr->name, $2->location->name); // unary = *unary1
                        }
                        else if ($1 == '+') $$ = $2;
                        else if ($1 == '-') {
                            $$->location = symbolTable::gentemp(new symbolType($2->location->type->base)); // Create new temp with type of current and store in addr
                            emit("= -", $$->location->name, $2->location->name); // unary = $1 unary1
                        }
                        else if ($1 == '~')  {
                            $$->location = symbolTable::gentemp(new symbolType($2->location->type->base)); // Create new temp with type of current and store in addr
                            emit("= ~", $$->location->name, $2->location->name); // unary = $1 unary1
                        }
                        else if ($1 == '!') {
                            $$->location = symbolTable::gentemp(new symbolType($2->location->type->base)); // Create new temp with type of current and store in addr
                            emit("= !", $$->location->name, $2->location->name); // unary = $1 unary1
                        }
                    }
                    | SIZEOF unary_expression {}
                    | SIZEOF PARANTHESIS_OPEN type_name PARANTHESIS_CLOSE {}
                    ;

unary_operator      : AMPERSAND {$$ = '&';}
                    | ASTERISK  {$$ = '*';}
                    | PLUS      {$$ = '+';}
                    | MINUS     {$$ = '-';}
                    | TILDE     {$$ = '~';}
                    | EXCLAMATION {$$ = '!';}
                    ;

cast_expression     : unary_expression {$$ =  $1;} 
                    | PARANTHESIS_OPEN type_name PARANTHESIS_CLOSE cast_expression {
                        $$ = new A();
                        $$->location = convType($4->location, data_type);
                    }
                    ;

multiplicative_expression : cast_expression {
                            $$ = new E(); // new expression
                            if ($1->arrType == "arr") {
                                $$->addr = symbolTable::gentemp($1->addr->type); // Create new temp with type of current and store in addr
                                emit("=[]", $$->addr->name, $1->location->name, $1->addr->name); // multexpr = castexpr [ castexpr->Array->name ]
                            }
                            else if($1->arrType == "ptr") {
                                $$->addr = $1->addr; // Copy the incoming symbol
                            }
                            else $$->addr = $1->location; // Copy the incoming symbol
                          }
                          | multiplicative_expression ASTERISK cast_expression {
                            if (typecheck($1->addr, $3->location)) {
                                $$ = new E();
                                $$->addr = symbolTable::gentemp(new symbolType($1->addr->type->base)); // Create new temp with type int and store in addr
                                emit("*", $$->addr->name, $1->addr->name, $3->location->name); // multexpr = multexpr1 * castexpr
                            }
                            else {
                                yyerror("Type mismatch");
                            }
                          }
                          | multiplicative_expression SLASH cast_expression {
                            if (typecheck($1->addr, $3->location)) {
                                $$ = new E();
                                $$->addr = symbolTable::gentemp(new symbolType($1->addr->type->base)); // Create new temp with type int and store in addr
                                emit("/", $$->addr->name, $1->addr->name, $3->location->name); // multexpr = multexpr1 / castexpr
                            }
                            else {
                                yyerror("Type mismatch");
                            }
                          }
                          | multiplicative_expression PERCENT cast_expression {
                            if (typecheck($1->addr, $3->location)) {
                                $$ = new E();
                                $$->addr = symbolTable::gentemp(new symbolType($1->addr->type->base)); // Create new temp with type int and store in addr
                                emit("%", $$->addr->name, $1->addr->name, $3->location->name); // multexpr = multexpr1 % castexpr
                            }
                            else {
                                yyerror("Type mismatch");
                            }
                          }
                          ;

additive_expression : multiplicative_expression { $$ = $1; } // Pass 
                    | additive_expression PLUS multiplicative_expression {
                        if (typecheck($1->addr, $3->addr)) {
                            $$ = new E();
                            $$->addr = symbolTable::gentemp(new symbolType($1->addr->type->base)); // Create new temp with type int and store in addr
                            emit("+", $$->addr->name, $1->addr->name, $3->addr->name); // addexpr = addexpr1 + multexpr
                        }
                        else {
                            yyerror("Type mismatch");
                        }
                    }
                    | additive_expression MINUS multiplicative_expression {
                        if (typecheck($1->addr, $3->addr)) {
                            $$ = new E();
                            $$->addr = symbolTable::gentemp(new symbolType($1->addr->type->base)); // Create new temp with type int and store in addr
                            emit("-", $$->addr->name, $1->addr->name, $3->addr->name); // addexpr = addexpr1 - multexpr
                        }
                        else {
                            yyerror("Type mismatch");
                        }
                    }
                    ;

shift_expression    : additive_expression {$$ = $1;} // Pass
                    | shift_expression LEFT_SHIFT additive_expression {
                        if ($3->addr->type->base == "int") {
                            $$ = new E();
                            $$->addr = symbolTable::gentemp(new symbolType("int")); // Create new temp with type int and store in addr
                            emit("<<", $$->addr->name, $1->addr->name, $3->addr->name); // shiftexpr = shiftexpr1 << addexpr
                        }
                        else {
                            yyerror("Type mismatch");
                        }
                    }
                    | shift_expression RIGHT_SHIFT additive_expression {
                        if ($3->addr->type->base == "int") {
                            $$ = new E();
                            $$->addr = symbolTable::gentemp(new symbolType("int")); // Create new temp with type int and store in addr
                            emit(">>", $$->addr->name, $1->addr->name, $3->addr->name); // shiftexpr = shiftexpr1 >> addexpr
                        }
                        else {
                            yyerror("Type mismatch");
                        }
                    }
                    ;

relational_expression   : shift_expression { $$ = $1; }
                        | relational_expression LESS_THAN shift_expression {
                            if (typecheck($1->addr, $3->addr)) {
                                $$ = new E();
                                $$->exprType = "bool";   // Boolean type
                                $$->trueList = makelist(nextinstr()); // Make list of next instruction
                                $$->falseList = makelist(nextinstr()+1); // Make list of next instruction
                                emit("<", "", $1->addr->name, $3->addr->name); // if relexpr < shiftexpr
                                emit("goto", ""); // goto
                            }
                            else {
                                yyerror("Type mismatch");
                            }
                        }
                        | relational_expression GREATER_THAN shift_expression {
                            if (typecheck($1->addr, $3->addr)) {
                                $$ = new E();
                                $$->exprType = "bool";   // Boolean type
                                $$->trueList = makelist(nextinstr()); // Make list of next instruction
                                $$->falseList = makelist(nextinstr()+1); // Make list of next instruction
                                emit(">", "", $1->addr->name, $3->addr->name); // if relexpr > shiftexpr
                                emit("goto", ""); // goto
                            }
                            else {
                                yyerror("Type mismatch");
                            }
                        }
                        | relational_expression LESS_THAN_EQUAL shift_expression {
                            if (typecheck($1->addr, $3->addr)) {
                                $$ = new E();
                                $$->exprType = "bool";   // Boolean type
                                $$->trueList = makelist(nextinstr()); // Make list of next instruction
                                $$->falseList = makelist(nextinstr()+1); // Make list of next instruction
                                emit("<=", "", $1->addr->name, $3->addr->name); // if relexpr <= shiftexpr
                                emit("goto", ""); // goto
                            }
                            else {
                                yyerror("Type mismatch");
                            }
                        }
                        | relational_expression GREATER_THAN_EQUAL shift_expression {
                            if (typecheck($1->addr, $3->addr)) {
                                $$ = new E();
                                $$->exprType = "bool";   // Boolean type
                                $$->trueList = makelist(nextinstr()); // Make list of next instruction
                                $$->falseList = makelist(nextinstr()+1); // Make list of next instruction
                                emit(">=", "", $1->addr->name, $3->addr->name); // if relexpr >= shiftexpr
                                emit("goto", ""); // goto
                            }
                            else {
                                yyerror("Type mismatch");
                            }
                        }
                        ;

equality_expression : relational_expression {$$ = $1;} // Pass
                    | equality_expression EQUAL relational_expression {
                        if (typecheck($1->addr, $3->addr)) {
                            convBoolToInt($1);
                            convBoolToInt($3);
                            $$ = new E();
                            $$->exprType = "bool";   // Boolean type
                            $$->trueList = makelist(nextinstr()); // Make list of next instruction
                            $$->falseList = makelist(nextinstr()+1); // Make list of next instruction
                            emit("==", "", $1->addr->name, $3->addr->name); // if eqexpr == relexpr
                            emit("goto", ""); // goto
                        }
                        else {
                            yyerror("Type mismatch");
                        }
                    }
                    | equality_expression NOT_EQUAL relational_expression {
                        if (typecheck($1->addr, $3->addr)) {
                            convBoolToInt($1);
                            convBoolToInt($3);
                            $$ = new E();
                            $$->exprType = "bool";   // Boolean type
                            $$->trueList = makelist(nextinstr()); // Make list of next instruction
                            $$->falseList = makelist(nextinstr()+1); // Make list of next instruction
                            emit("!=", "", $1->addr->name, $3->addr->name); // if eqexpr != relexpr
                            emit("goto", ""); // goto
                        }
                        else {
                            yyerror("Type mismatch");
                        }
                    }
                    ;

AND_expression      : equality_expression {$$ = $1;} // Pass
                    | AND_expression AMPERSAND equality_expression {
                        if (typecheck($1->addr, $3->addr)) {
                            convBoolToInt($1);
                            convBoolToInt($3);
                            $$ = new E();
                            $$->exprType = "not_bool"; // Not boolean
                            $$->addr = symbolTable::gentemp(new symbolType("int")); // Create new temp with type int and store in addr
                            emit("&", $$->addr->name, $1->addr->name, $3->addr->name); // andexpr = andexpr1 & eqexpr
                        }
                        else {
                            yyerror("Type mismatch");
                        }
                    }
                    ;
            
exclusive_OR_expression : AND_expression {$$ = $1;} // Pass
                        | exclusive_OR_expression CARET AND_expression {
                            if (typecheck($1->addr, $3->addr)) {
                                convBoolToInt($1);
                                convBoolToInt($3);
                                $$ = new E();
                                $$->exprType = "not_bool"; // Not boolean
                                $$->addr = symbolTable::gentemp(new symbolType("int")); // Create new temp with type int and store in addr
                                emit("^", $$->addr->name, $1->addr->name, $3->addr->name); // xorexpr = xorexpr1 ^ andexpr
                            }
                            else {
                                yyerror("Type mismatch");
                            }
                        }
                        ;

inclusive_OR_expression : exclusive_OR_expression {$$ = $1;} // Pass
                        | inclusive_OR_expression PIPE exclusive_OR_expression {
                            if (typecheck($1->addr, $3->addr)) {
                                convBoolToInt($1);
                                convBoolToInt($3);
                                $$ = new E();
                                $$->exprType = "not_bool"; // Not boolean
                                $$->addr = symbolTable::gentemp(new symbolType("int")); // Create new temp with type int and store in addr
                                emit("|", $$->addr->name, $1->addr->name, $3->addr->name); // orexpr = orexpr1 | xorexpr
                            }
                            else {
                                yyerror("Type mismatch");
                            }
                        }
                        ;

logical_AND_expression  : inclusive_OR_expression {$$ = $1;} // Pass
                        | logical_AND_expression LOGICAL_AND M inclusive_OR_expression {    // M is augmented non-terminal
                            convIntToBool($1);
                            convIntToBool($4);
                            $$ = new E();
                            $$->exprType = "bool";   // Boolean type
                            backpatch($1->trueList, $3); // Backpatch
                            $$->trueList = $4->trueList; // Copy true list
                            $$->falseList = merge($1->falseList, $4->falseList); // Merge false lists
                        }
                        ;

logical_OR_expression   : logical_AND_expression {$$ = $1;} // Pass
                        | logical_OR_expression LOGICAL_OR M logical_AND_expression {   // M is augmented non-terminal
                            convIntToBool($1);
                            convIntToBool($4);
                            $$ = new E();
                            $$->exprType = "bool";   // Boolean type
                            backpatch($1->falseList, $3); // Backpatch
                            $$->falseList = $4->falseList; // Copy false list
                            $$->trueList = merge($1->trueList, $4->trueList); // Merge true lists
                        }
                        ;

conditional_expression  : logical_OR_expression {$$ = $1;} // Pass
                        | logical_OR_expression N QUESTION M expression N COLON M conditional_expression {  // M and N are augmented non-terminals
                            $$->addr = symbolTable::gentemp($5->addr->type); // Create new temp with type of current and store in addr
                            $$->addr->update($5->addr->type);
                            emit("=", $$->addr->name, $9->addr->name); // condexpr = condexpr1
                            list <int> templist1 = makelist(nextinstr());
                            emit("goto", "");   // goto
                            backpatch($6->nextList, nextinstr());   // For N2
                            emit("=", $$->addr->name, $5->addr->name); // condexpr = expr
                            list <int> templist2 = makelist(nextinstr());
                            templist1 = merge(templist1, templist2);
                            emit("goto", "");   // goto
                            backpatch($2->nextList, nextinstr());   // For N1
                            convIntToBool($1);
                            backpatch($1->trueList, $4); // Backpatch to M1 when true
                            backpatch($1->falseList, $8); // Backpatch to M2 when false
                            backpatch(templist1, nextinstr());
                        }
                        ;

/* AUGMENTED EMPTY NON-TERMINALS */
M: %empty { $$ = nextinstr(); } // Has next instruction for backpatching

N: %empty { $$ = new S(); $$->nextList = makelist(nextinstr()); emit("goto", ""); } // Has next list for control flow

assignment_expression   : conditional_expression {$$ = $1;} // Pass
                        | unary_expression assignment_operator assignment_expression {
                            if ($1->arrType == "arr") { // convert array
                                $3->addr = convType($3->addr, $1->type->base);
                                emit("[]=", $1->location->name, $1->addr->name, $3->addr->name); // unary[unary1] = asgnexpr1
                            }
                            else if ($1->arrType == "ptr") emit("*=", $1->location->name, $3->addr->name);  // Pointer type, *unary = asgnexpr1
                            else {
                                $3->addr = convType($3->addr, $1->location->type->base);
                                emit("=", $1->location->name, $3->addr->name); // unary = asgnexpr1
                            }
                            $$ = $3;
                        }
                        ;

assignment_operator     : ASSIGN {}
                        | MULTIPLY_ASSIGN {}
                        | DIVIDE_ASSIGN {}
                        | MOD_ASSIGN {}
                        | PLUS_ASSIGN {}
                        | MINUS_ASSIGN {}
                        | LEFT_SHIFT_ASSIGN {}
                        | RIGHT_SHIFT_ASSIGN {}
                        | AND_ASSIGN {}
                        | XOR_ASSIGN {}
                        | OR_ASSIGN {}
                        ;

expression  : assignment_expression {$$ = $1;} // Pass
            | expression COMMA assignment_expression {}
            ;

constant_expression : conditional_expression {}
                    ;



declaration : declaration_specifiers init_declarator_list SEMICOLON {}
            | declaration_specifiers SEMICOLON {}
            ;

declaration_specifiers  : storage_class_specifier declaration_specifiers {}
                        | storage_class_specifier {}
                        | type_specifier declaration_specifiers {}
                        | type_specifier {}
                        | type_qualifier declaration_specifiers {}
                        | type_qualifier {}
                        | function_specifier declaration_specifiers {}
                        | function_specifier {}
                        ;

init_declarator_list: init_declarator_list COMMA init_declarator {}
                    | init_declarator {}
                    ;

init_declarator : declarator {$$ = $1;} // Pass
                | declarator ASSIGN initializer {
                    if ($3->initValue != "") $1->initValue = $3->initValue;
                    emit("=", $1->name, $3->name);
                }
                ;

storage_class_specifier : EXTERN {}
                        | STATIC {}
                        | AUTO {}
                        | REGISTER {}
                        ;

// Void, char, int and float are the only valid data types to be provided.
type_specifier  : VOID {data_type = "void";}
                | CHAR {data_type = "char";}
                | SHORT {}
                | INT {data_type = "int";}
                | LONG {}
                | FLOAT {data_type = "float";}
                | DOUBLE {}
                | SIGNED {}
                | UNSIGNED {}
                | BOOL {}
                | COMPLEX {}
                | IMAGINARY {}
                | enum_specifier {}
                ;

specifier_qualifier_list    : type_specifier specifier_qualifier_list_opt {}
                            | type_qualifier specifier_qualifier_list_opt {}
                            ;

specifier_qualifier_list_opt    : specifier_qualifier_list {}
                                | %empty {}
                                ;

enum_specifier  : ENUM identifier_opt CURLY_BRACKET_OPEN enumerator_list CURLY_BRACKET_CLOSE {}
                | ENUM identifier_opt CURLY_BRACKET_OPEN enumerator_list COMMA CURLY_BRACKET_CLOSE {}
                | ENUM IDENTIFIER {}
                ;

identifier_opt  : IDENTIFIER {}
                | %empty {}
                ;

enumerator_list : enumerator {}
                | enumerator_list COMMA enumerator {}
                ;
// can't use CONSTANT_ENUM as it would conflict with IDENTIFIER
enumerator  : IDENTIFIER {}
            | IDENTIFIER ASSIGN constant_expression {}
            ;

type_qualifier  : CONST {}
                | RESTRICT {}
                | VOLATILE {}
                ;

function_specifier  : INLINE {}
                    ;

declarator  : pointer direct_declarator {
                symbolType* t = $1;
                while(t->arrType != NULL) t = t->arrType;   // Multidimensional array, go to last dimension
                t->arrType = $2->type;  // Assign type
                $$ = $2->update($1);    // Update
            }
            | direct_declarator {}
            ;

direct_declarator   : IDENTIFIER {
                        $$ = $1->update(new symbolType(data_type));   // Get data type of identifier
                        currentSymbol = $1; // Update current symbol
                    }
                    | PARANTHESIS_OPEN declarator PARANTHESIS_CLOSE { $$ = $2;} // Assignment
                    | direct_declarator SQ_BRACKET_OPEN type_qualifier_list assignment_expression SQ_BRACKET_CLOSE {}
                    | direct_declarator SQ_BRACKET_OPEN type_qualifier_list SQ_BRACKET_CLOSE {} 
                    | direct_declarator SQ_BRACKET_OPEN assignment_expression SQ_BRACKET_CLOSE {
                        symbolType* t = $1->type;
                        symbolType* prev = NULL;
                        while(t->base == "arr") {
                            prev = t;
                            t = t->arrType;
                        }
                        if (prev == NULL) {
                            int temp = atoi($3->addr->initValue.c_str());   // Init value
                            symbolType* tp = new symbolType("arr", $1->type, temp);   // Create new array type
                            $$ = $1->update(tp);    // Update
                        }
                        else {
                            int temp = atoi($3->addr->initValue.c_str());   // Init value
                            prev->arrType = new symbolType("arr", t, temp);  // Create new array type
                            $$ = $1->update($1->type);  // Update
                        }
                    }
                    | direct_declarator SQ_BRACKET_OPEN SQ_BRACKET_CLOSE {
                        symbolType* t = $1->type;
                        symbolType* prev = NULL;
                        while(t->base == "arr") {
                            prev = t;
                            t = t->arrType;
                        }
                        if (prev == NULL) {
                            symbolType* tp = new symbolType("arr", $1->type, 0);   // Create new array type
                            $$ = $1->update(tp);    // Update
                        }
                        else {
                            prev->arrType = new symbolType("arr", t, 0);  // Create new array type
                            $$ = $1->update($1->type);  // Update
                        }
                    }
                    | direct_declarator SQ_BRACKET_OPEN STATIC type_qualifier_list assignment_expression SQ_BRACKET_CLOSE {}
                    | direct_declarator SQ_BRACKET_OPEN STATIC assignment_expression SQ_BRACKET_CLOSE {}
                    | direct_declarator SQ_BRACKET_OPEN type_qualifier_list STATIC assignment_expression SQ_BRACKET_CLOSE {}
                    | direct_declarator SQ_BRACKET_OPEN type_qualifier_list ASTERISK SQ_BRACKET_CLOSE {}
                    | direct_declarator SQ_BRACKET_OPEN ASTERISK SQ_BRACKET_CLOSE {}
                    | direct_declarator PARANTHESIS_OPEN change_table parameter_type_list PARANTHESIS_CLOSE {   // change_table non terminal is used to change the symbol table
                        currentSymbolTable->name = $1->name; // Update name
                        if ($1->type->base != "void") {
                            symbol* s = currentSymbolTable->lookup("return");   // Find return symbol
                            s->update($1->type);    // Update return type
                        }
                        $1->nestedTable = currentSymbolTable;    // Update nested table
                        currentSymbolTable->parent = globalSymbolTable;   // Update parent
                        switchTable(globalSymbolTable);  // Switch to global symbol table
                        currentSymbol = $$; // Update current symbol
                    }
                    | direct_declarator PARANTHESIS_OPEN identifier_list PARANTHESIS_CLOSE {}
                    | direct_declarator PARANTHESIS_OPEN change_table PARANTHESIS_CLOSE {
                        currentSymbolTable->name = $1->name; // Update name
                        if ($1->type->base != "void") {
                            symbol* s = currentSymbolTable->lookup("return");   // Find return symbol
                            s->update($1->type);    // Update return type
                        }
                        $1->nestedTable = currentSymbolTable;    // Update nested table
                        currentSymbolTable->parent = globalSymbolTable;   // Update parent
                        switchTable(globalSymbolTable);  // Switch to global symbol table
                        currentSymbol = $$; // Update current symbol
                    }
                    ;

type_qualifier_list_opt : type_qualifier_list {}
                        | %empty {}
                        ;

pointer : ASTERISK type_qualifier_list_opt {$$ =  new symbolType("ptr");} // Create new pointer type
        | ASTERISK type_qualifier_list_opt pointer {$$ = new symbolType("ptr", $3);} // Create new pointer type
        ;

type_qualifier_list : type_qualifier {}
                    | type_qualifier_list type_qualifier {}
                    ;

parameter_type_list : parameter_list {}
                    | parameter_list COMMA ELLIPSIS {}
                    ;

parameter_list  : parameter_declaration {}
                | parameter_list COMMA parameter_declaration {}
                ;

parameter_declaration   : declaration_specifiers declarator {}
                        | declaration_specifiers {}
                        ;

identifier_list : IDENTIFIER {}
                | identifier_list COMMA IDENTIFIER {}
                ;

type_name   : specifier_qualifier_list {}
            ;

initializer : assignment_expression {$$ = $1->addr;}
            | CURLY_BRACKET_OPEN initializer_list CURLY_BRACKET_CLOSE {}
            | CURLY_BRACKET_OPEN initializer_list COMMA CURLY_BRACKET_CLOSE {}
            ;

initializer_list    : designation_opt initializer {}
                    | initializer_list COMMA designation_opt initializer {}
                    ;

designation_opt : designation {}
                | %empty {}
                ;

designation : designator_list ASSIGN {}
            ;

designator_list : designator {}
                | designator_list designator {}
                ;

designator  : SQ_BRACKET_OPEN constant_expression SQ_BRACKET_CLOSE {}
            | PERIOD IDENTIFIER {}
            ;


statement   : labeled_statement {}
            | compound_statement { $$ = $1; }
            | expression_statement {
                $$ = new S();
                $$->nextList = $1->nextList;
            }
            | selection_statement { $$ = $1; }
            | iteration_statement { $$ = $1; }
            | jump_statement { $$ = $1; }
            ;

// Added new non-terminal for loops
loop_statement: labeled_statement {}
            | expression_statement {
                $$ = new S();
                $$->nextList = $1->nextList;
            }
            | selection_statement { $$ = $1; }
            | iteration_statement { $$ = $1; }
            | jump_statement { $$ = $1; }
            ;

labeled_statement   : IDENTIFIER COLON statement {}
                    | CASE constant_expression COLON statement {}
                    | DEFAULT COLON statement {}
                    ;

compound_statement  : CURLY_BRACKET_OPEN X change_table block_item_list_opt CURLY_BRACKET_CLOSE {   // X and change_table are augmented non-terminals
                        $$ = $4;
                        switchTable(currentSymbolTable->parent);
                    }
                    ;

block_item_list_opt : block_item_list { $$ = $1; }
                    | %empty { $$ = new S();}
                    ;

block_item_list : block_item {$$ = $1;}
                | block_item_list M block_item {    // M is augmented non-terminal
                    $$ = $3;
                    backpatch($1->nextList, $2);    // Backpatch to jump to 2
                }
                ;

block_item  : declaration { $$ = new S(); }
            | statement { $$ = $1; }
            ;

expression_statement    : expression SEMICOLON { $$ = $1; }
                        | SEMICOLON { $$ = new E(); }
                        ;

selection_statement : IF PARANTHESIS_OPEN expression N PARANTHESIS_CLOSE M statement N %prec THEN { // M, N and THEN augmented to help with control flow
                        backpatch($4->nextList, nextinstr());   // Backpatch to next instruction
                        convIntToBool($3);
                        $$ = new S();
                        backpatch($3->trueList, $6);    // Backpatch to M
                        list<int> temp = merge($3->falseList, $7->nextList); // Merge false lists
                        $$->nextList = merge($8->nextList, temp); // Merge false lists
                    }
                    | IF PARANTHESIS_OPEN expression N PARANTHESIS_CLOSE M statement N ELSE M statement {
                        backpatch($4->nextList, nextinstr());   // Backpatch to next instruction
                        convIntToBool($3);
                        $$ = new S();
                        backpatch($3->trueList, $6);    // Backpatch to M1
                        backpatch($3->falseList, $10);   // Backpatch to M2
                        list<int> temp = merge($7->nextList, $8->nextList); // Merge false lists
                        $$->nextList = merge($11->nextList, temp); // Merge false lists
                    }
                    | SWITCH PARANTHESIS_OPEN expression PARANTHESIS_CLOSE statement {}
                    ;

iteration_statement : WHILE W PARANTHESIS_OPEN X change_table M expression PARANTHESIS_CLOSE M loop_statement { // W, X, M and change_table are augmented non-terminals
                        $$ = new S(); // new statement
                        convIntToBool($7);
                        backpatch($10->nextList, $6);   // Backpatch to M1
                        backpatch($7->trueList, $9);    // Backpatch to M2
                        $$->nextList = $7->falseList;  // Copy false list
                        emit("goto", convIntToStr($6)); // goto
                        blockName = "";
                        switchTable(currentSymbolTable->parent);
                    }
                    | WHILE W PARANTHESIS_OPEN X change_table M expression PARANTHESIS_CLOSE CURLY_BRACKET_OPEN M block_item_list_opt CURLY_BRACKET_CLOSE { // W, X, M and change_table are augmented non-terminals
                        $$ = new S(); // new statement
                        convIntToBool($7);
                        backpatch($11->nextList, $6);   // Backpatch to M1
                        backpatch($7->trueList, $10);    // Backpatch to M2
                        $$->nextList = $7->falseList;  // Copy false list
                        emit("goto", convIntToStr($6)); // goto
                        blockName = "";
                        switchTable(currentSymbolTable->parent);
                    }
                    | DO D M loop_statement M WHILE PARANTHESIS_OPEN expression PARANTHESIS_CLOSE SEMICOLON {   // D and M are augmented non-terminals
                        $$ = new S();
                        convIntToBool($8);
                        backpatch($8->trueList, $3);    // Backpatch to D
                        backpatch($4->nextList, $5);    // Backpatch to M
                        $$->nextList = $8->falseList;  // Copy false list
                        blockName = "";
                    }
                    | DO D CURLY_BRACKET_OPEN M block_item_list_opt CURLY_BRACKET_CLOSE M WHILE PARANTHESIS_OPEN expression PARANTHESIS_CLOSE SEMICOLON {  // D and M are augmented non-terminals
                        $$ = new S();
                        convIntToBool($10);
                        backpatch($10->trueList, $4);    // Backpatch to M1
                        backpatch($5->nextList, $7);    // Backpatch to M2
                        $$->nextList = $10->falseList;  // Copy false list
                        blockName = "";
                    }
                    | FOR F PARANTHESIS_OPEN X change_table declaration M expression_statement M expression N PARANTHESIS_CLOSE M loop_statement {  // F, X, M, N and change_table are augmented non-terminals
                        $$ = new S();
                        convIntToBool($8);
                        backpatch($8->trueList, $13); // Backpatch to M3
                        backpatch($11->nextList, $7); // Backpatch to M1
                        backpatch($14->nextList, $9); // Backpatch to N
                        emit("goto", convIntToStr($9)); // goto
                        $$->nextList = $8->falseList;  // Copy false list
                        blockName = "";
                        switchTable(currentSymbolTable->parent);
                    }
                    | FOR F PARANTHESIS_OPEN X change_table expression_statement M expression_statement M expression N PARANTHESIS_CLOSE M loop_statement {  // F, X, M, N and change_table are augmented non-terminals
                        $$ = new S();
                        convIntToBool($8);
                        backpatch($8->trueList, $13); // Backpatch to M3
                        backpatch($11->nextList, $7); // Backpatch to M1
                        backpatch($14->nextList, $9); // Backpatch to N
                        emit("goto", convIntToStr($9)); // goto
                        $$->nextList = $8->falseList;  // Copy false list
                        blockName = "";
                        switchTable(currentSymbolTable->parent);
                    }
                    | FOR F PARANTHESIS_OPEN X change_table declaration M expression_statement M expression N PARANTHESIS_CLOSE M CURLY_BRACKET_OPEN block_item_list_opt CURLY_BRACKET_CLOSE {  // F, X, M, N and change_table are augmented non-terminals
                        $$ = new S();
                        convIntToBool($8);
                        backpatch($8->trueList, $13); // Backpatch to M3
                        backpatch($11->nextList, $7); // Backpatch to M1
                        backpatch($15->nextList, $9); // Backpatch to N
                        emit("goto", convIntToStr($9)); // goto
                        $$->nextList = $8->falseList;  // Copy false list
                        blockName = "";
                        switchTable(currentSymbolTable->parent);
                    }
                    | FOR F PARANTHESIS_OPEN X change_table expression_statement M expression_statement M expression N PARANTHESIS_CLOSE M CURLY_BRACKET_OPEN block_item_list_opt CURLY_BRACKET_CLOSE { // F, X, M, N and change_table are augmented non-terminals
                        $$ = new S();
                        convIntToBool($8);
                        backpatch($8->trueList, $13); // Backpatch to M3
                        backpatch($11->nextList, $7); // Backpatch to M1
                        backpatch($15->nextList, $9); // Backpatch to N
                        emit("goto", convIntToStr($9)); // goto
                        $$->nextList = $8->falseList;  // Copy false list
                        blockName = "";
                        switchTable(currentSymbolTable->parent);
                    }
                    ;

// Augmented empty non-terminals
F   : %empty { blockName = "FOR"; }
    ;
W   : %empty { blockName = "WHILE"; }
    ;
D   : %empty { blockName = "DO"; }
    ;
X   : %empty { 
        string newSymbolTableName = currentSymbolTable->name + "." + blockName + "$" + to_string(SymbolTableCount++); // Name the new table
        symbol* symbolFound = currentSymbolTable->lookup(newSymbolTableName); // Find the symbol
        symbolFound->nestedTable = new symbolTable(newSymbolTableName); // Create new symbol table
        symbolFound->name = newSymbolTableName; // Update name
        symbolFound->nestedTable->parent = currentSymbolTable; // Update parent
        symbolFound->type = new symbolType("block"); // Update type
        currentSymbol = symbolFound; // Update current symbol
    }
    ;
change_table    : %empty {
                    // Switch to new symbol table, if it does not exist, create it
                    if (currentSymbol->nestedTable != NULL) {
                        switchTable(currentSymbol->nestedTable); // Switch to nested table
                        emit("label", currentSymbolTable->name);
                    }
                    else {
                        switchTable(new symbolTable(""));
                    }
                }
                ;

jump_statement  : GOTO IDENTIFIER SEMICOLON {}
                | CONTINUE SEMICOLON { $$ = new S(); }
                | BREAK SEMICOLON { $$ = new S(); }
                | RETURN expression SEMICOLON {
                    $$ = new S();
                    emit("return", $2->addr->name); // return \$ 2->Array->name
                }
                | RETURN SEMICOLON {
                    $$ = new S();
                    emit("return", ""); // return
                }
                ;



translation_unit    : external_declaration {}
                    | translation_unit external_declaration {}
                    ;

external_declaration    : function_definition {}
                        | declaration {}
                        ;

function_definition : declaration_specifiers declarator declaration_list_opt change_table CURLY_BRACKET_OPEN block_item_list_opt CURLY_BRACKET_CLOSE {
                        currentSymbolTable->parent = globalSymbolTable;
                        SymbolTableCount = 0;
                        switchTable(globalSymbolTable);  // End of function, switch to global symbol table
                    }
                    ;

declaration_list_opt    : declaration_list {}
                        | %empty {}
                        ;

declaration_list    : declaration {}
                    | declaration_list declaration {}
                    ;
%%

void yyerror(const string &s) {
    int line = yylineno;
    string loc = yytext;
    cerr << "!!! ERROR: " << s << " at line " << line << ", near '" << loc << "'" << endl;
    return;
}
