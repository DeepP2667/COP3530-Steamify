#pragma once
#include <iostream>
#include <string>
#include "Game.h"
using namespace std;

//AVL TreeNode lecture 4 slide 26
//AVL Project Breakdown Session
class Node {
    Game videoGame;
public:
    int balanceFactor;
    bool isBalanced;
    bool red = true;
    Node* parent;
    Node* left;
    Node* right;
    Node() : videoGame(Game()), balanceFactor(0), isBalanced(true),parent(nullptr), left(nullptr), right(nullptr) {}
    Node(string t, string g, bool s, bool m, string r) : videoGame(Game(t, g, s, m, r)), balanceFactor(0), isBalanced(true), parent(nullptr), red(true), left(nullptr), right(nullptr) {}
    Node(Node* p, string t, string g, bool s, bool m, string r) : videoGame(Game(t, g, s, m, r)), balanceFactor(0), isBalanced(true), parent(p), left(nullptr), right(nullptr) {}
    Game GetGame() { return videoGame; }
    void PrintColor() {
        if (red)
            cout << "Red" << endl;
        else
            cout << "Black" << endl;
    }
    void PrintInfo() {
        PrintColor();
        videoGame.PrintInfo();
    }
    int NumChildren() {
        int n = 0;
        if (left)
            n++;
        if (right)
            n++;
        return n;
    }
};

class RBTree {
    Node* InsertHelp(Node* p, Node* node, string title, string genre, bool single, bool multi, string release) {
        if (node == nullptr) {
            parentInsert = p;
            return new Node(p, title, genre, single, multi, release);
        }
        else if (title > node->GetGame().GetTitle())
            node->right = InsertHelp(node, node->right, title, genre, single, multi, release);
        else if (title < node->GetGame().GetTitle())
            node->left = InsertHelp(node, node->left, title, genre, single, multi, release);
        return node;
    }
    Node* GetGrandParent(Node* node) {
        return node->parent->parent;
    }
    Node* GetUncle(Node* node){
        if (GetGrandParent(node) != nullptr) {
            Node* gp = GetGrandParent(node);
            if (gp->left == node->parent)
                return gp->right;
            else
                return gp->left;
        }
        return nullptr;
    }

    void TitleHelper(Node* head, string t) {
        if (head == nullptr)
            cout << "";
        else {
            if (head->GetGame().GetTitle() == t)
                head->GetGame().PrintInfo();
            TitleHelper(head->right, t);
            TitleHelper(head->left, t);
        }
    }
    void GenreHelper(Node* head, string g) {
        if (head == nullptr)
            cout << "";
        else {
            if (head->GetGame().GetGenre() == g)
                head->GetGame().PrintInfo();
            GenreHelper(head->right, g);
            GenreHelper(head->left, g);
        }
    }
    void SingleMultiHelper(Node* head, bool s, bool m) {
        if (head == nullptr)
            cout << "";
        else {
            if (head->GetGame().IsSingle() == s && head->GetGame().IsMulti() == m)
                head->GetGame().PrintInfo();
            SingleMultiHelper(head->right, s, m);
            SingleMultiHelper(head->left, s, m);
        }
    }
    void ReleaseHelper(Node* head, string r){
        if (head == nullptr)
            cout << "";
        else {
            if (head->GetGame().GetYear() == r)
                head->GetGame().PrintInfo();
            ReleaseHelper(head->right, r);
            ReleaseHelper(head->left, r);
        }
    }
    void PrintInOrderHelper(Node* head) {
        if (head == nullptr)
            cout << "";
        else {
            PrintInOrderHelper(head->left);
            head->GetGame().PrintInfo();
            PrintInOrderHelper(head->right);
        }
    }
    void RightRotation(Node* node) {
        bool right = false;
        Node* gp = node->parent;
        if (gp !=  nullptr && node->parent->right == node)
            right = true;
        Node* temp = node->left;
        node->left = temp->right;
        if (node->left != nullptr)
            node->left->parent = node;
        temp->right = node;
        temp->parent = node->parent;
        node->parent = temp;
        if (gp != nullptr) {
            if (right)
                temp->parent->right = temp;
            else
                temp->parent->left = temp;
        }
        else if (temp->parent == nullptr)
            root = temp;
    }
    void LeftRotation(Node* node) {
        bool right = false;
        Node* gp = node->parent;
        if (gp != nullptr && node->parent->right == node)
            right = true;
        Node* temp = node->right;
        node->right = temp->left;
        if (node->right != nullptr)
            node->right->parent = node;
        temp->left = node;
        temp->parent = node->parent;
        node->parent = temp;
        if (gp != nullptr) {
            if (right)
                temp->parent->right = temp;
            else
                temp->parent->left = temp;
        }
        else if (temp->parent == nullptr)
            root = temp;
    }
    //Code inspired by Lecture 4 slide 129
    void BalanceTree(Node* node) {
        if (node->parent == nullptr) {
            node->red = false;
            return;
        }
        if (node->parent->red == false) { return; }
        Node* currP = node->parent;
        Node* currGP = GetGrandParent(node);
        Node* currU = GetUncle(node);
        if (currU != nullptr && currU->red) {
            currP->red = currU->red = false;
            currGP->red = true;
            BalanceTree(currGP);
            return;
        }
        if (node == currP->right && currP == currGP->left) {
            LeftRotation(currP);
            node->red = false;
            currGP->red = true;
            node = currP;
            currP = node->parent;
        }
        else if (node == currP->left && currP == currGP->right) {
            RightRotation(currP);
            node->red = false;
            currGP->red = true;
            node = currP;
            currP = node->parent;
        }
        else {
            currP->red = false;
            currGP->red = true;
        }
        if (node == currP->left)
            RightRotation(currGP);
        else
            LeftRotation(currGP);
    }
    void RemovePostOrder(Node* head) {
        if (head == nullptr)
            cout << "";
        else {
            RemovePostOrder(head->left);
            RemovePostOrder(head->right);
            Deletion(head);
        }
    }
    void Deletion(Node* head) {
        head->right = nullptr;
        head->left = nullptr;
        head->parent = nullptr;
        delete head;
    }
    Node* root;
    Node* parentInsert = nullptr;

public:
    RBTree() : root(nullptr) {}
    ~RBTree() {
        RemovePostOrder(root);
    }
    Node* GetRoot() { return root; }
    void Insert(string title, Game* game) {
        root = InsertHelp(root, root, title, game->GetGenre(), game->IsSingle(), game->IsMulti(), game->GetYear());
        if (root->NumChildren() == 0)
            root->red = false;
        if (parentInsert != nullptr && parentInsert->red) {
            Node* inserted;
            if (parentInsert->right != nullptr && parentInsert->right->GetGame().GetTitle() == title)
                inserted = parentInsert->right;
            else
                inserted = parentInsert->left;
            parentInsert = nullptr;
            BalanceTree(inserted);
        }
    }
    void SearchByTitle(string t) {
        TitleHelper(root, t);    
    }
    void SearchByGenre(string g) {
        GenreHelper(root, g);
    }
    void SearchBySingleMulti(bool s, bool m) {
        SingleMultiHelper(root, s, m);
    }
    void SearchByRelease(string r){
        ReleaseHelper(root, r);
    }
    void PrintRoot() {
        root->PrintInfo();
    }
    void PrintInOrder(){
        PrintInOrderHelper(root);
    }
};