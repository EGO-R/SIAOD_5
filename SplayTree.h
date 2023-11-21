#ifndef SIAOD_5_SPLAYTREE_H
#define SIAOD_5_SPLAYTREE_H
#include "BinaryFile.h"



class SplayTree {
public:
    Node* root;
    BinaryFile* file;

    long long turns = 0;
    long long elem_amount = 0;

    SplayTree();
    void insert(int value);
    void print(Node* node, bool isRight, string prefix);
    void print_simple(Node* node, bool isRight, string prefix);
    Node* find(int value, Node* node);
    void delete_node(int value);
    void generate_tree(long long num);
    void splay(Node* node);
    void right_rotate(Node* child, Node* parent);
    void left_rotate(Node* child, Node* parent);
    void zig(Node* node, Node* parent);
    void zig_zig(Node* node, Node* parent, Node* parent_parent);
    void zig_zag(Node* node, Node* parent, Node* parent_parent);
    void merge(Node* left, Node* right);
    void split(int value, Node* nodes [2]);
    Node* find_closest(int value, Node* node);
};


#endif //SIAOD_5_SPLAYTREE_H
