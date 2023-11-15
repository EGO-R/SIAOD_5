#pragma once
#include <string>
#include <iostream>
#include <random>
#include <ctime>
#include <fstream>
#include "BinaryFile.h"
using namespace std;

class Node {
public:
    Discipline* discipline;
    streampos position;
    Node *parent;
    Node *left;
    Node *right;

    Node(Node* parent, Discipline* discipline, streampos position);

    ~Node();
};

class BST
{
public:
    Node* root;
    BinaryFile* file;

    BST();
    ~BST();
    void insert(int value, Node* node);
    void print(Node* node, bool isRight, string prefix);
    void print_simple(Node* node, bool isRight, string prefix);
    Node* find(int value, Node* node);
    void delete_node(int value);
    void generate_tree(long long num);
};

