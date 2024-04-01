#include "symboltable.hpp"


// Function to insert a variable into the symbol table
void SymbolTable::insertVariable(const Variable& variable) {
    symbolTableVariables[variable.name] = variable;
}

// Function to insert a function into the symbol table
void SymbolTable::insertFunction(const Function& function) {
    symbolTableFunctions[function.name] = function;
}

// Function to insert a procedure into the symbol table
void SymbolTable::insertProcedure(const Procedure& procedure) {
    symbolTableProcedures[procedure.name] = procedure;
}

// Function to print the symbol table
void SymbolTable::print() const {
    cout << "Variable Symbol Table:" << endl;
    for (const auto& entry : symbolTableVariables) {
        const Variable& variable = entry.second;
        cout << "Name: " << variable.name << ", Type: " << variable.type << ", Scope: " << variable.scope << endl;
    }

    cout << "Function Symbol Table:" << endl;
    for (const auto& entry : symbolTableFunctions) {
        const Function& function = entry.second;
        cout << "Name: " << function.name << ", Return Type: " << function.returnType << ", Scope: " << function.scope << endl;
        cout << "Parameters:" << endl;
        for (const auto& param : function.parameters) {
            cout << param.first << ": " << param.second << endl;
        }
    }

    cout << "Procedure Symbol Table:" << endl;
    for (const auto& entry : symbolTableProcedures) {
        const Procedure& procedure = entry.second;
        cout << "Name: " << procedure.name << ", Scope: " << procedure.scope << endl;
        cout << "Parameters:" << endl;
        for (const auto& param : procedure.parameters) {
            cout << param.first << ": " << param.second << endl;
        }
    }
}


