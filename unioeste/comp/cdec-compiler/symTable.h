#ifndef SYMTABLE_H
#define SYMTABLE_H

#include <unordered_map>
#include <string>
#include <vector>
#include "parser.h"
#include <variant>


using Value = std::variant<int,double,char,std::string,std::monostate>;

enum class TokenType {
    UNDEFINED,
    INT,
    REAL,
    CHAR,
    STR,
    ARRAY,
    FUNCTION,
    VOID
};

struct Parameter {
    TokenType type;
    std::string name;
    Value value;
};

struct SymbolInfo {
    std::string name;
    std::string classType;
    TokenType type = TokenType::UNDEFINED;
    std::vector<uint32_t> references;

    Value value; 

    // Valores do Array
    std::vector<Value> arrayValues;
    // Parametros caso seja tipo função
    std::vector<Parameter> parameters;
    // Para retorno de função e tipo do array
    TokenType aditionalType;

    SymbolInfo(const std::string& name, Cd::Parser::symbol_type inClassType, uint32_t firstReference):
            name(name), references({firstReference}), type(TokenType::UNDEFINED), value(std::monostate()) 
            {
                classType = Cd::Parser::symbol_name(inClassType.type_get());
            }

    SymbolInfo(const std::string& name, uint32_t firstReference):
            name(name), references({firstReference}), type(TokenType::UNDEFINED),
            value(std::monostate()), classType("UNDEFINED") {}
};

using SymIterator = std::unordered_map<std::string, SymbolInfo*>::iterator;

namespace Cd
{

inline const std::string typeStr[] = {
    "UNDEFINED", "INT", "REAL",
    "CHAR", "STR", "ARRAY", "FUNCTION", "VOID"
};

std::string typeToStr(TokenType type);

class SymbolTable {
public:
    SymbolTable(Cd::Driver& driver) : m_driver(driver) { }

    SymbolInfo* insert(const std::string& name, Cd::Parser::symbol_type classType);
    SymbolInfo* insert(const std::string& name);
    SymbolInfo* find(const std::string& name);
    void logPrint(SymbolInfo* info, bool firstInsertion);
    void print();

private:
    std::unordered_map<std::string, SymbolInfo*> symbolTable;
    Cd::Driver& m_driver;
};

}

#endif