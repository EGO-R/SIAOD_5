#ifndef SIAOD_5_SPLAYTREE_H
#define SIAOD_5_SPLAYTREE_H
#include "BinaryFile.h"

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

class SplayTree {
    Node* root;
    BinaryFile* file;

    SplayTree();
    ~SplayTree();
    void insert(int value, Node* node);
    void print(Node* node, bool isRight, string prefix);
    void print_simple(Node* node, bool isRight, string prefix);
    Node* find(int value, Node* node);
    void delete_node(int value);
    void generate_tree(long long num);
};


#endif //SIAOD_5_SPLAYTREE_H
