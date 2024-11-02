%{
    #include<iostream>
    #include "translator.h"
    using namespace std;
    extern int yylex();
    void yyerror(const string& s);
    extern int yylineno;
    extern char* yytext;
    extern string datatype;
%}

%union{
    int ival;
    char* sval;
    symbol* symb;
    symbolType* symbType;
    E* expr;
    A* arr;
    S* stmt;
    char unary_op;
    int count_params;
    int instr_num;

}

%token AUTO BOOL COMPLEX IMAGINARY RESTRICT UNSIGNED BREAK EXTERN RETURN VOID CASE FLOAT SHORT VOLATILE CHAR FOR SIGNED WHILE CONST GOTO SIZEOF  CONTINUE IF STATIC  DEFAULT INLINE STRUCT  DO INT SWITCH DOUBLE LONG TYPEDEF ELSE REGISTER UNION
%token SQRBROPEN SQRBRCLOSE RORBROPEN RORBRCLOSE CURBROPEN CURBRCLOSE DOT ARWCOM INCRM DECRM AMPSND PIPE MUL ADD SUB NEG EXCLAIM DIV MODULO SHL SHR LST GRT LTE GTE EQL NEQ AND OR XOR QUESTION COLON SEMICOLON DOTS ASSIGN
%token STAREQ DIVEQ MODEQ PLUSEQ MINUSEQ SHLEQ SHREQ BINANDEQ BINXOREQ BINOREQ COMMA HASH


%token<symb> IDENTIFIER
%token<ival> INTEGER_CONSTANT
%token<sval> FLOATING_CONSTANT
%token<sval> CHARACTER_CONSTANT
%token<sval> STRING_LITERAL

%start translation_unit
%right THEN ELSE  

%type<expr> expression assignment_expression primary_expression multiplicative_expression additive_expression shift_expression relational_expression equality_expression AND_expression exclusive_OR_expression inclusive_OR_expression logical_AND_expression logical_OR_expression conditional_expression expression_statement 
%type<arr> postfix_expression unary_expression cast_expression
%type<count_params> argument_expression_list_opt argument_expression_list
%type<unary_op> unary_operator
%type<instr_num> M 
%type<stmt> N
%type<symb> declarator init_declarator initializer direct_declarator
%type<symbType> pointer
%type<stmt> statement labeled_statement compound_statement selection_statement iteration_statement loop_statement jump_statement block_item_list_optional block_item_list block_item

%%
primary_expression: IDENTIFIER {
                       $$=new E();
                       $$->addr=$1;
                       $$->exprType="not_bool";
                    }
                  | INTEGER_CONSTANT {
                        $$=new E();
                        $$->addr=symbolTable::gentemp(new symbolType("int"),convIntToStr($1));
                        emit("=",$$->addr->getName(),$1);
                    }
                  | FLOATING_CONSTANT {
                        $$=new E();
                        $$->addr=symbolTable::gentemp(new symbolType("float"),string($1));
                        emit("=",$$->addr->getName(),string($1));
                    }   
                  | CHARACTER_CONSTANT {
                        $$=new E();
                        $$->addr=symbolTable::gentemp(new symbolType("char"),string($1));
                        emit("=",$$->addr->getName(),string($1));
                    }
                  | STRING_LITERAL{
                        $$=new E();
                        $$->addr=symbolTable::gentemp(new symbolType("ptr"),$1);
                        $$->addr->getType()->setArrType(new symbolType("char"));
                    }
                  | RORBROPEN expression RORBRCLOSE{
                        $$=$2;
                    }
                  ;
postfix_expression : primary_expression
                {
                    $$=new A();
                    $$->location=$1->addr;
                    $$->type=$1->addr->getType();
                    $$->addr=$$->location;
                }
                | postfix_expression SQRBROPEN expression SQRBRCLOSE
                {
                    $$=new A();
                    $$->location=$1->location;
                    $$->type=$1->type->getArrType();
                    $$->addr=symbolTable::gentemp(new symbolType("int"));
                    $$->arrType="arr";
                    if($1->arrType=="arr"){
                        symbol* temp=symbolTable::gentemp(new symbolType("int"));
                        emit("*",temp->getName(),$3->addr->getName(),convIntToStr(sizeOfType($$->type)));
                        emit("+",$$->addr->getName(),$1->addr->getName(),temp->getName());
                    }else{
                        emit("*",$$->addr->getName(),$3->addr->getName(),convIntToStr(sizeOfType($$->type)));
                    }
                }
                | postfix_expression RORBROPEN argument_expression_list_opt RORBRCLOSE
                {
                    $$=new A();
                    $$->location=symbolTable::gentemp($1->type);
                    emit("call",$$->location->getName(),$1->location->getName(),convIntToStr($3));
                }
                | postfix_expression DOT IDENTIFIER
                {
                    
                }
                | postfix_expression ARWCOM IDENTIFIER
                {
                
                }
                | postfix_expression INCRM
                {
                   $$=new A();
                   $$->location=symbolTable::gentemp($1->location->getType());
                   emit("=",$$->location->getName(),$1->location->getName());
                   emit("+",$1->location->getName(),$1->location->getName(),"1");
                }
                | postfix_expression DECRM
                {
                    $$=new A();
                    $$->location=symbolTable::gentemp($1->location->getType());
                    emit("=",$$->location->getName(),$1->location->getName());
                    emit("-",$1->location->getName(),$1->location->getName(),"1");
                }
                | RORBROPEN type_name RORBRCLOSE CURBROPEN initializer_list CURBRCLOSE
                {
                    
                }
                | RORBROPEN type_name RORBRCLOSE CURBROPEN initializer_list COMMA CURBRCLOSE
                {
                    
                }
                ;
argument_expression_list_opt: argument_expression_list {
                                    $$=$1;
                                }
                            | %empty {
                                $$=0;
                            }
                            ;
argument_expression_list: assignment_expression {
                                $$=1;
                                emit("param",$1->addr->getName());
                            }
                            |argument_expression_list COMMA assignment_expression {
                                $$=$1+1;
                                emit("param",$3->addr->getName());
                            }
                            ;

unary_expression : postfix_expression
                {
                    $$=$1;  
                }
                | INCRM unary_expression
                {
                    emit("+",$2->location->getName(),$2->location->getName(),"1");
                    $$=$2;
                }
                | DECRM unary_expression
                {
                   emit("-",$2->location->getName(),$2->location->getName(),"1");
                   $$=$2;
                }
                | unary_operator cast_expression
                {
                    $$=new A();
                    if($1=='&'){
                        $$->location=symbolTable::gentemp(new symbolType("ptr"));
                        $$->location->getType()->setArrType($2->location->getType());
                        emit("= &",$$->location->getName(),$2->location->getName());
                    }
                    else if($1=='+'){
                        $$=$2;
                    }
                    else if($1=='-'){
                        $$->location=symbolTable::gentemp(new symbolType($2->location->getType()->getBase()));
                        emit("= -",$$->location->getName(),$2->location->getName());
                    }
                    else if($1=='*'){
                        $$->arrType="ptr";
                        $$->addr=symbolTable::gentemp($2->location->getType()->getArrType());
                        $$->location=$2->location;
                        emit("= *",$$->addr->getName(),$2->location->getName());
                    }
                    else if($1=='~'){
                        $$->location=symbolTable::gentemp(new symbolType($2->location->getType()->getBase()));
                        emit("= ~",$$->location->getName(),$2->location->getName());
                    }
                    else if($1=='!'){
                        $$->location=symbolTable::gentemp(new symbolType($2->location->getType()->getBase()));
                        emit("= !",$$->location->getName(),$2->location->getName());
                    }
                }
                | SIZEOF unary_expression
                {
                    
                }
                | SIZEOF RORBROPEN type_name RORBRCLOSE
                {
                    
                };

unary_operator : AMPSND
                {
                    $$ = '&';
                }
                | MUL
                {
                    $$ = '*';
                }
                | ADD
                {
                    $$ = '+';
                }
                | SUB
                {
                    $$ = '-';
                }
                | NEG
                {
                    $$ = '~';
                }
                | EXCLAIM
                {
                    $$ = '!';
                }
                ;
cast_expression: unary_expression
                {
                    $$=$1;
                }
                | RORBROPEN type_name RORBRCLOSE cast_expression
                {
                    
                    $$=new A();
                    $$->location=convType($4->location,datatype);
                }
                ;

multiplicative_expression : cast_expression
                {
                    $$=new E();
                    if($1->arrType=="arr"){
                        $$->addr=symbolTable::gentemp($1->addr->getType());
                        emit("=[]",$$->addr->getName(),$1->location->getName(),$1->addr->getName());
                    }
                    else if($1->arrType=="ptr"){
                        $$->addr=$1->addr;
                    }
                    else{
                        $$->addr=$1->location;
                    }
                    
                }
                | multiplicative_expression MUL cast_expression
                {
                    if(typecheck($1->addr,$3->location)){
                        $$=new E();
                        $$->addr=symbolTable::gentemp(new symbolType($1->addr->getType()->getBase()));
                        emit("*",$$->addr->getName(),$1->addr->getName(),$3->location->getName());
                    }
                    else{
                        yyerror("Type mismatch");
                    }
                
                }
                | multiplicative_expression DIV cast_expression
                {
                    if(typecheck($1->addr,$3->location)){
                        $$=new E();
                        $$->addr=symbolTable::gentemp(new symbolType($1->addr->getType()->getBase()));
                        emit("/",$$->addr->getName(),$1->addr->getName(),$3->location->getName());
                    }
                    else{
                        yyerror("Type mismatch");
                    }
                }
                | multiplicative_expression MODULO cast_expression
                {
                    if(typecheck($1->addr,$3->location)){
                        $$=new E();
                        $$->addr=symbolTable::gentemp(new symbolType($1->addr->getType()->getBase()));
                        emit("%",$$->addr->getName(),$1->addr->getName(),$3->location->getName());
                    }
                    else{
                        yyerror("Type mismatch");
                    }
               
                }
                ;
additive_expression : multiplicative_expression{
                    $$=$1;
                }
                | additive_expression ADD multiplicative_expression
                {
                    if(typecheck($1->addr,$3->addr)){
                        $$=new E();
                        $$->addr=symbolTable::gentemp(new symbolType($1->addr->getType()->getBase()));
                        emit("+",$$->addr->getName(),$1->addr->getName(),$3->addr->getName());
                    }
                    else{
                        yyerror("Type mismatch");
                    }
                }
                | additive_expression SUB multiplicative_expression
                {
                    if(typecheck($1->addr,$3->addr)){
                        $$=new E();
                        $$->addr=symbolTable::gentemp(new symbolType($1->addr->getType()->getBase()));
                        emit("-",$$->addr->getName(),$1->addr->getName(),$3->addr->getName());
                    }
                    else{
                        yyerror("Type mismatch");
                    }
                }
                ;
shift_expression: additive_expression
                {
                    $$=$1;
                }
                | shift_expression SHL additive_expression
                {
                    if($3->addr->getType()->getBase()=="int"){
                        $$=new E();
                        $$->addr=symbolTable::gentemp(new symbolType("int"));
                        emit("<<",$$->addr->getName(),$1->addr->getName(),$3->addr->getName());
                    }
                    else{
                        yyerror("Type mismatch");
                    }
                    
                }
                | shift_expression SHR additive_expression
                {
                    if($3->addr->getType()->getBase()=="int"){
                        $$=new E();
                        $$->addr=symbolTable::gentemp(new symbolType("int"));
                        emit(">>",$$->addr->getName(),$1->addr->getName(),$3->addr->getName());
                    }
                    else{
                        yyerror("Type mismatch");
                    }
                }
                ;

relational_expression: shift_expression
                {
                    $$=$1;
                }
                | relational_expression LST shift_expression
                {
                    if(typecheck($1->addr,$3->addr)){
                        $$=new E();
                        $$->exprType="bool";
                        $$->trueList=makelist(nextinstr());
                        $$->falseList=makelist(nextinstr()+1);
                        emit("<","",$1->addr->getName(),$3->addr->getName());
                        emit("goto","");
                    }
                    else{
                        yyerror("Type mismatch");
                    }
                    
                }
                | relational_expression GRT shift_expression
                {
                    if(typecheck($1->addr,$3->addr)){
                        $$=new E();
                        $$->exprType="bool";
                        $$->trueList=makelist(nextinstr());
                        $$->falseList=makelist(nextinstr()+1);
                        emit(">","",$1->addr->getName(),$3->addr->getName());
                        emit("goto","");
                    }
                    else{
                        yyerror("Type mismatch");
                    }
                }
                | relational_expression LTE shift_expression
                {
                    if(typecheck($1->addr,$3->addr)){
                        $$=new E();
                        $$->exprType="bool";
                        $$->trueList=makelist(nextinstr());
                        $$->falseList=makelist(nextinstr()+1);
                        emit("<=","",$1->addr->getName(),$3->addr->getName());
                        emit("goto","");
                    }
                    else{
                        yyerror("Type mismatch");
                    }
                }
                | relational_expression GTE shift_expression
                {
                    if(typecheck($1->addr,$3->addr)){
                        $$=new E();
                        $$->exprType="bool";
                        $$->trueList=makelist(nextinstr());
                        $$->falseList=makelist(nextinstr()+1);
                        emit(">=","",$1->addr->getName(),$3->addr->getName());
                        emit("goto","");
                    }
                    else{
                        yyerror("Type mismatch");
                    }
                }
                ;
equality_expression: relational_expression
                {
                    $$=$1;
                    
                }
                | equality_expression EQL relational_expression
                {
                    if(typecheck($1->addr,$3->addr)){
                        convBool2Int($1);
                        convBool2Int($3);
                        $$=new E();
                        $$->exprType="bool";
                        $$->trueList=makelist(nextinstr());
                        $$->falseList=makelist(nextinstr()+1);
                        
                        emit("==","",$1->addr->getName(),$3->addr->getName());
                        emit("goto","");
                    }
                    else{
                        yyerror("Type mismatch");
                    }
                }
                | equality_expression NEQ relational_expression
                {
                    if(typecheck($1->addr,$3->addr)){
                        convBool2Int($1);
                        convBool2Int($3);
                        $$=new E();
                        $$->exprType="bool";
                        $$->trueList=makelist(nextinstr());
                        $$->falseList=makelist(nextinstr()+1);
                        emit("!=","",$1->addr->getName(),$3->addr->getName());
                        emit("goto","");
                    }
                    else{
                        yyerror("Type mismatch");
                    }

                    
                }
                ;
AND_expression: equality_expression
                {
                    $$=$1;
                }
                | AND_expression AMPSND equality_expression
                {
                    if(typecheck($1->addr,$3->addr)){
                        convBool2Int($1);
                        convBool2Int($3);
                        $$=new E();
                        $$->exprType="not_bool";
                        $$->addr=symbolTable::gentemp(new symbolType("int"));
                        
                        emit("&",$$->addr->getName(),$1->addr->getName(),$3->addr->getName());

                    }
                    else{
                        yyerror("Type mismatch");
                    }
                }
                ;
exclusive_OR_expression: AND_expression
                {
                    $$=$1;
                }
                | exclusive_OR_expression XOR AND_expression
                {
                    if(typecheck($1->addr,$3->addr)){
                        convBool2Int($1);
                        convBool2Int($3);
                        $$=new E();
                        $$->exprType="not_bool";
                        $$->addr=symbolTable::gentemp(new symbolType("int"));
                        emit("^",$$->addr->getName(),$1->addr->getName(),$3->addr->getName());
                    }
                    else{
                        yyerror("Type mismatch");
                    }
                    
                }
                ;
inclusive_OR_expression: exclusive_OR_expression
                {
                    $$=$1;
                }
                | inclusive_OR_expression PIPE exclusive_OR_expression
                {
                    if(typecheck($1->addr,$3->addr)){
                        convBool2Int($1);
                        convBool2Int($3);
                        $$=new E();
                        $$->exprType="not_bool";
                        $$->addr=symbolTable::gentemp(new symbolType("int"));
                        
                        emit("|",$$->addr->getName(),$1->addr->getName(),$3->addr->getName());
                    }
                    else{
                        yyerror("Type mismatch");
                    }
                    
                }
                ;
logical_AND_expression: inclusive_OR_expression
                {
                    $$=$1;
                }
                | logical_AND_expression AND M inclusive_OR_expression
                {
                    convInt2Bool($1);
                    convInt2Bool($4);
                    $$=new E();
                    $$->exprType="bool";
                    backpatch($1->trueList,$3);
                    $$->trueList=$4->trueList;
                    $$->falseList=merge($1->falseList,$4->falseList);

                }
                ;
logical_OR_expression: logical_AND_expression
                {
                    $$=$1;
                    
                }
                | logical_OR_expression OR M logical_AND_expression
                {
                    convInt2Bool($1);
                    convInt2Bool($4);
                    $$=new E();
                    $$->exprType="bool";
                    backpatch($1->falseList,$3);
                    $$->trueList=merge($1->trueList,$4->trueList);
                    $$->falseList=$4->falseList;
                }
                ;
conditional_expression: logical_OR_expression
                {
                    $$=$1;
                }
                | logical_OR_expression N QUESTION M expression N COLON M conditional_expression
                {
                    $$->addr=symbolTable::gentemp($5->addr->getType());
                    $$->addr->update($5->addr->getType());
                    emit("=",$$->addr->getName(),$9->addr->getName());
                    list<int>tmp1=makelist(nextinstr());
                    emit("goto","");
                    backpatch($6->nextList,nextinstr());
                    emit("=",$$->addr->getName(),$5->addr->getName());
                    list<int>tmp2=makelist(nextinstr());
                    tmp1=merge(tmp1,tmp2);
                    emit("goto","");
                    backpatch($2->nextList,nextinstr());
                    convInt2Bool($1);
                    backpatch($1->trueList,$4);
                    backpatch($1->falseList,$8);
                    backpatch(tmp1,nextinstr());
                }
                ;

M: %empty{
    $$=nextinstr();
}
N: %empty{
    $$=new S();
    $$->nextList=makelist(nextinstr());
    emit("goto","");
}                        

assignment_expression: conditional_expression{
                    $$=$1;
                }
                |unary_expression assignment_operator assignment_expression
                {
                    if($1->arrType=="arr"){
                        $3->addr=convType($3->addr,$1->type->getBase());
                        emit("[]=",$1->location->getName(),$1->addr->getName(),$3->addr->getName());
                    }
                    else if($1->arrType=="ptr"){
                        emit("*=",$1->location->getName(),$3->addr->getName());
                    }
                    else{
                        $3->addr=convType($3->addr,$1->location->getType()->getBase());
                        emit("=",$1->location->getName(),$3->addr->getName());
                    }
                    $$=$3;
                }
                ;

assignment_operator : ASSIGN
                { 
                }
                | STAREQ
                {  
                }
                | DIVEQ
                {
                }
                | MODEQ
                {
                }
                | PLUSEQ
                {
                }
                | MINUSEQ
                {
                }
                | SHLEQ
                {
                }
                | SHREQ
                {
                }
                | BINANDEQ
                {
                }
                | BINXOREQ
                {
                }
                | BINOREQ
                {
                }
                ;
expression : assignment_expression
            {
                $$=$1;
            }
            | expression COMMA assignment_expression
            {
                
            };

constant_expression : conditional_expression
            {
                
            };

declaration : declaration_specifiers SEMICOLON
            {
                
            }
            | declaration_specifiers init_declarator_list SEMICOLON
            {
                
            };
declaration_specifiers : storage_class_specifier
            {
            }
            | storage_class_specifier declaration_specifiers
            {
            }
            | type_specifier
            {
            }
            | type_specifier declaration_specifiers
            {
                
            }
            | type_qualifier
            {
            
            }
            | type_qualifier declaration_specifiers
            {
            
            }
            | function_specifier
            {
            }
            | function_specifier declaration_specifiers
            {
            
            };
init_declarator_list : init_declarator
            {
            }
            | init_declarator_list COMMA init_declarator
            {
            };
init_declarator : declarator
            {
                $$=$1;
            }
            | declarator ASSIGN initializer
            {
                if($3->getInitValue()!=""){
                    $1->setInitValue($3->getInitValue());
                }
                emit("=",$1->getName(),$3->getName());
            };
storage_class_specifier : AUTO
            {
            }
            | REGISTER
            {
            }
            | STATIC
            {
            }
            | EXTERN
            {
            }
            ;
type_specifier : VOID
            {
                datatype="void";
            }
            | CHAR
            {
                datatype="char";
            }
            | SHORT
            {
            }
            | INT
            {
                datatype="int";
            }
            | LONG
            {
            }
            | FLOAT
            {
                datatype="float";
            }
            | DOUBLE
            {
            }
            | SIGNED
            {
            }
            | UNSIGNED
            {
            }
            | BOOL
            {
            }
            | COMPLEX
            {
            }
            | IMAGINARY
            {
            }
            ;
specifier_qualifier_list : type_specifier
            {
            }
            | type_specifier specifier_qualifier_list
            {
            
            }
            | type_qualifier
            {
                
            }
            | type_qualifier specifier_qualifier_list
            {
            
            };
type_qualifier : CONST
            {
            }
            | RESTRICT
            {
            }
            | VOLATILE
            {
            }
            ;
function_specifier : INLINE
            {
            };
declarator: pointer direct_declarator
            {
                symbolType* t=$1;
                while(t->getArrType()!=NULL){
                    t=t->getArrType();
                }
                t->setArrType($2->getType());
                $$=$2->update($1);
            }
            | direct_declarator
            {
            };
direct_declarator : IDENTIFIER
            {
                $$=$1->update(new symbolType(datatype));
                __CURR_SYMBOL__=$1;
            
            }
            | RORBROPEN declarator RORBRCLOSE
            {
                $$=$2;
            }
            | direct_declarator SQRBROPEN type_qualifier_list assignment_expression SQRBRCLOSE
            {
            }
            | direct_declarator SQRBROPEN  type_qualifier_list  SQRBRCLOSE
            {   
            }
            | direct_declarator SQRBROPEN  assignment_expression SQRBRCLOSE
            {   
                symbolType* s=$1->getType();
                symbolType* prev=NULL;
                while(s->getBase()=="arr"){
                    prev=s;
                    s=s->getArrType();
                }
                if(prev==NULL){
                    int x=atoi($3->addr->getInitValue().c_str());
                    symbolType* tmp=new symbolType("arr",$1->getType(),x);
                    $$=$1->update(tmp);
                }else{
                    int x=atoi($3->addr->getInitValue().c_str());
                    prev->setArrType(new symbolType("arr", s,x));
                    $$=$1->update($1->getType());
                }
            }
            | direct_declarator SQRBROPEN  SQRBRCLOSE
            {   
                symbolType* s=$1->getType();
                symbolType* prev=NULL;
                while(s->getBase()=="arr"){
                    prev=s;
                    s=s->getArrType();
                }
                if (prev == NULL) {
                    symbolType* tmp = new symbolType("arr", $1->getType(), 0);   
                    $$ = $1->update(tmp);    
                }
                else {
                    prev->setArrType(new symbolType("arr", s, 0));  
                    $$ = $1->update($1->getType()); 
                }
            }
            | direct_declarator SQRBROPEN STATIC type_qualifier_list assignment_expression  SQRBRCLOSE
            {
            }
            | direct_declarator SQRBROPEN STATIC  assignment_expression  SQRBRCLOSE
            {

            }
            | direct_declarator SQRBROPEN type_qualifier_list STATIC assignment_expression SQRBRCLOSE{

            }
            | direct_declarator SQRBROPEN type_qualifier_list MUL SQRBRCLOSE{

            }
            | direct_declarator SQRBROPEN MUL  SQRBRCLOSE
            {   
            
            }
            | direct_declarator RORBROPEN change_table parameter_type_list RORBRCLOSE
            {
                __CURRENT_SYMBOL_TABLE__->setName($1->getName());
                if($1->getType()->getBase()!="void"){
                    symbol* s=__CURRENT_SYMBOL_TABLE__->lookup("return");
                    s->update($1->getType());
                }
                $1->setNestedTable(__CURRENT_SYMBOL_TABLE__);
                __CURRENT_SYMBOL_TABLE__->setParent(__GLOBAL_SYMBOL_TABLE__);
                switchTable(__GLOBAL_SYMBOL_TABLE__);
                __CURR_SYMBOL__=$$;
            }
            | direct_declarator RORBROPEN identifier_list RORBRCLOSE
            {
            }
            | direct_declarator RORBROPEN change_table RORBRCLOSE
            {
                __CURRENT_SYMBOL_TABLE__->setName($1->getName());
                if($1->getType()->getBase()!="void"){
                    symbol* s=__CURRENT_SYMBOL_TABLE__->lookup("return");
                    s->update($1->getType());
                }
                $1->setNestedTable(__CURRENT_SYMBOL_TABLE__);
                __CURRENT_SYMBOL_TABLE__->setParent(__GLOBAL_SYMBOL_TABLE__);
                switchTable(__GLOBAL_SYMBOL_TABLE__);
                __CURR_SYMBOL__=$$;
            }
            ;

pointer : MUL type_qualifier_list_optional
{
   $$=new symbolType("ptr");
}
| MUL type_qualifier_list_optional pointer
{
    $$=new symbolType("ptr",$3);
    
}
;

type_qualifier_list : type_qualifier
{   
}
| type_qualifier_list type_qualifier
{ 
}
;

type_qualifier_list_optional : type_qualifier_list
{
}
| %empty
{  
}
;

parameter_type_list : parameter_list 
{   
}
| parameter_list COMMA DOTS
{   
};

parameter_list : parameter_declaration
{
}
| parameter_list COMMA parameter_declaration
{
};

parameter_declaration : declaration_specifiers declarator
{
}
| declaration_specifiers
{  
};

identifier_list : IDENTIFIER
{
}
| identifier_list COMMA IDENTIFIER
{  
};

type_name:specifier_qualifier_list{
}
;

initializer : assignment_expression
{
    $$=$1->addr;
}
| CURBROPEN initializer_list CURBRCLOSE
{   
}
| CURBROPEN initializer_list COMMA CURBRCLOSE
{   
};

initializer_list : designation_optional initializer
{   
}
| initializer_list COMMA designation_optional initializer
{
};

designation : designator_list ASSIGN
{  
};

designation_optional : designation
{  
}
| %empty
{   
};

designator_list : designator
{  
}
| designator_list designator
{
};

designator : SQRBROPEN constant_expression SQRBRCLOSE
{ 
}
| DOT IDENTIFIER
{
};

statement: labeled_statement
        {
        }
        | compound_statement
        {
            $$=$1;
        }
        | expression_statement
        {
            $$=new S();
            $$->nextList=$1->nextList;
        }
        | selection_statement
        {
            $$=$1;
        }
        | iteration_statement
        {
            $$=$1;
        }
        | jump_statement
        {
            $$=$1;
        }
        ;
loop_statement: labeled_statement{

        }
        | expression_statement{
            $$=new S();
            $$->nextList=$1->nextList;
        }
        | selection_statement{
            $$=$1;
        }
        | iteration_statement {
            $$=$1;
        }
        | jump_statement{
            $$=$1;
        }
        ;
labeled_statement: IDENTIFIER COLON statement
        {
        }
        | CASE constant_expression COLON statement
        {
        }
        | DEFAULT COLON statement
        {
        }
        ;
compound_statement: CURBROPEN X change_table block_item_list_optional CURBRCLOSE
        {
            $$=$4;
            switchTable(__CURRENT_SYMBOL_TABLE__->getParent());
        }
        ;
block_item_list_optional : block_item_list
        {
            $$=$1;
        }
        | %empty
        {
            $$=new S();
        }
        ;
block_item_list: block_item
        {
            $$=$1;
        }
        | block_item_list M block_item
        {
            $$=$3;
            backpatch($1->nextList,$2);
        }
        ;
block_item: declaration
        {
            $$=new S();
        }
        | statement
        {
            $$=$1;
        }
        ;
expression_statement: SEMICOLON
        {
            $$=new E();
        }
        | expression SEMICOLON
        {
            $$=$1;
        }
        ;
selection_statement: IF RORBROPEN expression  N RORBRCLOSE M statement N %prec THEN
        {
            backpatch($4->nextList,nextinstr());
            convInt2Bool($3);
            backpatch($3->trueList,$6);
            $$=new S();
            list<int>tmp=merge($3->falseList,$7->nextList);
            $$->nextList=merge(tmp,$8->nextList);
        }
        | IF RORBROPEN expression N RORBRCLOSE M statement N ELSE M statement
        {
            backpatch($4->nextList,nextinstr());
            convInt2Bool($3);
            backpatch($3->trueList,$6);
            backpatch($3->falseList,$10);
            $$=new S();
            list<int>tmp=merge($7->nextList,$8->nextList);
            $$->nextList=merge(tmp,$11->nextList);
        }
        | SWITCH RORBROPEN expression RORBRCLOSE statement
        {
        }
        ;
iteration_statement : WHILE W RORBROPEN  X change_table M expression RORBRCLOSE M loop_statement
{
   $$=new S();
   convInt2Bool($7);
   backpatch($10->nextList,$6);
   backpatch($7->trueList,$9);
   $$->nextList=$7->falseList;
   emit("goto",convIntToStr($6));
   __CURR_BLOCK__="";
   switchTable(__CURRENT_SYMBOL_TABLE__->getParent());
}
|  WHILE W RORBROPEN  X change_table M expression RORBRCLOSE CURBROPEN M block_item_list_optional CURBRCLOSE{
    $$ = new S(); 
    convInt2Bool($7);
    backpatch($11->nextList, $6);  
    backpatch($7->trueList, $10);    
    $$->nextList = $7->falseList;  
    emit("goto", convIntToStr($6)); 
    __CURR_BLOCK__ = "";
    switchTable(__CURRENT_SYMBOL_TABLE__->getParent());
}
| DO D M loop_statement M  WHILE RORBROPEN expression RORBRCLOSE SEMICOLON
{
    $$=new S();
    convInt2Bool($8);
    backpatch($8->trueList,$3);
    backpatch($4->nextList,$5);
    __CURR_BLOCK__="";
    $$->nextList=$8->falseList;

}
| DO D CURBROPEN M block_item_list_optional CURBRCLOSE M WHILE RORBROPEN expression RORBRCLOSE SEMICOLON{
    $$ = new S();
    convInt2Bool($10);
    backpatch($10->trueList, $4);   
    backpatch($5->nextList, $7);   
    __CURR_BLOCK__="";
    $$->nextList = $10->falseList; 
   
}
| FOR F RORBROPEN X change_table declaration M expression_statement M expression N RORBRCLOSE M loop_statement
{
    $$ = new S();
    convInt2Bool($8);
    backpatch($8->trueList, $13); 
    backpatch($11->nextList, $7); 
    backpatch($14->nextList, $9); 
    emit("goto", convIntToStr($9)); 
    $$->nextList = $8->falseList;  
    __CURR_BLOCK__= "";
    switchTable(__CURRENT_SYMBOL_TABLE__->getParent());
}
| FOR F RORBROPEN X change_table expression_statement M expression_statement M expression N RORBRCLOSE M loop_statement
{
    $$ = new S();
    convInt2Bool($8);
    backpatch($8->trueList, $13); 
    backpatch($11->nextList, $7); 
    backpatch($14->nextList, $9); 
    emit("goto", convIntToStr($9));
    $$->nextList = $8->falseList; 
    __CURR_BLOCK__= "";
    switchTable(__CURRENT_SYMBOL_TABLE__->getParent());
}
| FOR F RORBROPEN X change_table declaration M expression_statement M expression N RORBRCLOSE M CURBROPEN block_item_list_optional CURBRCLOSE
{
    $$ = new S();
    convInt2Bool($8);
    backpatch($8->trueList, $13);
    backpatch($11->nextList, $7); 
    backpatch($15->nextList, $9); 
    emit("goto", convIntToStr($9)); 
    $$->nextList = $8->falseList;  
     __CURR_BLOCK__= "";
    switchTable(__CURRENT_SYMBOL_TABLE__->getParent());
}
    
| FOR F RORBROPEN X change_table expression_statement M expression_statement M expression N RORBRCLOSE M CURBROPEN block_item_list_optional CURBRCLOSE
{
    $$ = new S();
    convInt2Bool($8);
    backpatch($8->trueList, $13); 
    backpatch($11->nextList, $7); 
    backpatch($15->nextList, $9); 
    emit("goto", convIntToStr($9)); 
    $$->nextList = $8->falseList;  
    __CURR_BLOCK__= "";
    switchTable(__CURRENT_SYMBOL_TABLE__->getParent());
    
}
;
F   : %empty { __CURR_BLOCK__ = "_FOR_"; }
    ;
W   : %empty{ __CURR_BLOCK__ = "_WHILE_"; }
    ;
D   :  %empty{ __CURR_BLOCK__ = "_DO_"; }
    ;
X   : %empty{
        string newSTName=__CURRENT_SYMBOL_TABLE__->getName()+"."+__CURR_BLOCK__+"{"+to_string(__SYMBOL_TABLE_COUNT__++)+"}";
        symbol* symbolFound=__CURRENT_SYMBOL_TABLE__->lookup(newSTName);
        symbolFound->setNestedTable(new symbolTable(newSTName));
        symbolFound->setName(newSTName);
        symbolFound->getNestedTable()->setParent(__CURRENT_SYMBOL_TABLE__);
        symbolFound->setType(new symbolType("block"));
        __CURR_SYMBOL__=symbolFound;
    };
change_table: %empty{
        if(__CURR_SYMBOL__->getNestedTable()!=NULL){
            switchTable(__CURR_SYMBOL__->getNestedTable());
            emit("label",__CURRENT_SYMBOL_TABLE__->getName());
        }else{
            switchTable(new symbolTable(""));
        }
    }
    ;
jump_statement:GOTO IDENTIFIER SEMICOLON{

            }
            | CONTINUE SEMICOLON {
                $$=new S();
            }
            | BREAK SEMICOLON {
                $$=new S();
            }
            | RETURN expression SEMICOLON{
                $$=new S();
                emit("return",$2->addr->getName());
            }
            | RETURN SEMICOLON{
                $$=new S();
                emit("return","");
            }
            ;
translation_unit: external_declaration{

            }
            | translation_unit external_declaration{

            }
            ;
external_declaration: function_definition{

            }
            | declaration{

            }
            ;
function_definition: declaration_specifiers declarator declaration_list_optional change_table CURBROPEN block_item_list_optional CURBRCLOSE {
                __CURRENT_SYMBOL_TABLE__->setParent(__GLOBAL_SYMBOL_TABLE__);
                __SYMBOL_TABLE_COUNT__=0;
                switchTable(__GLOBAL_SYMBOL_TABLE__);
            }
            ;
declaration_list_optional: declaration_list{

            }
            | %empty{

            }
            ;
declaration_list: declaration{

            }
            | declaration_list declaration{

            }
            ;
%%