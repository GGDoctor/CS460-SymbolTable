#include "symboltable.hpp"

// SymbolTable::SymbolTable() {
//     // Initialize the symbol table
// }

// void SymbolTable::insertVariable(const Variable& variable) {
//     symbolTableVariables[variable.name] = variable;
// }

// void SymbolTable::insertFunction(const Function& function) {
//     symbolTableFunctions[function.name] = function;
// }

// void SymbolTable::insertProcedure(const Procedure& procedure) {
//     symbolTableProcedures[procedure.name] = procedure;
// }

// void SymbolTable::populateSymbolTable(LCRS* symbols) {
//     /*
//     *   Changed the type of scope in .h and here to int so we can track it easier
//     */
//    cout << symbols->BFS();

//     /*
//     int currentScope; // To keep track of the current scope
//     string currentFunction; // To keep track of the current function being processed
//     vector<pair<string, string>> currentParameters; // To store parameters of the current function/procedure
    
//     // Iterate over the tokens
//     for (size_t i = 0; i < tokens.size(); ++i) {
//         const Token& token = tokens[i];

//         // Note that the token.type is not actually IDENTIFIER it is 2, refer to Tokenixation.hpp
//         // cout<< token.type << " " << token.character << " " << isdigit(token.type) << endl;

//         int scope = currentScope;
       
//         // Check for function definitions
//         if (token.type == IDENTIFIER && (token.character == "function" || token.character == "procedure")) {
//             // Extract function/procedure name and scope
//             string name = tokens[i + 2].character;
//             // string scope = currentScope;

//             // Check if it's a function or procedure
//             if (token.character == "function") {
//                 // Extract return type
//                 string returnType = tokens[i + 1].character;

//                 // Insert da function into the symbol table
//                 Function function;
//                 function.name = name;
//                 function.returnType = returnType;
//                 function.scope = scope;
//                 function.parameters = currentParameters;
//                 insertFunction(function);

//                 // Update da current function and clear parameters
//                 currentFunction = name;
//                 currentParameters.clear();
//             } 
//             else if (token.character == "procedure") {
//                 // Insert da procedure into the symbol table
//                 Procedure procedure;
//                 procedure.name = name;
//                 procedure.scope = scope;
//                 procedure.parameters = currentParameters;
//                 insertProcedure(procedure);

//                 // Update da current function and clear parameters
//                 currentFunction = name;
//                 currentParameters.clear();
//             }
//             scope += 1;
//         }
//     }
//     */
// }

// void SymbolTable::print() const {




//     // cout << "Symbol Table:" << endl << endl;
//     // // Print variables
//     // for (const auto& entry : symbolTableVariables) {
//     //     const Variable& variable = entry.second;
//     //     cout << "IDENTIFIER_NAME: " << variable.name << endl;
//     //     cout << "IDENTIFIER_TYPE: variable" << endl;
//     //     cout << "DATATYPE: " << variable.type << endl;
//     //     cout << "DATATYPE_IS_ARRAY: no" << endl;
//     //     cout << "DATATYPE_ARRAY_SIZE: 0" << endl;
//     //     cout << "SCOPE: " << variable.scope << endl;
//     //     cout << endl;
//     // }

//     // // Print functions
//     // for (const auto& entry : symbolTableFunctions) {
//     //     const Function& function = entry.second;
//     //     cout << "IDENTIFIER_NAME: " << function.name << endl;
//     //     cout << "IDENTIFIER_TYPE: function" << endl;
//     //     cout << "DATATYPE: " << function.returnType << endl;
//     //     cout << "DATATYPE_IS_ARRAY: no" << endl;
//     //     cout << "DATATYPE_ARRAY_SIZE: 0" << endl;
//     //     cout << "SCOPE: " << function.scope << endl;
//     //     //Need to fix this. Does not have to be here till (int n) or whatever
//     //     // cout << "PARAMETER LIST FOR: " << function.name << endl;
//     //     for (const auto& param : function.parameters) {
//     //         cout << "IDENTIFIER_NAME: " << param.first << endl;
//     //         cout << "DATATYPE: " << param.second << endl;
//     //         cout << "DATATYPE_IS_ARRAY: no" << endl;
//     //         cout << "DATATYPE_ARRAY_SIZE: 0" << endl;
//     //         cout << "SCOPE: " << function.scope << endl;
//     //     }
//     //     cout << endl;
//     // }

//     // // Print procedures
//     // for (const auto& entry : symbolTableProcedures) {
//     //     const Procedure& procedure = entry.second;
//     //     cout << "IDENTIFIER_NAME: " << procedure.name << endl;
//     //     cout << "IDENTIFIER_TYPE: procedure" << endl;
//     //     cout << "DATATYPE: NOT APPLICABLE" << endl;
//     //     cout << "DATATYPE_IS_ARRAY: no" << endl;
//     //     cout << "DATATYPE_ARRAY_SIZE: 0" << endl;
//     //     cout << "SCOPE: " << procedure.scope << endl;
//     //     //Need to fix this. Does not have to be here till (int n) or whatever
//     //     // cout << "PARAMETER LIST FOR: " << procedure.name << endl;
//     //     for (const auto& param : procedure.parameters) {
//     //         cout << "IDENTIFIER_NAME: " << param.first << endl;
//     //         cout << "DATATYPE: " << param.second << endl;
//     //         cout << "DATATYPE_IS_ARRAY: no" << endl;
//     //         cout << "DATATYPE_ARRAY_SIZE: 0" << endl; // Assuming parameters are not arrays
//     //         cout << "SCOPE: " << procedure.scope << endl;
//     //     }
//     //     cout << endl;
//     // }
// }


// //I still dont know if this is a good idea but I give up and am tired
// void handleSyntaxErrors(const string& errorMessage, int lineNumber) {
//     cerr << "Error on line " << lineNumber << ": " << errorMessage << endl;
// }


/**
 * @file RecursiveDescentParser.cpp
 * @brief Implementation file for the RecursiveDescentParser class
 * @authors Jacob Franco, Zach Gassner, Haley Joerger, Adam Lyday
 */

//#include "RecursiveDescentParser.hpp"
#include <queue>

/**
 * @param token - A token object
 * @returns The actual character(s) of the token
 */
auto symbolToTokenCharacter(Token token) {
    return token.character;
}

/**
 * @brief Returns string version of token type
 * @param token - A Token object
 * @returns A string of the token type instead of 0, 1, 2, ...
 */
auto symbolToTokenType(Token token) {
    switch (token.type) {
        case CHAR:
            return "CHAR";

        case VOID:
            return "VOID";

        case IDENTIFIER:
            return "IDENTIFIER";

        case INTEGER:
            return "INTEGER";

        case STRING:
            return "STRING";

        case LEFT_PARENTHESIS:
            return "LEFT_PARENTHESIS";

        case RIGHT_PARENTHESIS:
            return "RIGHT_PARENTHESIS";

        case LEFT_BRACKET:
            return "LEFT_BRACKET";

        case RIGHT_BRACKET:
            return "RIGHT_BRACKET";

        case LEFT_BRACE:
            return "LEFT_BRACE";

        case RIGHT_BRACE:
            return "RIGHT_BRACE";

        case DOUBLE_QUOTE:
            return "DOUBLE_QUOTE";

        case SINGLE_QUOTE:
            return "SINGLE_QUOTE";

        case SEMICOLON:
            return "SEMICOLON";

        case COMMA:
            return "COMMA";

        case ASSIGNMENT:
            return "ASSIGNMENT";

        case PLUS:
            return "PLUS";

        case MINUS:
            return "MINUS";

        case DIVIDE:
            return "DIVIDE";

        case ASTERISK:
            return "ASTERISK";

        case MODULO:
            return "MODULO";

        case CARAT:
            return "CARAT";

        case LT:
            return "LT";

        case GT:
            return "GT";

        case LT_EQUAL:
            return "LT_EQUAL";

        case GT_EQUAL:
            return "GT_EQUAL";
    
        case BOOLEAN_AND_OPERATOR:
            return "BOOLEAN_AND_OPERATOR";

        case BOOLEAN_OR_OPERATOR:
            return "BOOLEAN_OR_OPERATOR";

        case BOOLEAN_NOT_OPERATOR:
            return "BOOLEAN_NOT_OPERATOR";

        case BOOLEAN_EQUAL:
            return "BOOLEAN_EQUAL";

        case BOOLEAN_NOT_EQUAL:
            return "BOOLEAN_NOT_EQUAL";

        case BOOLEAN_TRUE:
            return "BOOLEAN_TRUE";

        case BOOLEAN_FALSE:
            return "BOOLEAN_FALSE";

    }
}

/**
 * @brief Breadth-first search function
 * @returns A string with the resulting BFS
 */
string SymbolLCRS::BFS() const {
    /**
     * @remark pair a SymbolLCRS node and its level in the tree 
     */
    queue<std::pair<const SymbolLCRS*, int>> q;
    q.push({this, 0});
    string result = "";
    int currentLevel = -1;

    while (!q.empty()) {
        const SymbolLCRS* current = q.front().first;
        int level = q.front().second;
        q.pop();

        if (level != currentLevel) {
            if (currentLevel != -1) 
                result += '\n';
            
            currentLevel = level;
        }
        
        // Skip printing for parentheses and braces
        // if (current->token.type != LEFT_PARENTHESIS && 
        //     current->token.type != RIGHT_PARENTHESIS && 
        //     current->token.type != LEFT_BRACE && 
        //     current->token.type != RIGHT_BRACE &&
        //     current->token.type != SEMICOLON) {
        //     result += symbolToTokenCharacter(current->token) + ' ';
        // }

        result += symbolToTokenCharacter(current->token) + ' ';

        if (current->leftChild)
            q.push({current->leftChild, level + 1});
        if (current->rightSibling)
            q.push({current->rightSibling, level});

    }

    return result += '\n';
}

/**
 * @brief Returns the DFA state 
 * @param token - The token to get the DFA state for
 */
SymbolState symbolGetStateDFA(Token token) {
    if (token.type == IDENTIFIER) {
        if (token.character == "function" || token.character == "procedure") 
            return SymbolFUNCTION_DECLARATION;
        
        if (token.character == "int" || token.character == "string" ||
            token.character == "char" || token.character == "bool")
            return SymbolVARIABLE_DECLARATION;

        if (token.character == "if")
            return SymbolCONDITIONAL;

        if (token.character == "for" || token.character == "while")
            return SymbolLOOP;

        if (token.character == "=")
            return SymbolVARIABLE_ASSIGNMENT;
    }
        
    return SymbolOTHER;
}

/**
 * @brief Constructor
 * @param tokens - A vector of tokens from a C-style program 
 */
SymbolTable::SymbolTable(const vector<Token>& tokens) {
    /**
     * used to keep track of left parenthesis in the cases of math/bool expression 
     */
    int leftParenCounter = 0;

    SymbolLCRS* lcrs = tokens.size() > 0 ? new SymbolLCRS(tokens[0]) : nullptr;
    SymbolLCRS* temp = lcrs;
    SymbolState state = symbolGetStateDFA(tokens[0]);

    for (int i = 1; i < tokens.size(); i++) {
        switch (state) {
            case SymbolOTHER:
                if (tokens[i - 1].type == SEMICOLON || 
                    tokens[i - 1].type == RIGHT_BRACE ||
                    tokens[i - 1].type == LEFT_BRACE ||
                    tokens[i - 1].character == "else") {
                    temp->leftChild = new SymbolLCRS(tokens[i]);
                    temp = temp->leftChild;
                    state = symbolGetStateDFA(tokens[i]);
                } else {
                    temp->rightSibling = new SymbolLCRS(tokens[i]);
                    temp = temp->rightSibling;
                }
                break;

            case SymbolFUNCTION_DECLARATION:
                if (tokens[i - 1].type == RIGHT_PARENTHESIS) {
                    temp->leftChild = new SymbolLCRS(tokens[i]);
                    temp = temp->leftChild;
                    state = symbolGetStateDFA(tokens[i]);
                } else {
                    temp->rightSibling = new SymbolLCRS(tokens[i]);
                    temp = temp->rightSibling;
                }
                break;

            case SymbolVARIABLE_DECLARATION:
                if (tokens[i - 1].type == SEMICOLON) {
                    temp->leftChild = new SymbolLCRS(tokens[i]);
                    temp = temp->leftChild;
                    state = symbolGetStateDFA(tokens[i]);
                } else {
                    temp->rightSibling = new SymbolLCRS(tokens[i]);
                    temp = temp->rightSibling;
                }
                break;

            case SymbolVARIABLE_ASSIGNMENT:
                if (tokens[i - 1].type == SEMICOLON) {
                    temp->leftChild = new SymbolLCRS(tokens[i]);
                    temp = temp->leftChild;
                    state = symbolGetStateDFA(tokens[i]);
                } else {
                    temp->rightSibling = new SymbolLCRS(tokens[i]);
                    temp = temp->rightSibling;
                }
                break;

            case SymbolLOOP:
                if (tokens[i - 1].type == RIGHT_PARENTHESIS && leftParenCounter == 0) {
                    temp->leftChild = new SymbolLCRS(tokens[i]);
                    temp = temp->leftChild;
                    state = symbolGetStateDFA(tokens[i]);
                } else {
                    if (tokens[i].type == RIGHT_PARENTHESIS) 
                        leftParenCounter--;

                    if (tokens[i].type == LEFT_PARENTHESIS) 
                        leftParenCounter++;
            
                    temp->rightSibling = new SymbolLCRS(tokens[i]);
                    temp = temp->rightSibling;
                }
                break;

            case SymbolCONDITIONAL:
                if (tokens[i - 1].type == RIGHT_PARENTHESIS && leftParenCounter == 0) {
                    temp->leftChild = new SymbolLCRS(tokens[i]);
                    temp = temp->leftChild;
                    state = symbolGetStateDFA(tokens[i]);
                } else {
                    if (tokens[i].type == RIGHT_PARENTHESIS) 
                        leftParenCounter--;

                    if (tokens[i].type == LEFT_PARENTHESIS) 
                        leftParenCounter++;
            
                    temp->rightSibling = new SymbolLCRS(tokens[i]);
                    temp = temp->rightSibling;
                }
                break;

        }
    }

    concreteSyntaxTree = lcrs;
}

/**
 * @brief Output operator overload
 * @param os - The output stream operator
 * @param obj - The RecursiveDescentParser object to output
 * @returns The modified output stream
 * @remark Outputs CST according to project spec
 * 
 *      ex: cout << RecursiveDescentParserObj;
 */
ostream& operator << (ostream& os, const SymbolTable& obj) {
    os << obj.concreteSyntaxTree->BFS();
    return os;
}

SymbolLCRS* SymbolTable::getConcreteSyntaxTree(){
    return concreteSyntaxTree;
}