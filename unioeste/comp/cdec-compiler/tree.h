#ifndef TREE_H
#define TREE_H
#include <vector>
#include <variant>
#include <string>

enum class TokenType;

class Node
{
public:
    Node() {}
    Node(std::string name): name(name) {}
    Node(std::string name, TokenType type ) : name(name), type(type) {}
    Node(std::string name, TokenType type, std::variant<int,double,char,std::string, std::monostate> value)
        : name(name), type(type), value(value) {}

    void addChild(Node* newChild);
    Node* getChildByIndex(int index);
    std::vector<Node*> getChildsByName(std::string search);

public:
    std::variant<int, double, char, std::string, std::monostate> value;
    std::string name;
    TokenType type;
    struct SymbolInfo* symbolRef;
    std::vector<Node*> children;
};

#endif