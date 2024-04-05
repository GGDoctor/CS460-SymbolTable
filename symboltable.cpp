#include "symboltable.hpp"
#include <string>
#include <vector>
#include <sstream>
#include <cassert>

SymbolTable::SymbolTable() {
    // Initialize the symbol table
}

/**
 * @brief Constructs SymbolTable object
 * @param cst - The string version of the concrete syntax tree that was
 *          generated in RecursiveDescentParser
 */
SymbolTable::SymbolTable(const string& cst) {
    //cout << cst;

    // makes 2d vector of strings from the cst string
    //
    // outter vector is vector of vectors where each inner vector represents one
    // line from the cst string
    //
    // inner vector has each word from that line
    istringstream iss(cst);
    vector<vector<string>> linesAndWords;
    string line;
    while (getline(iss, line)) {
        istringstream lineStream(line);
        vector<string> words;
        string word;

        while (lineStream >> word) {
            words.push_back(word);
        }

        linesAndWords.push_back(words);
    }

    vector<string> slice;
    // used to keep track of when a new scope is neccesary -- when to scope++
    int leftBraceCounter = 0;
    int scope = 1;
    for (int i = 0; i < linesAndWords.size(); i++) {
        TableEntry tableEntry;
        StateDFA state = linesAndWords[i][0] == "function" ? FUNCTION :
                         linesAndWords[i][0] == "procedure" ? PROCEDURE :
                        (linesAndWords[i][0] == "int" ||
                         linesAndWords[i][0] == "char" ||
                         linesAndWords[i][0] == "bool") ? VARIABLE : OTHER_STATE;

        switch (state) {
            case FUNCTION:
                tableEntry.identifierName = linesAndWords[i][2];
                tableEntry.identifierType = linesAndWords[i][0];
                tableEntry.datatype = linesAndWords[i][1];
                tableEntry.datatypeIsArray = false;
                tableEntry.datatypeArraySize = 0;
                tableEntry.scope = scope;
                table.push_back(tableEntry);
                assert(linesAndWords[i][3] == "(");
                slice.assign(linesAndWords[i].begin() + 4, linesAndWords[i].end());
                parseParams(slice, scope, tableEntry.identifierName);
                //cout << "function";
                break;
            case PROCEDURE:
                tableEntry.identifierName = linesAndWords[i][1];
                tableEntry.identifierType = linesAndWords[i][0];
                tableEntry.datatype = "NOT APPLICABLE";
                tableEntry.datatypeIsArray = false;
                tableEntry.datatypeArraySize = 0;
                tableEntry.scope = scope;
                table.push_back(tableEntry);
                assert(linesAndWords[i][2] == "(");
                //cout << "procedure";
                break;
            case VARIABLE:
                tableEntry.identifierName = linesAndWords[i][1];
                tableEntry.identifierType = "datatype";
                tableEntry.datatype = linesAndWords[i][0];
                tableEntry.scope = leftBraceCounter == 0 ? 0 : scope;

                cout << linesAndWords[i].size() << ": ";
                for (int j = 0; j < linesAndWords[i].size(); j++) {
                    cout << linesAndWords[i][j] << ' ';
                }

                // 1 variable
                if (linesAndWords[i].size() == 3) {
                    tableEntry.datatypeIsArray = false;
                    tableEntry.datatypeArraySize = 0;
                    table.push_back(tableEntry);
                } else if (linesAndWords[i][2] == ",") { // multiple variables
                    tableEntry.datatypeIsArray = false;
                    tableEntry.datatypeArraySize = 0;
                    table.push_back(tableEntry);
                    assert(linesAndWords[i].size() % 2 == 1);
                    for (int j = 3; j < linesAndWords[i].size(); j += 2) {
                        tableEntry.identifierName = linesAndWords[i][j];
                        table.push_back(tableEntry);
                    }
                } else { // array 
                    tableEntry.datatypeIsArray = true;
                    assert(linesAndWords[i][2] == "[");
                    tableEntry.datatypeArraySize = stoi(linesAndWords[i][3]);
                    assert(linesAndWords[i][4] == "]");
                    table.push_back(tableEntry);
                }
                //cout << "\nvariable";
                break;
            case OTHER_STATE:
                if (linesAndWords[i][0] == "{") 
                    leftBraceCounter++;

                if (linesAndWords[i][0] == "}") {
                    leftBraceCounter--;

                    if (leftBraceCounter == 0)
                        scope++;
                } 
                break;
        }

        std::cout << std::endl;
    }
    
    //cout << table.size() << "*****\n";
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
    string currentScope; // To keep track of the current scope
    string currentFunction; // To keep track of the current function being processed
    vector<pair<string, string>> currentParameters; // To store parameters of the current function/procedure

    // Iterate over the tokens
    for (size_t i = 0; i < tokens.size(); ++i) {
        const Token& token = tokens[i];

        // Check for function definitions
        if (token.type == IDENTIFIER && (token.character == "function" || token.character == "procedure")) {
            // Extract function/procedure name and scope
            string name = tokens[i + 2].character;
            string scope = currentScope;

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
            } else {
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
        }
    }
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


//I still dont know if this is a good idea but I give up and am tired
void handleSyntaxErrors(const string& errorMessage, int lineNumber) {
    cerr << "Error on line " << lineNumber << ": " << errorMessage << endl;
}

/**
 * @brief Output operator overload
 * @param os - The output stream operator
 * @param obj - The SymbolTable object to output
 * @returns The modified output stream
 * @remark Outputs symbol table according to project spec
 * 
 *      ex: cout << SymbolTableObj;
 */
ostream& operator << (ostream& os, const SymbolTable& obj) {
    for (const auto& entry : obj.table) {
        os << "IDENTIFIER_NAME: " << entry.identifierName << '\n';
        os << "IDENTIFIER_TYPE: " << entry.identifierType << '\n';
        os << "DATATYPE: " << entry.datatype << '\n';
        os << "DATATYPE_IS_ARRAY: ";
        if (entry.datatypeIsArray) os << "yes\n";
        else os << "no\n";
        os << "DATATYPE_ARRAY_SIZE: " << entry.datatypeArraySize << '\n';
        os << "SCOPE: " << entry.scope << '\n';
        os << '\n';
    }

    for (const auto& entry : obj.paramTable) {
        os << "PARAMETER LIST FOR: " << entry.paramListName << '\n';
        os << "IDENTIFIER_NAME: " << entry.identifierName << '\n';
        os << "DATATYPE: " << entry.datatype << '\n';
        os << "DATATYPE_IS_ARRAY: ";
        if (entry.datatypeIsArray) os << "yes\n";
        else os << "no\n";
        os << "DATATYPE_ARRAY_SIZE: " << entry.datatypeArraySize << '\n';
        os << "SCOPE: " << entry.scope << '\n';
        os << '\n';
    }

    return os;
}

void SymbolTable::parseParams(const vector<string>& params, int scope, 
                                            const string& paramListName) {
    ParamListEntry paramListEntry;
    cout << "\n******\n";
    for (const auto& i : params)
        cout << i << ' ';
    cout << "\n******\n";
    paramListEntry.paramListName = paramListName;
    paramListEntry.identifierName = params[1];
    paramListEntry.datatype = params[0];
    paramListEntry.scope = scope;
    paramTable.push_back(paramListEntry);

    // 1 variable
    if (params.size() == 3) {
        paramListEntry.datatypeIsArray = false;
        paramListEntry.datatypeArraySize = 0;
        paramTable.push_back(paramListEntry);
    } else if (params[2] == ",") { // multiple variables
        paramListEntry.datatypeIsArray = false;
        paramListEntry.datatypeArraySize = 0;
        paramTable.push_back(paramListEntry);
        assert(params.size() % 2 == 1);
        for (int j = 3; j < params.size(); j += 2) {
            paramListEntry.identifierName = params[j];
            paramTable.push_back(paramListEntry);
        }
    } else { // array 
        paramListEntry.datatypeIsArray = true;
        assert(params[2] == "[");
        paramListEntry.datatypeArraySize = stoi(params[3]);
        assert(params[4] == "]");
        paramTable.push_back(paramListEntry);
    }
}
