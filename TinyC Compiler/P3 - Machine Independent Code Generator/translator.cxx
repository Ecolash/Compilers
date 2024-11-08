#include "translator.h"
using namespace std;

/*================================================================================================================
Printing Formatters
================================================================================================================*/
string gen(int n, const string &s)
{
    string t;
    for (int i = 0; i < n; ++i) t += s;
    return t;
}

const int width = 170;
const string sep = gen(width, "═");
const string line = gen(width, "─");

void yyerror(const string &s)
{
    int line = yylineno;
    string loc = yytext;
    cerr << "!!! ERROR: " << s << " at line " << line << ", near '" << loc << "'" << endl;
    return;
}

/*================================================================================================================
Global Variables used in the translator:
=================================================================================================================*/

STPtr __CURRENT_SYMBOL_TABLE__;
STPtr __GLOBAL_SYMBOL_TABLE__;
QTPtr __GLOBAL_QUAD_TABLE__;
int __SYMBOL_TABLE_COUNT__;
sPtr __CURR_SYMBOL__;
string __CURR_BLOCK__;

string datatype;
int markers[1000];

/*================================================================================================================
Implementations of constructors and functions for the symbol class
================================================================================================================*/
symbol::symbol(string name_, string type_, tPtr arrType, int width)
    : name(name_), initValue("-"), offset(0), nestedTable(NULL)
{
    type = new symbolType(type_, arrType, width);
    size = sizeOfType(type);
}

string symbol::getName() const { return name; }
tPtr symbol::getType() const { return type; }
string symbol::getInitValue() const { return initValue; }
int symbol::getSize() const { return size; }
int symbol::getOffset() const { return offset; }
STPtr symbol::getNestedTable() const { return nestedTable; }

void symbol::setName(const string &name_) { name = name_; }
void symbol::setType(tPtr type_) { type = type_; }
void symbol::setInitValue(const string &initValue_) { initValue = initValue_; }
void symbol::setSize(int size_) { size = size_; }
void symbol::setOffset(int offset_) { offset = offset_; }
void symbol::setNestedTable(STPtr nestedTable_) { nestedTable = nestedTable_; }

sPtr symbol::update(tPtr t)
{
    type = t, size = sizeOfType(t);
    return this;
}
/*================================================================================================================
Implementations of constructors and functions for the symbolType class
================================================================================================================*/
symbolType::symbolType(string base_, tPtr arrType_, int width_)
    : base(base_), arrType(arrType_), width(width_) {}

string symbolType::getBase() const { return base; }
int symbolType::getWidth() const { return width; }
tPtr symbolType::getArrType() const { return arrType; }

void symbolType::setBase(const string &base_) { base = base_; }
void symbolType::setWidth(int width_) { width = width_; }
void symbolType::setArrType(tPtr arrType_) { arrType = arrType_; }

/*================================================================================================================
Implementations of constructors and functions for the symbolTable class
================================================================================================================*/
symbolTable::symbolTable(string name_)
    : name(name_), count(0), parent(NULL) {}

string symbolTable::getName() const { return name; }
int symbolTable::getCount() const { return count; }
list<symbol> &symbolTable::getTable() { return table; }
STPtr symbolTable::getParent() const { return parent; }

void symbolTable::setName(const string &name_) { name = name_; }
void symbolTable::setCount(int count_) { count = count_; }
void symbolTable::setTable(const list<symbol> &table_) { table = table_; }
void symbolTable::setParent(STPtr parent_) { parent = parent_; }

/*
Function: symbolTable::lookup
-----------------------------
This function looks up a symbol by name in the current symbol table and its parent tables.

1) Searches for the symbol in the current table using find_if - If found, returns a pointer to the symbol.
2) If not found, checks the parent table (if it exists) for the symbol - If found in the parent, returns the symbol from the parent.
3) If the symbol is not found and the current table is the active symbol table, creates a new symbol - Adds the new symbol to the table and returns a pointer to it.
4) If the symbol is found in the parent, returns the symbol from the parent.
5) If the symbol is not found in any table, returns NULL.
 */
sPtr symbolTable::lookup(string name)
{
    auto it = find_if(table.begin(), table.end(), [&](const symbol &sym) { return sym.getName() == name; });
    if (it != table.end()) return &(*it);

    sPtr s = NULL;
    if (this->parent != NULL) s = this->parent->lookup(name);
    if (__CURRENT_SYMBOL_TABLE__ == this  and !(s))
    {
        sPtr sym = new symbol(name);
        table.push_back(*sym);
        return &(table.back());
    }
    else if (s != NULL) return s;
    return NULL;
}

/*
Function: symbolTable::gentemp
------------------------------
This function generates a temporary symbol with a given type and initial value.

1) Creates a unique name for the temporary symbol using a counter.
2) Creates a new symbol with the generated name.
3) Sets the type, initial value, and size of the symbol.
4) Adds the symbol to the current symbol table.
5) Returns a pointer to the newly added symbol.
 */

sPtr symbolTable::gentemp(tPtr t, string initValue)
{
    string name = "t" + convIntToStr(__CURRENT_SYMBOL_TABLE__->count++);
    sPtr sym = new symbol(name);
    sym->setType(t);
    sym->setInitValue(initValue);
    sym->setSize(sizeOfType(t));
    __CURRENT_SYMBOL_TABLE__->table.push_back(*sym);
    return &(__CURRENT_SYMBOL_TABLE__->table.back());
}

/*
Function: symbolTable::print
----------------------------
This function prints the symbol table and optionally its nested tables.

1) Prints the header with the table name and parent table name.
2) Prints the column headers for the symbol attributes.
3) Iterates through the symbols in the table and prints their attributes - If a symbol has a nested table, adds it to the list of tables to print.
4) If nested printing is enabled, recursively prints the nested tables.
 */
void symbolTable::print(bool nested)
{
    cout << sep << endl;
    cout << " Symbol Table: " << setfill(' ') << left << setw(62) << this->name;
    cout << "| Parent Table: " << setfill(' ') << left << setw(50) << (this->parent ? this->parent->name : "NULL") << endl;
    cout << line << endl;

    cout << setfill(' ') << left << setw(45) << " Name" << "│ ";
    cout << left << setw(30) << "Type" << "│ ";
    cout << left << setw(30) << "Initial Value" << "│ ";
    cout << left << setw(10) << "Size" << "│ ";
    cout << left << setw(10) << "Offset" << "│ ";
    cout << left << "Nested" << endl;
    cout << line << endl;

    STPtr tableList[100];
    int size = 0;
    for (auto &sym : this->table)
    {
        cout << " " << left << setw(44) << sym.getName() << "│ ";
        cout << left << setw(30) << printType(sym.getType()) << "│ ";
        cout << left << setw(30) << (sym.getInitValue() != "" ? sym.getInitValue() : "-") << "│ ";
        cout << left << setw(10) << sym.getSize() << "│ ";
        cout << left << setw(10) << sym.getOffset() << "│ ";
        cout << left;

        if (sym.getNestedTable()) tableList[size++] = sym.getNestedTable();
        (sym.getNestedTable()) ? cout << sym.getNestedTable()->name << endl : cout << "NULL" << endl;
    }

    cout << line << endl << endl;
    if (nested) for (int i = 0; i < size; i++) tableList[i]->print(nested);
}

/*
Function: symbolTable::StructureTree
------------------------------------
This function prints the structure of the symbol table tree.

1) Prints the current depth markers.
2) Prints the current table name with appropriate tree structure symbols.
3) If the table is empty, returns.
4) Iterates through the symbols and recursively prints the nested tables.
 */
void symbolTable::StructureTree(int depth, int last)
{
    for (int i = 0; i < depth - 1; i++) 
    {
        if (markers[i]) cout << " │ ";
        else cout << "   ";
    }

    if (depth > 0) cout << (last ? " └─ " : " ├─ ");
    cout << this->name << endl;

    if (this->table.empty()) return;
    int n = this->table.size(), i = 0;
    if (depth > 0) markers[depth - 1] = !last;
    for (auto it = this->table.begin(); it != this->table.end(); ++it, ++i) 
        if (it->getNestedTable())  it->getNestedTable()->StructureTree(depth + 1, i == n - 1);
}

/*
Function: symbolTable::update
-----------------------------
This function updates the offsets of symbols in the table and recursively updates nested tables.
1) Initializes the offset to 0.
2) Iterates through the symbols in the table and sets their offsets.
   - Adds the size of each symbol to the offset.
   - If a symbol has a nested table, adds it to the list of tables to update.

3) Recursively updates the nested tables.
 */
void symbolTable::update()
{
    list<STPtr> tableList;
    int offset = 0;
    for (auto &sym : table)
    {
        sym.setOffset(offset);
        offset += sym.getSize();
        if (sym.getNestedTable()) tableList.push_back(sym.getNestedTable());
    }

    for (auto &nestedTable : tableList) nestedTable->update();
}

/*================================================================================================================
Implementations of constructors and functions for the quad class
================================================================================================================*/

quad::quad(string res_, string arg1_, string op_, string arg2_)
    : result(res_), arg1(arg1_), opcode(op_), arg2(arg2_) {}

quad::quad(string res_, int arg1_, string op_, string arg2_)
    : result(res_), arg1(convIntToStr(arg1_)), opcode(op_), arg2(arg2_) {}

quad::quad(string res_, float arg1_, string op_, string arg2_)
    : result(res_), arg1(convFloatToStr(arg1_)), opcode(op_), arg2(arg2_) {}

string quad::getOpcode() const { return opcode; }
string quad::getarg1() const { return arg1; }
string quad::getarg2() const { return arg2; }
string quad::getResult() const { return result; }

void quad::setOpcode(const string &opcode_) { opcode = opcode_; }
void quad::setarg1(const string &arg1_) { arg1 = arg1_; }
void quad::setarg2(const string &arg2_) { arg2 = arg2_; }
void quad::setResult(const string &result_) { result = result_; }

/*
Function: quad::print
---------------------
This function prints the quad representation based on the opcode.

1) Checks if the opcode is one of the following: "=", "*=", "[]=", "=[]", "call", "label".
   - If opcode is "=", prints result = arg1.
   - If opcode is "*=", prints *result = arg1.
   - If opcode is "[]=", prints result[arg1] = arg2.
   - If opcode is "=[]", prints result = arg1[arg2].
   - If opcode is "call", prints result = call arg1, arg2.
   - If opcode is "label", prints result:.

2) Defines four sets of opcodes: opset1, opset2, opset3, opset4.
   - opset1: {"goto", "param", "return"}.
   - opset2: {"+", "-", "*", "/", "%", "^", "|", "&", "<<", ">>"}.
   - opset3: {"==", "!=", "<", ">", "<=", ">="}.
   - opset4: {"= &", "= *", "= -", "= ~", "= !"}.

3) Iterates through each set of opcodes and prints the corresponding quad representation:
   - For opset1, prints opcode result.
   - For opset2, prints result = arg1 opcode arg2.
   - For opset3, prints if arg1 opcode arg2 goto result.
   - For opset4, prints result = opcode.substr(2) arg1.

4) If an invalid operator is encountered, calls yyerror with an appropriate message.
 */
void quad::print()
{
    if (opcode == "=" || opcode == "*=" || opcode == "[]=" || opcode == "=[]" || opcode == "call" || opcode == "label")
    {
        if (opcode == "=") cout << result << " = " << arg1;
        else if (opcode == "*=") cout << "*" << result << " = " << arg1;
        else if (opcode == "[]=") cout << result << "[" << arg1 << "] = " << arg2;
        else if (opcode == "=[]") cout << result << " = " << arg1 << "[" << arg2 << "]";
        else if (opcode == "call") cout << result << " = call " << arg1 << ", " << arg2;
        else if (opcode == "label") cout << result << ": ";
        return;
    }

    string opset1[] = {"goto", "param", "return"};
    string opset2[] = {"+", "-", "*", "/", "%", "^", "|", "&", "<<", ">>"};
    string opset3[] = {"==", "!=", "<", ">", "<=", ">="};
    string opset4[] = {"= &", "= *", "= -", "= ~", "= !"};

    for (const auto &op : opset1) if (opcode == op) { cout << opcode << " " << result; return; }
    for (const auto &op : opset2) if (opcode == op) { cout << result << " = " << arg1 << " " << opcode << " " << arg2; return; }
    for (const auto &op : opset3) if (opcode == op) { cout << "if " << arg1 << " " << opcode << " " << arg2 << " goto " << result; return; }
    for (const auto &op : opset4) if (opcode == op) { cout << result << " = " << opcode.substr(2) << arg1; return; }
    yyerror(" [ Quad::print ] - Invalid operator encountered");
}

/*================================================================================================================
Implementations of singleton class function init() and functions for the quadArray class
================================================================================================================*/
quadArray *quadArray::instance = NULL;

quadArray *quadArray::init()
{
    if (!instance) instance = new quadArray();
    return instance;
}

vector<quad> &quadArray::getArray() { return array; }
void quadArray::setArray(const vector<quad> &array_) { array = array_; }
void quadArray::insert(quad q) { array.push_back(q); }
quad quadArray::get(int index) const { return array.at(index); }
quad &quadArray::getQuad(int index) { return array.at(index); }
int quadArray::getsize() { return array.size(); }

/**
Function: quadArray::print
--------------------------
This function prints the three-address code (TAC) representation of the quads stored in the quadArray.
 *
The function performs the following steps:
1) Prints a separator line and the header "THREE ADDRESS CODE (TAC)".
2) Calculates the number of digits in the size of the quad array for formatting purposes.
3) Iterates through each quad in the array:
   - Converts the index to a string and pads it with spaces for alignment.
   - Calls the print method of the current quad to print its details.

4) Prints a newline at the end.
 */
void quadArray::print()
{
    int cnt = 0;
    cout << sep << endl;
    cout << "THREE ADDRESS CODE (TAC):" << endl;
    cout << sep << endl;

    int numDigits = to_string(this->array.size()).length();
    for (size_t i = 0; i < this->array.size(); ++i)
    {
        string s = to_string(i);
        s.insert(s.begin(), numDigits - s.length(), ' ');
        if (this->array[i].getOpcode() != "label") cout << left << setw(numDigits + 3) << ("[" + s + "]") << "│    ";
        else cout << endl << left << setw(numDigits + 3) << ("[" + s + "]") << "│ ";
        this->array[i].print();
        cout << endl;
    }
    cout << endl;
}

/*================================================================================================================
Implementations of Overloaded emit functions
================================================================================================================*/

void emit(string op, string result, string arg1, string arg2) { __GLOBAL_QUAD_TABLE__->insert(quad(result, arg1, op, arg2)); }
void emit(string op, string result, int arg1, string arg2) { __GLOBAL_QUAD_TABLE__->insert(quad(result, arg1, op, arg2)); }
void emit(string op, string result, float arg1, string arg2) { __GLOBAL_QUAD_TABLE__->insert(quad(result, arg1, op, arg2)); }

/*================================================================================================================
Implementations of Global functions
================================================================================================================*/
/*
Function: makelist
------------------
This function creates a list containing a single integer.
1) Initializes a list with one element, the integer passed as an argument.
2) Returns the created list.
*/
list<int> makelist(int i)
{
    list<int> l(1, i);
    return l;
}

/*
Function: merge
---------------
This function merges two lists of integers.
1) Merges the second list into the first list.
2) Returns the merged list.
*/
list<int> merge(list<int> &list1, list<int> &list2)
{
    list1.merge(list2);
    return list1;
}

/*
Function: backpatch
-------------------
This function updates the result field of quads in a global quad table.
1) Converts the given address to a string.
2) Iterates over the list of indices.
3) For each index, updates the result field of the corresponding quad in the global quad table.
*/
void backpatch(list<int> l, int address)
{
    string str = convIntToStr(address);
    for (int index : l)
        __GLOBAL_QUAD_TABLE__->getQuad(index).setResult(str);
}

/*
Function: typecheck (sPtr &s1, sPtr &s2)
----------------------------------------
This function checks if two symbols have compatible types.
1) Checks if the types of the two symbols are the same.
2) If not, tries to convert the first symbol to the type of the second symbol and checks again.
3) If still not compatible, tries to convert the second symbol to the type of the first symbol and checks again.
4) Returns true if any of the above checks succeed, otherwise returns false.
*/
bool typecheck(sPtr &s1, sPtr &s2)
{
    if (typecheck(s1->getType(), s2->getType())) return true;
    if (s1 == convType(s1, s2->getType()->getBase())) return true;
    if (s2 == convType(s2, s1->getType()->getBase())) return true;
    return false;
}

/*
Function: typecheck (tPtr t1, tPtr t2)
-------------------------------------
This function checks if two types are compatible.
1) Returns true if both types are NULL.
2) Returns false if one type is NULL and the other is not.
3) Checks if the base types of the two types are the same.
4) Recursively checks if the array types of the two types are compatible.
5) Returns true if all checks succeed, otherwise returns false.
*/
bool typecheck(tPtr t1, tPtr t2)
{
    if (t1 == NULL && t2 == NULL) return true;
    if (t1 == NULL || t2 == NULL) return false;
    if (t1->getBase() != t2->getBase()) return false;
    return typecheck(t1->getArrType(), t2->getArrType());
}

/*================================================================================================================
Implementations of Type Conversion functions
==================================================================================================================
| Function       | Source Type | Target Type | Description                          |
|----------------|-------------|-------------|--------------------------------------|
| convBool2Int   | bool        | int         | Converts boolean to integer          |
| convBool2Float | bool        | float       | Converts boolean to float            |
| convBool2Char  | bool        | char        | Converts boolean to char             |
| convInt2Bool   | int         | bool        | Converts integer to boolean          |
| convInt2Float  | int         | float       | Converts integer to float            |
| convFloatool   | float       | bool        | Converts float to boolean            |
| convChar2Int   | char        | int         | Converts char to integer             |
| convChar2Float | char        | float       | Converts char to float               |
| convChar2Bool  | char        | bool        | Converts char to boolean             |
=================================================================================================================*/

string convIntToStr(int i) { return to_string(i); }
string convFloatToStr(float f) { return to_string(f); }

E *convBool2Int(E *expr)
{
    if (expr->exprType == "bool")
    {
        expr->addr = symbolTable::gentemp(new symbolType("int"));
        backpatch(expr->trueList, nextinstr());
        emit("=", expr->addr->getName(), "true");
        emit("goto", convIntToStr(nextinstr() + 1));
        backpatch(expr->falseList, nextinstr());
        emit("=", expr->addr->getName(), "false");
    }
    return expr;
}

E *convInt2Bool(E *expr)
{
    if (expr->exprType != "bool")
    {
        expr->falseList = makelist(nextinstr()); 
        emit("==", expr->addr->getName(), "0");
        expr->trueList = makelist(nextinstr()); 
        emit("goto", "");
    }
    return expr;
}

E *convBool2Float(E *expr)
{
    if (expr->exprType == "bool")
    {
        expr->exprType = "float";
        expr->addr = symbolTable::gentemp(new symbolType("float"));
        backpatch(expr->trueList, nextinstr());
        emit("=", expr->addr->getName(), "1.000000");
        emit("goto", convIntToStr(nextinstr() + 1), "", "");
        backpatch(expr->falseList, nextinstr());
        emit("=", expr->addr->getName(), "0.000000");
    }
    return expr;
}

E *convBool2Char(E *expr)
{
    if (expr->exprType == "bool")
    {
        expr->exprType = "char";
        expr->addr = symbolTable::gentemp(new symbolType("char"));
        backpatch(expr->trueList, nextinstr());
        emit("=", expr->addr->getName(), "1");
        emit("goto", convIntToStr(nextinstr() + 1), "", "");
        backpatch(expr->falseList, nextinstr());
        emit("=", expr->addr->getName(), "0");
    }
    return expr;
}

E *convInt2Float(E *expr)
{
    if (expr->exprType == "int")
    {
        expr->exprType = "float";
        expr->addr = symbolTable::gentemp(new symbolType("float"));
        emit("=", expr->addr->getName(), "intTofloat(" + expr->addr->getName() + ")");
    }
    return expr;
}

E *convFloat2Bool(E *expr)
{
    if (expr->exprType == "float")
    {
        expr->exprType = "bool";
        expr->falseList = makelist(nextinstr());
        emit("==", "", expr->addr->getName(), "0.000000");
        expr->trueList = makelist(nextinstr());
        emit("goto", "", "", "");
    }
    return expr;
}

E *convChar2Int(E *expr)
{
    if (expr->exprType == "char")
    {
        expr->exprType = "int";
        expr->addr = symbolTable::gentemp(new symbolType("int"));
        emit("=", expr->addr->getName(), "charToint(" + expr->addr->getName() + ")");
    }
    return expr;
}

E *convChar2Float(E *expr)
{
    if (expr->exprType == "char")
    {
        expr->exprType = "float";
        expr->addr = symbolTable::gentemp(new symbolType("float"));
        emit("=", expr->addr->getName(), "charTofloat(" + expr->addr->getName() + ")");
    }
    return expr;
}

E *convChar2Bool(E *expr)
{
    if (expr->exprType == "char")
    {
        expr->exprType = "bool";
        expr->falseList = makelist(nextinstr());
        emit("==", "", expr->addr->getName(), "0");
        expr->trueList = makelist(nextinstr());
        emit("goto", "", "", "");
    }
    return expr;
}

/*================================================================================================================
Implementations of Helper functions
================================================================================================================*/
sPtr convType(sPtr s, string t)
{
    sPtr temp = symbolTable::gentemp(new symbolType(t));
    string base = s->getType()->getBase();
    if (base == t) return s;

    if (!t.empty()) t[0] = toupper(t[0]);
    if (!base.empty()) base[0] = toupper(base[0]);
    string conversion = base + "2" + t;
    emit("=", temp->getName(), conversion + "(" + s->getName() + ")");
    return temp;
}

void switchTable(STPtr newTable) { __CURRENT_SYMBOL_TABLE__ = newTable; }
int nextinstr() { return __GLOBAL_QUAD_TABLE__->getsize(); }

int sizeOfType(tPtr t)
{
    if (t == NULL) return 0;
    if (t->getBase() == "func") return 0;

    switch (t->getBase()[0])
    {
        case 'v': return __SIZE_OF_VOID__;
        case 'c': return __SIZE_OF_CHAR__;
        case 'i': return __SIZE_OF_INT__;
        case 'p': return __SIZE_OF_PTR__;
        case 'f': return __SIZE_OF_FLOAT__;
        case 'a': return t->getWidth() * sizeOfType(t->getArrType());
        default: return -1;
    }
}

string printType(tPtr t)
{
    if (t == NULL) return "null";
    if (t->getBase() == "func") return "func";

    switch (t->getBase()[0])
    {
        case 'v': return "void";
        case 'c': return "char";
        case 'i': return "int";
        case 'f': return "float";
        case 'b': return "block";
        case 'p': return "ptr(" + printType(t->getArrType()) + ")";
        case 'a': return "arr(" + convIntToStr(t->getWidth()) + ", " + printType(t->getArrType()) + ")";
        default: yyerror(" [ printType ] - Invalid type encountered");
    }
    return "null";
}

int main(int argc, char *argv[])
{
    yyin = stdin;
    if (argc > 1)
    {
        FILE *file = fopen(argv[1], "r");
        if (!file) fprintf(stderr, "Error opening file: %s\n", argv[1]);
        if (!file) exit(1);
        yyin = file;
    }

    __SYMBOL_TABLE_COUNT__ = 0;
    __GLOBAL_SYMBOL_TABLE__ = new symbolTable("Global");
    __CURRENT_SYMBOL_TABLE__ = __GLOBAL_SYMBOL_TABLE__;
    __GLOBAL_QUAD_TABLE__ = quadArray::init();
    __CURR_BLOCK__ = "";

    cout << "Source File: " << argv[1] << endl;
    cout << "Generated at: "<< __DATE__ << ", " << __TIME__ << endl;
    cout << sep << endl;
    yyparse();

    __GLOBAL_SYMBOL_TABLE__->update();
    __GLOBAL_QUAD_TABLE__->print();
    cout << sep << endl;
    cout << "GENERATED SYMBOL TABLES:" << endl;
    cout << sep << endl;
    cout << "NESTING OF SYMBOL TABLES: " << endl;
    cout << line << endl;
    __GLOBAL_SYMBOL_TABLE__->StructureTree();
    __GLOBAL_SYMBOL_TABLE__->print(true);
    return 0;
}