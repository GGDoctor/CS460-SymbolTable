#ifndef SYMBOLTABLE_HPP
#define SYMBOLTABLE_HPP

#include <iostream>
#include <vector>
#include <unordered_map>
#include "Tokenization.hpp" // Include the header where Token is defined
#include "RecursiveDescentParser.hpp"

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
    int scope; //Changed from string
    vector<pair<string, string>> parameters;
    string datatype;
};

struct Procedure {
    string name;
    int scope; //Changed from string
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
    void populateSymbolTable(LCRS* symbols); // Declaration for populateSymbolTable
    void print() const;
private:
    unordered_map<string, Variable> symbolTableVariables;
    unordered_map<string, Function> symbolTableFunctions;
    unordered_map<string, Procedure> symbolTableProcedures;
};

// Function to handle syntax errors
void handleSyntaxErrors(const string& errorMessage, int lineNumber);

#endif /* SYMBOLTABLE_HPP */
