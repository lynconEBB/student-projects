#ifndef DRIVER_H
#define DRIVER_H

#include "scanner.h"
#include "parser.h"
#include "symTable.h"
#include <fstream>
#include "tree.h"

namespace Cd {

class Driver {

public:
    Driver(std::ifstream& inputStream, const std::string& filename): 
        m_filename(filename), m_scanner(*this, inputStream), m_parser(m_scanner, *this), m_symbolTable(*this) {}
    void init();
    void printAST(Node* node);
public:
    int lineNumber = 1;
    SymbolTable m_symbolTable;
    std::string m_filename;
    bool declaring = true;

private:
    Scanner m_scanner;
    Parser m_parser;
};

}

#endif