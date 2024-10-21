#include "translator.h"
#include <iomanip>
using namespace std;

// Global variables as defined and explained in the header file
symbol* currentSymbol;
symbolTable* currentSymbolTable;
symbolTable* globalSymbolTable;
quadArray quadTable;
int SymbolTableCount;
string blockName;

// Used for storing the last encountered type
string data_type;

// Implementations of constructors and functions for the symbolType class
symbolType::symbolType(string base_, symbolType* arrType_, int width_):
    base(base_), width(width_), arrType(arrType_) {}

// Implementations of constructors and functions for the symbol class
symbol::symbol(string name_, string type_, symbolType* arrType, int width): name(name_), initValue("-"), offset(0), nestedTable(NULL) {
    type = new symbolType(type_, arrType, width);
    size = sizeOfType(type);
}

symbol* symbol::update(symbolType* t) {
    // Update the type and size for the symbol
    type = t;
    size = sizeOfType(t);
    return this;
}

// Implementations of constructors and functions for the symbolTable class
symbolTable::symbolTable(string name_): name(name_), count(0), parent(NULL) {}

symbol* symbolTable::lookup(string name) {
    // Start searching for the symbol in the symbol table
    for(list<symbol>::iterator it = table.begin(); it != table.end(); it++) {
        if(it->name == name) {
            return &(*it);
        }
    }

    // If not found, go up the hierarchy to search in the parent symbol tables
    symbol* s = NULL;
    if(this->parent != NULL) {
        s = this->parent->lookup(name);
    }

    if(currentSymbolTable == this && s == NULL) {
        // If the symbol is not found, create the symbol, add it to the symbol table and return a pointer to it
        symbol* sym = new symbol(name);
        table.push_back(*sym);
        return &(table.back());
    }
    else if(s != NULL) {
        // If the symbol is found in one of the parent symbol tables, return it
        return s;
    }

    return NULL;
}

symbol* symbolTable::gentemp(symbolType* t, string initValue) {
    // Create the name for the temporary
    string name = "t" + convIntToStr(currentSymbolTable->count++);
    symbol* sym = new symbol(name);
    sym->type = t;
    sym->initValue = initValue;         // Assign the initial value, if any
    sym->size = sizeOfType(t);

    // Add the temporary to the symbol table
    currentSymbolTable->table.push_back(*sym);
    return &(currentSymbolTable->table.back());
}

void symbolTable::print() {
    for(int i = 0; i < 120; i++) {
        cout << '-';
    }
    cout << endl;
    cout << "Symbol Table: " << setfill(' ') << left << setw(50) << this->name;
    cout << "Parent Table: " << setfill(' ') << left << setw(50) << ((this->parent != NULL) ? this->parent->name : "NULL") << endl;
    for(int i = 0; i < 120; i++) {
        cout << '-';
    }
    cout << endl;

    // Table Headers
    cout << setfill(' ') << left << setw(25) <<  "Name";
    cout << left << setw(25) << "Type";
    cout << left << setw(20) << "Initial Value";
    cout << left << setw(15) << "Size";
    cout << left << setw(15) << "Offset";
    cout << left << "Nested" << endl;

    for(int i = 0; i < 120; i++) {
        cout << '-';
    }
    cout << endl;

    list<symbolTable*> tableList;

    // Print the symbols in the symbol table
    for(list<symbol>::iterator it = this->table.begin(); it != this->table.end(); it++) {
        cout << left << setw(25) << it->name;
        cout << left << setw(25) << printType(it->type);
        cout << left << setw(20) << (it->initValue != "" ? it->initValue : "-");
        cout << left << setw(15) << it->size;
        cout << left << setw(15) << it->offset;
        cout << left;

        if(it->nestedTable != NULL) {
            cout << it->nestedTable->name << endl;
            tableList.push_back(it->nestedTable);
        }
        else {
            cout << "NULL" << endl;
        }
    }

    for(int i = 0; i < 120; i++) {
        cout << '-';
    }
    cout << endl << endl;

    // Recursively call the print function for the nested symbol tables
    for(list<symbolTable*>::iterator it = tableList.begin(); it != tableList.end(); it++) {
        (*it)->print();
    }

}

void symbolTable::update() {
    list<symbolTable*> tableList;
    int off_set;

    // Update the offsets of the symbols based on their sizes
    for(list<symbol>::iterator it = table.begin(); it != table.end(); it++) {
        if(it == table.begin()) {
            it->offset = 0;
            off_set = it->size;
        }
        else {
            it->offset = off_set;
            off_set = it->offset + it->size;
        }

        if(it->nestedTable != NULL) {
            tableList.push_back(it->nestedTable);
        }
    }

    // Recursively call the update function to update the offsets of symbols of the nested symbol tables
    for(list<symbolTable*>::iterator iter = tableList.begin(); iter != tableList.end(); iter++) {
        (*iter)->update();
    }
}

// Implementations of constructors and functions for the quad class
quad::quad(string res, string arg1_, string operation, string arg2_): result(res), arguement1(arg1_), opcode(operation), arguement2(arg2_) {}

quad::quad(string res, int arg1_, string operation, string arg2_): result(res), opcode(operation), arguement2(arg2_) {
    arguement1 = convIntToStr(arg1_);
}

quad::quad(string res, float arg1_, string operation, string arg2_): result(res), opcode(operation), arguement2(arg2_) {
    arguement1 = convFloatToStr(arg1_);
}

void quad::print() {
    if(opcode == "=")       // Simple assignment
        cout << result << " = " << arguement1;
    else if(opcode == "*=")
        cout << "*" << result << " = " << arguement1;
    else if(opcode == "[]=")
        cout << result << "[" << arguement1 << "]" << " = " << arguement2;
    else if(opcode == "=[]")
        cout << result << " = " << arguement1 << "[" << arguement2 << "]";
    else if(opcode == "goto" || opcode == "param" || opcode == "return")
        cout << opcode << " " << result;
    else if(opcode == "call")
        cout << result << " = " << "call " << arguement1 << ", " << arguement2;
    else if(opcode == "label")
        cout << result << ": ";

    // Binary Operators
    else if(opcode == "+" || opcode == "-" || opcode == "*" || opcode == "/" || opcode == "%" || opcode == "^" || opcode == "|" || opcode == "&" || opcode == "<<" || opcode == ">>")
        cout << result << " = " << arguement1 << " " << opcode << " " << arguement2;

    // Relational Operators
    else if(opcode == "==" || opcode == "!=" || opcode == "<" || opcode == ">" || opcode == "<=" || opcode == ">=")
        cout << "if " << arguement1 << " " << opcode << " " << arguement2 << " goto " << result;

    // Unary operators
    else if(opcode == "= &" || opcode == "= *" || opcode == "= -" || opcode == "= ~" || opcode == "= !")
        cout << result << " " << opcode << arguement1;

    else
        cout << "Unknown Operator";
}

// Implementations of constructors and functions for the quadArray class
void quadArray::print() {
    for(int i = 0; i < 120; i++) {
        cout << '-';
    }
    cout << endl;
    cout << "THREE ADDRESS CODE (TAC):" << endl;
    for(int i = 0; i < 120; i++) {
        cout << '-';
    }
    cout << endl;

    int cnt = 0;
    // Print each of the quads one by one
    for(vector<quad>::iterator it = this->array.begin(); it != this->array.end(); it++, cnt++) {
        if(it->opcode != "label") {
            cout << left << setw(4) << cnt << ":    ";
            it->print();
        }
        else {
            cout << endl << left << setw(4) << cnt << ": ";
            it->print();
        }
        cout << endl;
    }
}

// Overloaded emit functions
void emit(string op, string result, string arguement1, string arguement2) {
    quad* q = new quad(result, arguement1, op, arguement2);
    quadTable.array.push_back(*q);
}

void emit(string op, string result, int arguement1, string arguement2) {
    quad* q = new quad(result, arguement1, op, arguement2);
    quadTable.array.push_back(*q);
}

void emit(string op, string result, float arguement1, string arguement2) {
    quad* q = new quad(result, arguement1, op, arguement2);
    quadTable.array.push_back(*q);
}

// Implementation of the makelist function
list<int> makelist(int i) {
    list<int> l(1, i);
    return l;
}

// Implementation of the merge function
list<int> merge(list<int> &list1, list<int> &list2) {
    list1.merge(list2);
    return list1;
}

// Implementation of the backpatch function
void backpatch(list<int> l, int address) {
    string str = convIntToStr(address);
    for(list<int>::iterator it = l.begin(); it != l.end(); it++) {
        quadTable.array[*it].result = str;
    }
}

// Implementation of the typecheck functions
bool typecheck(symbol* &s1, symbol* &s2) {
    symbolType* t1 = s1->type;
    symbolType* t2 = s2->type;

    if(typecheck(t1, t2))
        return true;
    else if(s1 == convType(s1, t2->base))
        return true;
    else if(s2 == convType(s2, t1->base))
        return true;
    else
        return false;
}

bool typecheck(symbolType* t1, symbolType* t2) {
    if(t1 == NULL && t2 == NULL)
        return true;
    else if(t1 == NULL || t2 == NULL)
        return false;
    else if(t1->base != t2->base)
        return false;

    return typecheck(t1->arrType, t2->arrType);
}

// Implementation of the convType function
symbol* convType(symbol* s, string t) {
    symbol* temp = symbolTable::gentemp(new symbolType(t));

    if(s->type->base == "float") {
        if(t == "int") {
            emit("=", temp->name, "float2int(" + s->name + ")");
            return temp;
        }
        else if(t == "char") {
            emit("=", temp->name, "float2char(" + s->name + ")");
            return temp;
        }
        return s;
    }

    else if(s->type->base == "int") {
        if(t == "float") {
            emit("=", temp->name, "int2float(" + s->name + ")");
            return temp;
        }
        else if(t == "char") {
            emit("=", temp->name, "int2char(" + s->name + ")");
            return temp;
        }
        return s;
    }

    else if(s->type->base == "char") {
        if(t == "float") {
            emit("=", temp->name, "char2float(" + s->name + ")");
            return temp;
        }
        else if(t == "int") {
            emit("=", temp->name, "char2int(" + s->name + ")");
            return temp;
        }
        return s;
    }

    return s;
}

string convIntToStr(int i) {
    return to_string(i);
}

string convFloatToStr(float f) {
    return to_string(f);
}

// Implementation of the convIntToBool function
E* convIntToBool(E* expr) {
    if(expr->exprType != "bool") {
        expr->falseList = makelist(nextinstr());    // Add falselist for boolean expressions
        emit("==", expr->addr->name, "0");
        expr->trueList = makelist(nextinstr());     // Add truelist for boolean expressions
        emit("goto", "");
    }
    return expr;
}

// Implementation of the convBoolToInt function
E* convBoolToInt(E* expr) {
    if(expr->exprType == "bool") {
        expr->addr = symbolTable::gentemp(new symbolType("int"));
        backpatch(expr->trueList, nextinstr());
        emit("=", expr->addr->name, "true");
        emit("goto", convIntToStr(nextinstr() + 1));
        backpatch(expr->falseList, nextinstr());
        emit("=", expr->addr->name, "false");
    }
    return expr;
}

void switchTable(symbolTable* newTable) {
    currentSymbolTable = newTable;
}

int nextinstr() {
    return quadTable.array.size();
}

int sizeOfType(symbolType* t) {
    if(t->base == "void")
        return sizeof_void;
    else if(t->base == "char")
        return sizeof_char;
    else if(t->base == "int")
        return sizeof_int;
    else if(t->base == "ptr")
        return sizeof_pointer;
    else if(t->base == "float")
        return sizeof_float;
    else if(t->base == "arr")
        return t->width * sizeOfType(t->arrType);
    else if(t->base == "func")
        return 0;
    else
        return -1;
}

string printType(symbolType* t) {
    if(t == NULL)
        return "null";
    else if(t->base == "void" || t->base == "char" || t->base == "int" || t->base == "float" || t->base == "block" || t->base == "func")
        return t->base;
    else if(t->base == "ptr")
        return "ptr(" + printType(t->arrType) + ")";
    else if(t->base == "arr")
        return "arr(" + convIntToStr(t->width) + ", " + printType(t->arrType) + ")";
    else
        return "unknown";
}

int main() {
    SymbolTableCount = 0;                            // Initialize STCount to 0
    globalSymbolTable = new symbolTable("Global");   // Create global symbol table
    currentSymbolTable = globalSymbolTable;                   // Make global symbol table the currently active symbol table
    blockName = "";

    yyparse();
    globalSymbolTable->update();
    quadTable.print();       // Print Three Address Code
    cout << endl;
    globalSymbolTable->print();      // Print symbol tables

    return 0;
}