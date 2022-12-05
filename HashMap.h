// [djb2 Hash Function] - https://theartincode.stanis.me/008-djb2/

#include <iostream>
#include <string>
#include <vector>
#include "Node.h"
#pragma once

using namespace std;

class HashMap
{
    public:
        ~HashMap();
        void insert(std::string title, Game* game);
        Game* getByTitle(std::string title);
        std::vector<std::string> getByGenre(std::string genre);
        std::vector<std::string> getByYear(std::string year);
        std::vector<std::string> getByCategory(std::string category);

    private:
        int buckets = 0;
        int tableSize = 50;
        Node** table = new Node*[50]();

        unsigned long hashFunction(std::string title);
        int reduce(unsigned long hash);
        void checkLoadFactor();
        void reHash(Node** newTable, Node* node);
};

HashMap::~HashMap()
{
    // Delete linked list from each index of array

    for (int i = 0; i < tableSize; i++)
    {
        if (table[i])
        {
            Node* head = table[i];
            Node* next = nullptr;

            while (head != nullptr)
            {
                next = head->getNext();
                delete head;
                head = next;
            }
            head = nullptr;
        }
    }
    delete [] table;
}

unsigned long HashMap::hashFunction(std::string title)
{
    // For each letter in the string, multiply the hash by 33 and add the ascii value of the letter

    unsigned long hash = 5381;

    for (unsigned char letter : title)
    {
        hash = ((hash << 5) + hash) + int(letter); /* hash * 33 + c */
    }
    return hash;
}

int HashMap::reduce(unsigned long hash)
{
    return hash % tableSize;
}

void HashMap::reHash(Node** newTable, Node* node)
{
    // Go through each value in the linked list and re insert into newTable with new index

    unsigned long hash = hashFunction(node->getKey());
    int index = reduce(hash);

    node->setNext(nullptr);

    if (newTable[index]) 
    {
        Node* head = newTable[index];
        Node* temp = head;

        while (temp->getNext() != nullptr)
        {
            temp = temp->getNext();
        }
        temp->setNext(node);
    }
    else
    {
        newTable[index] = node;
    }
}

void HashMap::checkLoadFactor()
{
    // If load factor is > 0.8, double array size and rehash
    float loadFactor = 0.8;
    if (((float) buckets / tableSize) >= loadFactor)
    {
        tableSize *= 2;
        Node** newTable = new Node*[tableSize]();
        for (int i = 0; i < tableSize / 2; i++)
        {
            if (table[i])
            {
                Node* head = table[i];
                Node* temp = head;
                Node* next = nullptr;

                while (temp != nullptr)
                {
                    next = temp->getNext();
                    reHash(newTable, temp);
                    temp = next;
                }
            }
        }
        delete [] table;
        table = newTable;
        newTable = nullptr;
    }
}

void HashMap::insert(std::string title, Game* game)
{
    // Hash and reduce the title
    unsigned long hash = hashFunction(title);
    int index = reduce(hash);
    Node* node = new Node(title, game);

    // If the table's value at index is empty, insert directly
    // Otherwise, add to end of linked list
    
    if (table[index]) 
    {
        Node* head = table[index];
        Node* temp = head;
        while (temp->getNext() != nullptr)
        {
            temp = temp->getNext();
        }
        temp->setNext(node);
    }
    else
    {
        table[index] = node;
    }

    buckets += 1;
    checkLoadFactor();
}

Game* HashMap::getByTitle(std::string title)
{
    unsigned long hash = hashFunction(title);
    int index = reduce(hash);
    Game* game = nullptr;

    if (table[index]) 
    {
        Node* head = table[index];
        Node* temp = head;
        while (temp != nullptr)
        {
            if (temp->getKey() == title)
            {
                game = temp->getValue();
                break;
            }
            temp = temp->getNext();
        }
        if (temp == nullptr)
        {
            std::cout << "Game not found" << endl;
        }
    }
    else
    {
        std::cout << "Game not found" << endl;
    }

    return game;
}

std::vector<std::string> HashMap::getByGenre(std::string genre)
{
    std::vector<std::string> games;

    for (int i = 0; i < tableSize; i++)
    {
        Node* head = table[i];
        Node* temp = head;
        while (temp != nullptr)
        {
            if (temp->getValue()->genre == genre)
            {
                games.push_back(temp->getKey());
            }
            temp = temp->getNext();
        }
    }

    return games;
}

std::vector<std::string> HashMap::getByYear(std::string year)
{
    std::vector<std::string> games;

    for (int i = 0; i < tableSize; i++)
    {
        Node* head = table[i];
        Node* temp = head;
        while (temp != nullptr)
        {
            if (temp->getValue()->releaseYear == year)
            {
                games.push_back(temp->getKey());
            }
            temp = temp->getNext();
        }
    }

    return games;
}

std::vector<std::string> HashMap::getByCategory(std::string category)
{
    std::vector<std::string> games;

    for (int i = 0; i < tableSize; i++)
    {
        Node* head = table[i];
        Node* temp = head;
        while (temp != nullptr)
        {
            if (category == "Single" && temp->getValue()->isSingle)
            {
                games.push_back(temp->getKey());
            }
            if (category == "Multi" && temp->getValue()->isMulti)
            {
                games.push_back(temp->getKey());
            }
            temp = temp->getNext();
        }
    }

    return games;
}