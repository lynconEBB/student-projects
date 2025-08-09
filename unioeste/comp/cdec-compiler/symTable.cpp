#include "symTable.h"
#include "driver.h"
#include <iostream>
#include <iomanip>
#include <utility>

namespace Cd 
{
    std::string typeToStr(TokenType type)
    {
        return typeStr[static_cast<unsigned int>(type)];
    }

    void SymbolTable::logPrint(SymbolInfo* info, bool firstInsertion){
        if (firstInsertion) {
            std::cout << "[Tabela de Simbolos] Encontrado cadeia: " << info->name << 
            " da classe: " << info->classType <<
            " na linha: " << m_driver.lineNumber << '\n';
        } else {
            std::cout << "[Tabela de Simbolos] Nova referencia da cadeia: " << info->name << 
            " da classe: " << info->classType <<
            " encontrada na linha: " << m_driver.lineNumber << '\n';
        }
    }
    void SymbolTable::print()
    {
        std::cout << '\n';
        std::cout << std::left << std::setw(30) << "Cadeia" << 
                    std::setw(10) << "Classe" << 
                    std::setw(15) << "Tipo" << std::setw(22) << "Valor" <<
                    "Referencia Linha" << '\n' ;

        for (auto it = symbolTable.begin(); it != symbolTable.end(); it++) {
            SymbolInfo* info = it->second;

            std::cout << std::setw(30) << info->name; 
            std::cout << std::setw(10) << info->classType;
            std::cout << std::setw(15) << typeStr[static_cast<unsigned int>(info->type)];
            std::cout << std::setw(22);

            switch(info->value.index()) {
                case 0: {
                    std::cout << std::get<int>(info->value);
                } break;
                case 1: {
                    std::cout << std::get<double>(info->value);
                } break;
                case 2: {
                    std::cout << std::get<char>(info->value);
                } break;
                case 3: {
                    std::cout << std::get<std::string>(info->value);
                } break;
                case 4: {
                    std::cout << "UNDEFINED";
                } break;
            }

            for (uint32_t line: info->references) {
                std::cout << line << ' ';
            }
            std::cout << '\n';
        } 
    }

    SymbolInfo* SymbolTable::insert(const std::string& name, Cd::Parser::symbol_type classType)
    {
        SymIterator result = symbolTable.find(name);
        SymbolInfo* info;

        if (result != symbolTable.end()) {
            info = result->second;
            info->references.push_back(m_driver.lineNumber);
            logPrint(info,false);
        } else {
            info = new SymbolInfo(name, classType, m_driver.lineNumber);
            symbolTable.insert(std::make_pair(name, info));
            logPrint(info,true);
        }

        return info;
    }

    SymbolInfo* SymbolTable::insert(const std::string& name)
    {
        SymIterator result = symbolTable.find(name);
        SymbolInfo* info;

        if (result != symbolTable.end()) {
            info = result->second;
            info->references.push_back(m_driver.lineNumber);
        } else {
            info = new SymbolInfo(name, m_driver.lineNumber);
            symbolTable.insert(std::make_pair(name, info));
        }

        return info;
    }

    SymbolInfo* SymbolTable::find(const std::string& name)
    {
       SymIterator result = symbolTable.find(name); 
       return result->second;
    }

}