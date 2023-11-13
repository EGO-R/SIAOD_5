#pragma once
#include <string>
#include <iostream>
#include <random>
#include <ctime>
#include <fstream>
using namespace std;

class Node {
public:
    char value;
    ofstream position;
    Node *parent;
    Node *left;
    Node *right;

    Node(Node* parent, char value);

    ~Node();
};

class BST
{
public:
    Node* root;

    BST();
    void insert(char value);
    void print(Node* node, bool isRight, string prefix);
    void print_tree();
    Node* find(char value);
    void get_distance(char value);
    void which_is_higher(char vaue1, char value2);
    int recur_distance(Node* node, long long counter);
    void delete_tree(char value);
    void generate_tree(long long num);
};

