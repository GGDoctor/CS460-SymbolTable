#ifndef SYMBOLTABLE_HPP
#define SYMBOLTABLE_HPP

#include <iostream>
#include <vector>
#include <unordered_map>
#include <list>
#include "Tokenization.hpp" // Include the header where Token is defined

using namespace std;

struct TableEntry {
    TableEntry() : identifierName(""), identifierType(""), datatype(""), 
                    datatypeIsArray(false), datatypeArraySize(0), scope(0) { }
    string identifierName;
    string identifierType;
    string datatype;
    bool datatypeIsArray;
    int datatypeArraySize;
    int scope;
};

struct ParamListEntry {
    ParamListEntry() : identifierName(""), datatype(""), 
                       datatypeIsArray(false), datatypeArraySize(0), 
                       scope(0) { }
    string identifierName;
    string datatype;
    bool datatypeIsArray;
    int datatypeArraySize;
    int scope;
};

enum StateDFA {
    OTHER_STATE,
    FUNCTION,
    PROCEDURE,
    VARIABLE,
};

// Structs for variables, functions, and procedures
struct Variable {
    string name;
    string type;
    string scope;
    string datatype;
};

struct Function {
    string name;
    string returnType;
    string scope;
    vector<pair<string, string>> parameters;
    string datatype;
};

struct Procedure {
    string name;
    string scope;
    vector<pair<string, string>> parameters;
    string datatype;
};

// Symbol table class
class SymbolTable {
public:
    SymbolTable();
    SymbolTable(const string& cst);
    void insertVariable(const Variable& variable);
    void insertFunction(const Function& function);
    void insertProcedure(const Procedure& procedure);
    void populateSymbolTable(const vector<Token>& tokens); // Declaration for populateSymbolTable
    void print() const;

    /**
     * @brief Output operator overload
     * @param os - The output stream operator
     * @param obj - The SymbolTable object to output
     * @returns The modified output stream
     * @remark Outputs symbol table according to project spec
     * 
     *      ex: cout << SymbolTableObj;
     */
    friend ostream& operator << (ostream& os, const SymbolTable& obj);
private:
    list<TableEntry> table;
    list<ParamListEntry> paramTable;

    unordered_map<string, Variable> symbolTableVariables;
    unordered_map<string, Function> symbolTableFunctions;
    unordered_map<string, Procedure> symbolTableProcedures;
};

// Function to handle syntax errors
void handleSyntaxErrors(const string& errorMessage, int lineNumber);

#endif /* SYMBOLTABLE_HPP */
