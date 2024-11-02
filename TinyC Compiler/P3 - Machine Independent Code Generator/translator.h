#ifndef __TRANSLATOR_H__
#define __TRANSLATOR_H__

#include <iostream>
#include <iomanip>
#include <vector>
#include <list>
#include <algorithm>

using namespace std;

extern int yyparse();
extern char *yytext;
extern int yylineno;
extern FILE *yyin;
extern void yyerror(const string &s);

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

struct E;
struct A;
struct S;

using sPtr = symbol *;
using tPtr = symbolType *;
using STPtr = symbolTable *;
using QTPtr = quadArray *;

#define __SIZE_OF_VOID__  0
#define __SIZE_OF_CHAR__  1
#define __SIZE_OF_INT__   4
#define __SIZE_OF_PTR__   4
#define __SIZE_OF_FLOAT__ 8

/*
==================================================================================================================
Global Variables used in the translator: (declared in translator.cxx)
==================================================================================================================
- STPtr  __CURRENT_SYMBOL_TABLE__           | Points to current symbol table.
- STPtr  __GLOBAL_SYMBOL_TABLE__            | Points to global symbol table.
- QTPtr  __GLOBAL_QUAD_TABLE__              | Points to the global quad table (singleton instnace)
- int    __SYMBOL_TABLE_COUNT__             | Count of symbol tables.
- sPtr   __CURR_SYMBOL__                    | Points to current symbol.
- string __CURR_BLOCK__                     | Name of current block.
==================================================================================================================
*/

extern STPtr __CURRENT_SYMBOL_TABLE__;
extern STPtr __GLOBAL_SYMBOL_TABLE__;
extern QTPtr __GLOBAL_QUAD_TABLE__;
extern int __SYMBOL_TABLE_COUNT__;
extern sPtr __CURR_SYMBOL__;
extern string __CURR_BLOCK__;

/*
==================================================================================================================
Class symbol:
==================================================================================================================
- string name         | Name of the symbol.
- tPtr type           | Type of the symbol.
- string initValue    | Initial value of the symbol.
- int size            | Size of the symbol.
- int offset          | Offset of the symbol.
- STPtr nestedTable   | Nested symbol table if the symbol is a function/record.
==================================================================================================================
- symbol(string, string = "int", tPtr = NULL, int = 0)   | Constructor to initialize a symbol.

- string getName() const                                 | Get function for name.
- tPtr getType() const                                   | Get function for type.
- string getInitValue() const                            | Get function for initial value.
- int getSize() const                                    | Get function for size.
- int getOffset() const                                  | Get function for offset.
- STPtr getNestedTable() const                           | Get function for nested table.

- void setName(const string &)                           | Set function for name.
- void setType(tPtr)                                     | Set function for type.
- void setInitValue(const string &)                      | Set function for initial value.
- void setSize(int)                                      | Set function for size.
- void setOffset(int)                                    | Set function for offset.
- void setNestedTable(STPtr)                             | Set function for nested table.
- sPtr update(tPtr)                                      | Updates the type of the symbol.
==================================================================================================================
*/

class symbol
{
private:
    string name;
    string initValue;
    STPtr nestedTable;
    tPtr type;
    int size;
    int offset;

public:
    symbol(string, string = "int", tPtr = NULL, int = 0);

    string getName() const;
    tPtr getType() const;
    string getInitValue() const;
    int getSize() const;
    int getOffset() const;
    STPtr getNestedTable() const;

    void setName(const string &name_);
    void setType(tPtr type_);
    void setInitValue(const string &initValue_);
    void setSize(int size_);
    void setOffset(int offset_);
    void setNestedTable(STPtr nestedTable_);

    sPtr update(tPtr t);
};

/*
==================================================================================================================
Class symbolType:
==================================================================================================================
- string base         | Base type of symbol.
- int width           | Width of symbol, 1 by default. Size for arrays.
- tPtr arrType        | Array type of symbol.
==================================================================================================================
- symbolType(string, tPtr = NULL, int = 1)               | Constructor to initialize a symbol type.

- string getBase() const                                 | Get function for base.
- int getWidth() const                                   | Get function for width.
- tPtr getArrType() const                                | Get function for array type.

- void setBase(const string &)                           | Set function for base.
- void setWidth(int)                                     | Set function for width.
- void setArrType(tPtr)                                  | Set function for array type.
==================================================================================================================
*/

class symbolType
{
private:
    string base;
    int width;
    tPtr arrType;

public:
    symbolType(string base_, tPtr arrType_ = NULL, int width_ = 1);

    string getBase() const;
    int getWidth() const;
    tPtr getArrType() const;

    void setBase(const string &base_);
    void setWidth(int width_);
    void setArrType(tPtr arrType_);
};

/*
==================================================================================================================
Class symbolTable:
==================================================================================================================
- string name         | Name of symbol table.
- int count           | Count of symbols in symbol table.
- list<symbol> table  | List of symbols in symbol table.
- STPtr parent        | Parent symbol table.
==================================================================================================================
- symbolTable(string = "NULL")                           | Constructor to initialize a symbol table.
- sPtr lookup(string)                                    | Lookup for symbol in symbol table.
- static sPtr gentemp(tPtr, string = "")                 | Generate temporary symbol.
- void update()                                          | Update offset of symbols in symbol table.
- void print()                                           | Print symbol table.
- void StructureTree()                                   | Print the DFS tree of nested Symbol Tables

- string getName() const                                 | Get function for name.
- int getCount() const                                   | Get function for count.
- list<symbol>& getTable()                               | Get function for table.
- STPtr getParent() const                                | Get function for parent.

- void setName(const string &)                           | Set function for name.
- void setCount(int)                                     | Set function for count.
- void setTable(const list<symbol> &)                    | Set function for table.
- void setParent(STPtr)                                  | Set function for parent.
==================================================================================================================
*/

class symbolTable
{
private:
    string name;
    STPtr parent;
    int count;
    list<symbol> table;

public:
    symbolTable(string name_ = "NULL");

    sPtr lookup(string name);
    static sPtr gentemp(tPtr type_, string initValue_ = "");
    void print(bool nested = false);
    void StructureTree(int depth = 0, int last = 0);
    void update();

    string getName() const;
    int getCount() const;
    list<symbol> &getTable();
    STPtr getParent() const;

    void setName(const string &name_);
    void setCount(int count_);
    void setTable(const list<symbol> &table_);
    void setParent(STPtr parent_);
};

/*
==================================================================================================================
Class quad:
==================================================================================================================
- string opcode       | Opcode of quad.
- string arg1         | First argument of quad.
- string arg2         | Second argument of quad.
- string result       | Result of quad.
==================================================================================================================
- quad(string, string, string = "=", string = "")        | Constructor for string argument.
- quad(string, int, string = "=", string = "")           | Constructor for int argument.
- quad(string, float, string = "=", string = "")         | Constructor for float argument.

- string getOpcode() const                               | Get function for opcode.
- string getarg1() const                                 | Get function for first argument.
- string getarg2() const                                 | Get function for second argument.
- string getResult() const                               | Get function for result.

- void setOpcode(const string &)                         | Set function for opcode.
- void setarg1(const string &)                           | Set function for first argument.
- void setarg2(const string &)                           | Set function for second argument.
- void setResult(const string &)                         | Set function for result.
- void print()                                           | Print quad.
==================================================================================================================
*/

class quad
{
private:
    string opcode;
    string arg1;
    string arg2;
    string result;

public:
    quad(string res_, string arg1_, string op_ = "=", string arg2_ = "");
    quad(string res_, int arg1_, string op_ = "=", string arg2_ = "");
    quad(string res_, float arg1_, string op_ = "=", string arg2_ = "");

    string getOpcode() const;
    string getarg1() const;
    string getarg2() const;
    string getResult() const;

    void setOpcode(const string &opcode_);
    void setarg1(const string &arg1_);
    void setarg2(const string &arg2_);
    void setResult(const string &result_);

    void print();
};

/*
==================================================================================================================
Class quadArray: (Singleton class)
==================================================================================================================
- vector<quad> array         | Vector of quads.
- static quadArray* instance | Singleton instance of quad array.
==================================================================================================================
- quadArray()                                            | Private Constructor to initialize quad array.
- static quadArray* init()                               | Initialize singleton instance of quad array

- void print()                                           | Print quad array.
- vector<quad>& getArray()                               | Get function for array.
- void setArray(const vector<quad>&)                     | Set function for array.
- quad get(int) const                                    | Get quad at index.
- quad& getQuad(int)                                     | Get reference to quad at index.
- int getsize()                                          | Get size of quad array.

- quadArray(const quadArray&) = delete                   | Disable copy constructor.
- quadArray& operator=(const quadArray&) = delete;       | Disable assignment operator.
==================================================================================================================
*/

class quadArray
{
private:
    vector<quad> array;
    static quadArray *instance;
    quadArray() {}

public:
    quadArray(const quadArray &) = delete;
    quadArray &operator=(const quadArray &) = delete;
    static quadArray *init();

    void print();
    vector<quad> &getArray();
    void setArray(const vector<quad> &array_);
    void insert(quad q);
    quad get(int index) const;
    quad &getQuad(int index);
    int getsize();
};
/*
==================================================================================================================
Emit Functions:
==================================================================================================================
An overloaded static method to add a (newly generated) quad of the form: result = arg1 op arg2
------------------------------------------------------------------------------------------------------------------
- op usually is a binary operator.
- If arg2 is missing, op is unary.
- If op also is missing, this is a copy instruction.
==================================================================================================================
- void emit(string, string, string = "", string = "")    | Emit quad with string arguments.
- void emit(string, string, int, string = "")            | Emit quad with int argument.
- void emit(string, string, float, string = "")          | Emit quad with float argument.
==================================================================================================================
*/

void emit(string opcode, string res, string arg1 = "", string arg2 = "");
void emit(string opcode, string res, int arg1, string arg2 = "");
void emit(string opcode, string res, float arg1, string arg2 = "");

/*
==================================================================================================================
Global Functions:
==================================================================================================================
- list<int> makelist(int i)                              | Make a new list with i as the only element, index of current quad.
- list<int> merge(list<int> &p1, list<int> &p2)          | Merge two lists, return merged list.
- void backpatch(list<int> p, int i)                     | Backpatch list p with i, update quad array.
- bool typecheck(tPtr t1, tPtr t2)                       | Check if types t1 and t2 are compatible for operations
- sPtr convType(sPtr s, string t)                        | Convert type of symbol s to t.
==================================================================================================================
*/

list<int> makelist(int i);
void backpatch(list<int> p, int i);
bool typecheck(tPtr t1, tPtr t2);
bool typecheck(sPtr &s1, sPtr &s2);
list<int> merge(list<int> &p1, list<int> &p2);
sPtr convType(sPtr s, string t);

/*
==================================================================================================================
Struct A:
==================================================================================================================
- string arrType      | Type of array. arr or ptr.
- sPtr addr           | Base symbol of array in Symbol Table.
- sPtr location       | To get address of array.
- tPtr type           | Type of array stored in symbol table.
==================================================================================================================
*/

typedef struct A
{
    string arrType;
    sPtr addr;
    sPtr location;
    tPtr type;
} A;

/*
==================================================================================================================
Struct S:
==================================================================================================================
- list<int> nextList  | List of nexts.
==================================================================================================================
- list<int>& getNextList()                               | Get function for nextList.
- void setNextList(const list<int>&)                     | Set function for nextList.
- void insert(int)                                       | Insert value into nextList.
==================================================================================================================
*/

typedef struct S
{
    list<int> nextList;
} S;

/*
==================================================================================================================
Struct E:
==================================================================================================================
- string exprType     | Type of expression. bool or not_bool.
- sPtr addr           | Base symbol of expression in Symbol Table.
- list<int> trueList  | List of statements for true.
- list<int> falseList | List of statements for false.
- list<int> nextList  | List of nexts.
==================================================================================================================
*/

typedef struct E
{
    string exprType;
    sPtr addr;
    list<int> trueList;
    list<int> falseList;
    list<int> nextList;
} E;

/*
==================================================================================================================
Helper Functions:
==================================================================================================================
- void switchTable(STPtr newTable)                       | Switch to new symbol table.
- int nextinstr()                                        | Return index of next quad.
- int sizeOfType(tPtr t)                                 | Return size of type t.
- string printType(tPtr t)                               | Return string representation of type t.
==================================================================================================================
*/

void switchTable(STPtr newTable);
int nextinstr();
int sizeOfType(tPtr t);
string printType(tPtr t);

/*
==================================================================================================================
Type Conversion Functions:
==================================================================================================================
- string convIntToStr(int n)                             | Convert int to string.
- string convFloatToStr(float f)                         | Convert float to string.
- E* convBool2Int(E *e)                                  | Convert expression of boolean type to int.
- E* convBool2Float(E *e)                                | Convert expression of boolean type to float.
- E* convBool2Char(E *e)                                 | Convert expression of boolean type to char.
- E* convInt2Bool(E *e)                                  | Convert expression of int type to boolean.
- E* convInt2Float(E *e)                                 | Convert expression of int type to float.
- E* convFloat2Bool(E *e)                                | Convert expression of float type to boolean.
- E* convChar2Int(E *e)                                  | Convert expression of char type to int.
- E* convChar2Float(E *e)                                | Convert expression of char type to float.
- E* convChar2Bool(E *e)                                 | Convert expression of char type to boolean.
==================================================================================================================
*/

string convIntToStr(int i);
string convFloatToStr(float f);

E *convBool2Int(E *);
E *convBool2Float(E *);
E *convBool2Char(E *);
E *convInt2Bool(E *);
E *convInt2Float(E *);
E *convFloat2Bool(E *);
E *convChar2Int(E *);
E *convChar2Float(E *);
E *convChar2Bool(E *);


#endif