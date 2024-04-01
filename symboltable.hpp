#ifndef SYMBOLTABLE_HPP
#define SYMBOLTABLE_HPP

#include <iostream>
#include <vector>
#include <unordered_map>
#include "Tokenization.hpp" // Include the header where Token is defined

using namespace std;

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
    void insertVariable(const Variable& variable);
    void insertFunction(const Function& function);
    void insertProcedure(const Procedure& procedure);
    void populateSymbolTable(const vector<Token>& tokens); // Declaration for populateSymbolTable
    void print() const;
private:
    unordered_map<string, Variable> symbolTableVariables;
    unordered_map<string, Function> symbolTableFunctions;
    unordered_map<string, Procedure> symbolTableProcedures;
};

// Function to handle syntax errors
void handleSyntaxErrors(const string& errorMessage, int lineNumber);

#endif /* SYMBOLTABLE_HPP */
