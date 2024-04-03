 #ifndef SYMBOLTABLE_HPP
 #define SYMBOLTABLE_HPP

// #include <iostream>
// #include <vector>
// #include <unordered_map>
// #include "Tokenization.hpp" // Include the header where Token is defined
// #include "RecursiveDescentParser.hpp"

// using namespace std;

// // Structs for variables, functions, and procedures
// struct Variable {
//     string name;
//     string type;
//     string scope;
//     string datatype;
// };

// struct Function {
//     string name;
//     string returnType;
//     int scope; //Changed from string
//     vector<pair<string, string>> parameters;
//     string datatype;
// };

// struct Procedure {
//     string name;
//     int scope; //Changed from string
//     vector<pair<string, string>> parameters;
//     string datatype;
// };

// // Symbol table class
// class SymbolTable {
// public:
//     SymbolTable();
//     void insertVariable(const Variable& variable);
//     void insertFunction(const Function& function);
//     void insertProcedure(const Procedure& procedure);
//     void populateSymbolTable(LCRS* symbols); // Declaration for populateSymbolTable
//     void print() const;
// private:
//     unordered_map<string, Variable> symbolTableVariables;
//     unordered_map<string, Function> symbolTableFunctions;
//     unordered_map<string, Procedure> symbolTableProcedures;
// };

// // Function to handle syntax errors
// void handleSyntaxErrors(const string& errorMessage, int lineNumber);

// #endif /* SYMBOLTABLE_HPP */

/**
 * @file RecursiveDescentParser.hpp
 * @brief Defines the RecursiveDescentParser class that takes in vector of 
 *        tokens and creates a Left Child Right Sibling (LCRS) binary tree
 *        that represents the Concrete Syntax Tree (CST) 
 * @authors Jacob Franco, Zach Gassner, Haley Joerger, Adam Lyday 
 */

// #ifndef RECURSIVE_DESCENT_PARSER_HPP
// #define RECURSIVE_DESCENT_PARSER_HPP

#include "IgnoreComments.hpp"
#include "Tokenization.hpp"
#include <iostream>
#include <vector>

using namespace std;

/**
 * @enum State
 * @brief Enumerates the different states of the DFA 
 */
enum SymbolState {
    SymbolOTHER,
    SymbolFUNCTION_DECLARATION,
    SymbolVARIABLE_DECLARATION,
    SymbolVARIABLE_ASSIGNMENT,
    SymbolLOOP,
    SymbolCONDITIONAL
};

/**
 * @class LCRS
 * @brief Represents a LCRS binary tree 
 */
class SymbolLCRS {
public:
    /**
     * @brief Constructor
     * @param token - A token from the input vector of tokens 
     */
    SymbolLCRS(const Token& token) : token(token), leftChild(nullptr), rightSibling(nullptr) { }

    /**
     * @brief Breadth-first search function
     * @returns A string with the resulting BFS
     */
    string BFS() const;

private:
    /**
     * @brief The data for a LCRS node 
     */
    Token token;

    /**
     * @brief The LCRS node's LC
     */
    SymbolLCRS* leftChild;

    /**
     * @brief The LCRS node's RS 
     */
    SymbolLCRS* rightSibling;

    /**
     * @brief Returns the DFA state 
     * @param token - The token to get the DFA state for
     */
    SymbolState getStateDFA(Token token);

    /**
     * @brief So RecursiveDescentParser can access LCRS private variables 
     */
    friend class SymbolTable;
};


/**
 * @class RecursiveDescentParser
 * @brief Creates a CST using Recursive Descent Parsing
 */
class SymbolTable {
public:
    /**
     * @brief Constructor
     * @param tokens - A vector of tokens from a C-style program 
     */
    SymbolTable(const vector<Token>& tokens);

    SymbolLCRS* getConcreteSyntaxTree();
    /**
     * @brief Output operator overload
     * @param os - The output stream operator
     * @param obj - The RecursiveDescentParser object to output
     * @returns The modified output stream
     * @remark Outputs CST according to project spec
     * 
     *      ex: cout << RecursiveDescentParserObj;
     */
    friend ostream& operator << (ostream& os, const SymbolTable& obj);

private:
    /**
     * @brief The CST 
     */
    SymbolLCRS* concreteSyntaxTree;
};

#endif