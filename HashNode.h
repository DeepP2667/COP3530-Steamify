#include <string>
#include "Game.h"
#pragma once

using namespace std;

class HashNode
{
    public:
        HashNode(std::string key, Game* game);
        std::string getKey();
        Game* getValue();
        void setNext(HashNode* node);
        HashNode* getNext();

    private:
        std::string key;
        Game* value = nullptr;
        HashNode* next = nullptr;
};

HashNode::HashNode(std::string key, Game* game)
{
    this->key = key;
    this->value = game;
    next = nullptr;
}

std::string HashNode::getKey()
{
    return key;
}

Game* HashNode::getValue()
{
    return value;
}

void HashNode::setNext(HashNode* node)
{
    next = node;
}

HashNode* HashNode::getNext()
{
    return next;
}