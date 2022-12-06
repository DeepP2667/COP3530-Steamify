// [djb2 Hash Function] - https://theartincode.stanis.me/008-djb2/
// Hash Maps lecture slides
// Seperate chaining lecture slides

#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "HashNode.h"

using namespace std;

class HashMap
{
    public:
        ~HashMap();
        void insert(std::string title, Game* game);
        void printAll();
        void getByTitle(std::string title);
        void getByGenre(std::string genre);
        void getByRelease(std::string release);
        void getByCategory(std::string category);

    private:
        int buckets = 0;
        int tableSize = 50;
        HashNode** table = new HashNode*[50]();

        unsigned long hashFunction(std::string title);
        int reduce(unsigned long hash);
        void checkLoadFactor();
        void reHash(HashNode** newTable, HashNode* node);
};

HashMap::~HashMap()
{
    // Delete linked list from each index of array

    for (int i = 0; i < tableSize; i++)
    {
        if (table[i])
        {
            HashNode* head = table[i];
            HashNode* next = nullptr;

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

void HashMap::reHash(HashNode** newTable, HashNode* node)
{
    // Go through each value in the linked list and re insert into newTable with new index

    unsigned long hash = hashFunction(node->getKey());
    int index = reduce(hash);

    node->setNext(nullptr);

    if (newTable[index]) 
    {
        HashNode* head = newTable[index];
        HashNode* temp = head;

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
        HashNode** newTable = new HashNode*[tableSize]();
        for (int i = 0; i < tableSize / 2; i++)
        {
            if (table[i])
            {
                HashNode* head = table[i];
                HashNode* temp = head;
                HashNode* next = nullptr;

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
    HashNode* node = new HashNode(title, game);

    // If the table's value at index is empty, insert directly
    // Otherwise, add to end of linked list
    if (table[index]) 
    {
        HashNode* head = table[index];
        HashNode* temp = head;

        if (temp->getKey() == title)
        {
            return;
        }

        while (temp->getNext() != nullptr)
        {
            temp = temp->getNext();
            if (temp->getKey() == title)
            {
                return;
            }
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

void HashMap::printAll()
{
    int printAmount = tableSize;
    int printedGames = 0;

    int index = 0;

    while (printedGames < printAmount)
    {
        if (table[index])
        {
            HashNode* head = table[index];
            while (head != nullptr)
            {
                head->getValue()->PrintInfo();
                head = head->getNext();
                printedGames++;
                if (printedGames > printAmount)
                {
                    break;
                }
            }
        }
        index++;
    }
}

void HashMap::getByTitle(std::string title)
{
    unsigned long hash = hashFunction(title);
    int index = reduce(hash);
    Game* game = nullptr;

    if (table[index])
    {
        HashNode* head = table[index];
        HashNode* temp = head;
        while (temp != nullptr)
        {
            if (temp->getKey() == title)
            {
                game = temp->getValue();
                game->PrintInfo();
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
}

void HashMap::getByGenre(std::string genre)
{
    for (int i = 0; i < tableSize; i++)
    {
        HashNode* head = table[i];
        HashNode* temp = head;
        while (temp != nullptr)
        {
            if (temp->getValue()->GetGenre() == genre)
            {
                temp->getValue()->PrintInfo();
            }
            temp = temp->getNext();
        }
    }
}

void HashMap::getByRelease(std::string release)
{
    for (int i = 0; i < tableSize; i++)
    {
        HashNode* head = table[i];
        HashNode* temp = head;
        while (temp != nullptr)
        {
            if (temp->getValue()->GetYear() == release)
            {
                temp->getValue()->PrintInfo();
            }
            temp = temp->getNext();
        }
    }
}

void HashMap::getByCategory(std::string category)
{
    for (int i = 0; i < tableSize; i++)
    {
        HashNode* head = table[i];
        HashNode* temp = head;
        while (temp != nullptr)
        {
            if (category == "Singleplayer" && temp->getValue()->IsSingle())
            {
                temp->getValue()->PrintInfo();
            }
            if (category == "Multiplayer" && temp->getValue()->IsMulti())
            {
                temp->getValue()->PrintInfo();
            }
            temp = temp->getNext();
        }
    }
}