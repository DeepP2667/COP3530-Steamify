#include <string>
#include "Game.h"
#pragma once

using namespace std;

class Node
{
    public:
        Node(std::string key, Game* game);
        std::string getKey();
        Game* getValue();
        void setNext(Node* node);
        Node* getNext();

    private:
        std::string key;
        Game* value = nullptr;
        Node* next = nullptr;
};

Node::Node(std::string key, Game* game)
{
    this->key = key;
    this->value = game;
    next = nullptr;
}

std::string Node::getKey()
{
    return key;
}

Game* Node::getValue()
{
    return value;
}

void Node::setNext(Node* node)
{
    next = node;
}

Node* Node::getNext()
{
    return next;
}