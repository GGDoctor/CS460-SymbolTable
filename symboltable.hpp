#ifndef SYMBOLTABLE_HPP
#define SYMBOLTABLE_HPP

#include <iostream>
#include <vector>
#include <unordered_map>
#include <sstream>

// Using the std namespace
using namespace std;

//struct for da defined variables
struct Variable {
    string name;
    string type;
    string scope;
};

//struct for da functions
//"Functions and procedures may also have an input parameter list of variables and types."
struct Function {
    string name;
    string returnType;
    string scope;
    vector<pair<string, string>> parameters; // (name, type)
};

//struct for da procedures
//"Functions and procedures may also have an input parameter list of variables and types." 
struct Procedure {
    string name;
    string scope;
    vector<pair<string, string>> parameters; // (name, type)
};


class SymbolTable {
public:
    // Constructor
    SymbolTable() {
        // Initialize da symbol table
    }

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


// Function to handle syntax errors and output error messages
// I think creating a function might be an easier way to handle our errors but if you guys desagree you 
// can take this out.
void handleSyntaxErrors(const string& errorMessage, int lineNumber) {
    cerr << "Error on line " << lineNumber << ": " << errorMessage << endl;
}

// Function to output symbol table
void outputSymbolTable(const unordered_map<string, Variable>& symbolTable) {
    cout << "Symbol Table:" << endl;
    for (const auto& entry : symbolTable) {
        const Variable& variable = entry.second;
        cout << "Name: " << variable.name << ", Type: " << variable.type << ", Scope: " << variable.scope << endl;
    }
}

#endif /* SYMBOLTABLE_HPP */
