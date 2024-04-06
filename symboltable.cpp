#include "symboltable.hpp"
#include <string>
#include <sstream>
#include <cassert>

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
    int lineNumber = 1;

    while (getline(iss, line)) {
        istringstream lineStream(line);
        vector<string> words;
        string word;

        while (lineStream >> word) {
            words.push_back(word);
        }

        linesAndWords.push_back(words);
        lineNumber++; 
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
                slice.assign(linesAndWords[i].begin() + 3, linesAndWords[i].end());
                parseParams(slice, scope, tableEntry.identifierName);
                //cout << "procedure";
                break;
            case VARIABLE:
                tableEntry.identifierType = "datatype"; 
                tableEntry.datatype = linesAndWords[i][0];
                tableEntry.scope = leftBraceCounter == 0 ? 0 : scope;
            
                for ( int j = 1; j < linesAndWords[i].size(); ) {
                    if (linesAndWords[i][j] == ";") break;
                    tableEntry.identifierName = linesAndWords[i][j];
                    tableEntry.datatypeIsArray = false;
                    tableEntry.datatypeArraySize = 0;

                    // array
                    if (linesAndWords[i][j + 1] == "[") {
                        tableEntry.datatypeIsArray = true;
                        tableEntry.datatypeArraySize = stoi(linesAndWords[i][j + 2]);
                        table.push_back(tableEntry);
                        j += 5;
                    } else {
                        table.push_back(tableEntry);
                        j += 2;
                    }
                }

                /*
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
                } */
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
    }
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
    ParamListEntry previous;

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
        if(previous.paramListName != entry.paramListName){
            os << "PARAMETER LIST FOR: " << entry.paramListName << '\n';
            previous=entry;
        }
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

void SymbolTable::parseParams(const vector<string>& params, int scope, const string& paramListName) {
    if (params[0] == "void") return;
    ParamListEntry paramListEntry;
    paramListEntry.paramListName = paramListName;
    paramListEntry.scope = scope;

    for ( int j = 0; j < params.size(); ) {
        if (params[j] == ")") break;
        paramListEntry.identifierName = params[j + 1];
        paramListEntry.datatype = params[j];
        paramListEntry.datatypeIsArray = false;
        paramListEntry.datatypeArraySize = 0;

        // array
        if (params[j + 2] == "[") {
            paramListEntry.datatypeIsArray = true;
            paramListEntry.datatypeArraySize = stoi(params[j + 3]);
            paramTable.push_back(paramListEntry);
            j += 6;
        } else { //regular variable
            paramTable.push_back(paramListEntry);
            j += 3;
        }
    }

    /*
    // Loop through the parameters
    for (int i = 0; i < params.size(); ++i) {
        // Skip commas
        if (params[i] == ",")
            continue;

        // Skip the '[' character for arrays
        if (params[i] == "[") {
            // The array size is the next parameter
            paramListEntry.datatypeArraySize = stoi(params[i + 1]);
            continue;
        }

        // Skip the ']' character for arrays
        if (params[i] == "]")
            continue;

        // Determine if the parameter is a datatype or identifier
        if (params[i + 1] == "," || params[i + 1] == "[" || params[i + 1] == ")") {
            // Parameter is an identifier
            paramListEntry.identifierName = params[i];
            paramTable.push_back(paramListEntry);
        } else {
            // Parameter is a datatype
            paramListEntry.datatype = params[i];
        }
    }
    */
}

