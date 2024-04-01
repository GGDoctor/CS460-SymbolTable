#include "symboltable.hpp"

SymbolTable::SymbolTable() {
    // Initialize the symbol table
}

void SymbolTable::insertVariable(const Variable& variable) {
    symbolTableVariables[variable.name] = variable;
}

void SymbolTable::insertFunction(const Function& function) {
    symbolTableFunctions[function.name] = function;
}

void SymbolTable::insertProcedure(const Procedure& procedure) {
    symbolTableProcedures[procedure.name] = procedure;
}

void SymbolTable::print() const {
    cout << "Symbol Table:" << endl;
    // Print variables
    for (const auto& entry : symbolTableVariables) {
        const Variable& variable = entry.second;
        cout << "IDENTIFIER_NAME: " << variable.name << endl;
        cout << "IDENTIFIER_TYPE: variable" << endl;
        cout << "DATATYPE: " << variable.type << endl;
        cout << "DATATYPE_IS_ARRAY: no" << endl;
        cout << "DATATYPE_ARRAY_SIZE: 0" << endl;
        cout << "SCOPE: " << variable.scope << endl;
        cout << endl;
    }

    // Print functions
    for (const auto& entry : symbolTableFunctions) {
        const Function& function = entry.second;
        cout << "IDENTIFIER_NAME: " << function.name << endl;
        cout << "IDENTIFIER_TYPE: function" << endl;
        cout << "DATATYPE: " << function.returnType << endl;
        cout << "DATATYPE_IS_ARRAY: no" << endl;
        cout << "DATATYPE_ARRAY_SIZE: 0" << endl;
        cout << "SCOPE: " << function.scope << endl;
        cout << "PARAMETER LIST FOR: " << function.name << endl;
        for (const auto& param : function.parameters) {
            cout << "IDENTIFIER_NAME: " << param.first << endl;
            cout << "DATATYPE: " << param.second << endl;
            cout << "DATATYPE_IS_ARRAY: no" << endl; 
            cout << "DATATYPE_ARRAY_SIZE: 0" << endl; 
            cout << "SCOPE: " << function.scope << endl;
        }
        cout << endl;
    }

    // Print procedures
    for (const auto& entry : symbolTableProcedures) {
        const Procedure& procedure = entry.second;
        cout << "IDENTIFIER_NAME: " << procedure.name << endl;
        cout << "IDENTIFIER_TYPE: procedure" << endl;
        cout << "DATATYPE: NOT APPLICABLE" << endl;
        cout << "DATATYPE_IS_ARRAY: no" << endl;
        cout << "DATATYPE_ARRAY_SIZE: 0" << endl;
        cout << "SCOPE: " << procedure.scope << endl;
        cout << "PARAMETER LIST FOR: " << procedure.name << endl;
        for (const auto& param : procedure.parameters) {
            cout << "IDENTIFIER_NAME: " << param.first << endl;
            cout << "DATATYPE: " << param.second << endl;
            cout << "DATATYPE_IS_ARRAY: no" << endl; 
            cout << "DATATYPE_ARRAY_SIZE: 0" << endl; // Assuming parameters are not arrays
            cout << "SCOPE: " << procedure.scope << endl;
        }
        cout << endl;
    }
}

void handleSyntaxErrors(const string& errorMessage, int lineNumber) {
    cerr << "Error on line " << lineNumber << ": " << errorMessage << endl;
}
