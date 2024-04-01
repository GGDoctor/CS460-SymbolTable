#ifndef SYMBOLTABLE_HPP
#define SYMBOLTABLE_HPP

#include <iostream>
#include <vector>
#include <unordered_map>
#include <sstream>

using namespace std;

// Struct for variables
struct Variable {
    string name;
    string type;
    string scope;
};

// Struct for functions
struct Function {
    string name;
    string returnType;
    string scope;
    vector<pair<string, string>> parameters; // (name, type)
};

// Struct for procedures
struct Procedure {
    string name;
    string scope;
    vector<pair<string, string>> parameters; // (name, type)
};

// Symbol table class
class SymbolTable {
public:
    // Constructor
    SymbolTable();

    // Function declarations
    void insertVariable(const Variable& variable);
    void insertFunction(const Function& function);
    void insertProcedure(const Procedure& procedure);
    void print() const;

private:
    // Data members
    unordered_map<string, Variable> symbolTableVariables;
    unordered_map<string, Function> symbolTableFunctions;
    unordered_map<string, Procedure> symbolTableProcedures;
};

// Function to handle syntax errors
void handleSyntaxErrors(const string& errorMessage, int lineNumber);

#endif /* SYMBOLTABLE_HPP */
