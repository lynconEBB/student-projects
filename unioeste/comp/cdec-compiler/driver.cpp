#include "driver.h"
#include <iostream>
#include <fstream>
#include <filesystem>

namespace Cd
{

void Driver::init() {
    int a = m_parser.parse();
    m_symbolTable.print();
    std::cout << "Compilação finalizada!" << std::endl;
}

void recursivePrint(Node* node, int tabs, std::ostream& out)
{
    for (int i = 0; i < tabs; i++) {
        if (i == tabs-1) {
            out << " |--";
        } else {
            out << " |  ";
        }
    }

    out << node->name << '\n';

    for (Node* child : node->children) {
        recursivePrint(child, tabs + 1, out);
    }
}

void Driver::printAST(Node* node) 
{
    std::filesystem::path path(m_filename);
    path = path.replace_extension("txt");
    std::string singleFileName = path.filename();
    std::cout << "Gerando arvore sintatica no arquivo: arvores_" << singleFileName << std::endl;
    std::ofstream outfile("arvores_" + singleFileName, std::ios::out);

    outfile << "============ Árvore Sintática ============\n";
    recursivePrint(node, 0, outfile); 
}

}