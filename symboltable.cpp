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

void SymbolTable::populateSymbolTable(const vector<Token>& tokens) {
    /*
    *   Changed the type of scope in .h and here to int so we can track it easier
    */


    int currentScope; // To keep track of the current scope
    string currentFunction; // To keep track of the current function being processed
    vector<pair<string, string>> currentParameters; // To store parameters of the current function/procedure
    
    // Iterate over the tokens
    for (size_t i = 0; i < tokens.size(); ++i) {
        const Token& token = tokens[i];

        // Note that the token.type is not actually IDENTIFIER it is 2, refer to Tokenixation.hpp
        // cout<< token.type << " " << token.character << " " << isdigit(token.type) << endl;

        int scope = currentScope;
       
        // Check for function definitions
        if (token.type == IDENTIFIER && (token.character == "function" || token.character == "procedure")) {
            // Extract function/procedure name and scope
            string name = tokens[i + 2].character;
            // string scope = currentScope;

            // Check if it's a function or procedure
            if (token.character == "function") {
                // Extract return type
                string returnType = tokens[i + 1].character;

                // Insert da function into the symbol table
                Function function;
                function.name = name;
                function.returnType = returnType;
                function.scope = scope;
                function.parameters = currentParameters;
                insertFunction(function);

                // Update da current function and clear parameters
                currentFunction = name;
                currentParameters.clear();
            } 
            else if (token.character == "procedure") {
                // Insert da procedure into the symbol table
                Procedure procedure;
                procedure.name = name;
                procedure.scope = scope;
                procedure.parameters = currentParameters;
                insertProcedure(procedure);

                // Update da current function and clear parameters
                currentFunction = name;
                currentParameters.clear();
            }
            scope += 1;
        }
    }
}

void SymbolTable::print() const {

    cout << "Symbol Table:" << endl << endl;
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
        //Need to fix this. Does not have to be here till (int n) or whatever
        // cout << "PARAMETER LIST FOR: " << function.name << endl;
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
        //Need to fix this. Does not have to be here till (int n) or whatever
        // cout << "PARAMETER LIST FOR: " << procedure.name << endl;
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


//I still dont know if this is a good idea but I give up and am tired
void handleSyntaxErrors(const string& errorMessage, int lineNumber) {
    cerr << "Error on line " << lineNumber << ": " << errorMessage << endl;
}
