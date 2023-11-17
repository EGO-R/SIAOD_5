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
    void rebuild_tree(Node* node);
    void right_rotate(Node* child, Node* parent);
    void left_rotate(Node* child, Node* parent);
    void zig(Node* node, Node* parent);
    void zig_zig(Node* node, Node* parent, Node* parent_parent);
    void zig_zag(Node* node, Node* parent, Node* parent_parent);
};


#endif //SIAOD_5_SPLAYTREE_H
