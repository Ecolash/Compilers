#ifndef __TRANSLATOR_H
#define __TRANSLATOR_H

#include <iostream>
#include <vector>
#include <list>
using namespace std;

#define sizeof_void    0
#define sizeof_char    1
#define sizeof_int     4
#define sizeof_float   8
#define sizeof_pointer 4

/*
==================================================================================================================
Forward declarations for the classes used in the translator:
==================================================================================================================
- class symbol         | Represents a symbol table record.
- class symbolType     | Represents the type of a symbol.
- class symbolTable    | Represents a symbol table.
- class quad           | Represents a quad to store three-address code (TAC).
- class quadArray      | Represents a list of quads.
==================================================================================================================
*/

class symbol;      
class symbolType; 
class symbolTable; 
class quad;      
class quadArray;  

using sPtr = symbol*;
using tPtr = symbolType*;
using STPtr = symbolTable*;

/*
==================================================================================================================
Global Variables used in the translator:
==================================================================================================================
- sPtr currentSymbol                 | Points to current symbol.
- STPtr currentSymbolTable           | Points to current symbol table.
- STPtr globalSymbolTable            | Points to global symbol table.
- quadArray quadTable                | Points to quad table.
- int SymbolTableCount               | Count of symbol tables.
- string blockName                   | Name of current block.
==================================================================================================================
*/

extern sPtr currentSymbol;           
extern STPtr currentSymbolTable; 
extern STPtr globalSymbolTable;  
extern quadArray quadTable;             
extern int SymbolTableCount;            
extern string blockName;                

/* Lex objects */
extern int yyparse();
extern char *yytext;

class symbol
{
public:
    string name;              // Name of symbol
    tPtr type;         // Type of symbol
    string initValue;         // Initial value of symbol
    int size;                 // Size of symbol
    int offset;               // Offset of symbol
    STPtr  nestedTable; // Nested symbol table if symbol is a function/record

    symbol(string name_, string type_ = "int", tPtr arrType = NULL, int width = 0); // Constructor
    sPtr update(tPtr t);                                                         // Update type of symbol to t
};

class symbolType
{
public:
    string base;         // Base type of symbol
    int width;           // Width of symbol, 1 by default. Size for arrays
    tPtr arrType; // Array type of symbol

    symbolType(string base_, tPtr arrType_ = NULL, int width_ = 1); // Constructor
};

class symbolTable
{
public:
    string name;         // Name of symbol table
    int count;           // Count of symbols in symbol table
    list<symbol> table;  // List of symbols in symbol table
    STPtr  parent; // Parent symbol table

    symbolTable(string name_ = "NULL"); // Constructor

    sPtr lookup(string name);                                       // Lookup for symbol in symbol table
    static sPtr gentemp(tPtr type_, string initValue_ = ""); // Generate temporary symbol
    void update();                                                     // Update offset of symbols in symbol table
    void print();                                                      // Print symbol table
};

class quad
{
public:
    string opcode;     // Opcode of quad
    string arguement1; // First argument of quad
    string arguement2; // Second argument of quad
    string result;     // Result of quad

    quad(string res_, string arg1_, string op_ = "=", string arg2_ = ""); // Constructor for string argument
    quad(string res_, int arg1_, string op_ = "=", string arg2_ = "");    // Constructor for int argument
    quad(string res_, float arg1_, string op_ = "=", string arg2_ = "");  // Constructor for float argument

    void print(); // Print quad
};

class quadArray
{
public:
    vector<quad> array; // Vector of quads
    void print();       // Print quad array
};

// Method to add a new quad.
void emit(string opcode, string res, string arg1 = "", string arg2 = ""); // String type arg
void emit(string opcode, string res, int arg1, string arg2 = "");         // Int type arg
void emit(string opcode, string res, float arg1, string arg2 = "");       // Float type arg

// Array class for arrays and pointers
class A
{
public:
    string arrType;   // Type of array. arr or ptr
    sPtr addr;     // Base symbol of array in Symbol Table
    sPtr location; // To get address of array
    tPtr type; // Type of array stored in symbol table
};

// Statement class for statements
class S
{
public:
    list<int> nextList; // List of nexts
};

// Expression class for expressions
class E
{
public:
    string exprType;     // Type of expression. bool or not_bool
    sPtr addr;        // Base symbol of expression in Symbol Table
    list<int> trueList;  // List of statements for true
    list<int> falseList; // List of statements for false
    list<int> nextList;  // List of nexts
};

/* GLOBAL FUNCTIONS */
list<int> makelist(int i);                      // Make a new list with i as the only element, index of current quad
list<int> merge(list<int> &p1, list<int> &p2);  // Merge two lists, return merged list
void backpatch(list<int> p, int i);             // Backpatch list p with i, update quad array
bool typecheck(tPtr t1, tPtr t2); // Check if types t1 and t2 are compatible (called by typecheck(symbol, symbol) to check types of symbols and compatible types)
sPtr convType(sPtr s, string t);          // Convert type of symbol s to t, which calls

/* HELPER FUNCTIONS */
bool typecheck(sPtr &s1, sPtr &s2); // Check if types of symbols s1 and s2 are compatible
string convIntToStr(int n);               // Convert int to string
string convFloatToStr(float f);           // Convert float to string
E *convIntToBool(E *e);                   // Convert int to bool
E *convBoolToInt(E *e);                   // Convert bool to int
void switchTable(STPtr  newTable);  // Switch to new symbol table
int nextinstr();                          // Return index of next quad
int sizeOfType(tPtr t);            // Return size of type t
string printType(tPtr t);          // Return string representation of type t

#endif