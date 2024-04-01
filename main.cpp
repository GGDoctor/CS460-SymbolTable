#include "IgnoreComments.hpp"
#include "Tokenization.hpp"
#include "RecursiveDescentParser.hpp"
#include "symboltable.hpp" // Include the symbol table header
#include <iostream>
#include <sstream>

using namespace std;

int main(int argc, char *argv[]) {
    if (argc != 2 ) {
        cerr << "Error! There is not a correct number of command line arguments.\n";
        return 1;
    }

    string fileName = argv[1];
    IgnoreComments ignoreComments(fileName);
    stringstream ss;
    ss << ignoreComments;
    Tokenization tokenization(ss.str());
    vector<Token> tokens = tokenization.getTokens();
    RecursiveDescentParser recursiveDescentParser(tokens);

    // Get identifiers from the parser
    vector<Identifier> identifiers = recursiveDescentParser.getIdentifiers();

    // Insert identifiers into the symbol table
    SymbolTable symbolTable;
    for (const auto& identifier : identifiers) {
        symbolTable.insertIdentifier(identifier);
    }

    // Print the symbol table
    symbolTable.print();

    return 0;
}
