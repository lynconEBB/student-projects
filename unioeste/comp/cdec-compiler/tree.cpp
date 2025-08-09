#include "tree.h"
#include <iostream>

void Node::addChild(Node* newChild)
{
    children.push_back(newChild);
}

Node* Node::getChildByIndex(int index) 
{
    return children[index];
}

void recursiveGet(Node* node, const std::string& search, std::vector<Node*>& list ) 
{
    if (node->name == search ) {
        list.push_back(node);
    }
    for (Node* child : node->children) {
        recursiveGet(child, search, list);
    }
}

std::vector<Node*> Node::getChildsByName(std::string search)
{
    std::vector<Node*> list;
    recursiveGet(this, search, list);
    return list;
}
