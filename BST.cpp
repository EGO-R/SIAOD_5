#include "BST.h"

Node::Node(Node* parent, char value) : parent(parent), value(value) {};

Node::~Node() {
    if (parent) {
        if (parent->left == this)
            parent->left = nullptr;

        else
            parent->right = nullptr;
    }

    if (left)
        delete(left);

    if (right)
        delete(right);
}

BST::BST() : root(nullptr) {}

void BST::insert(char value)
{
    if (!root) {
        root = new Node(nullptr, value);
        return;
    }

    Node* current_node = root;
    Node* next_node;

    if (current_node->value > value)
        next_node = root->left;
    else
        next_node = root->right;

    while (next_node != nullptr) {
        while (next_node != nullptr && next_node->value > value) {
            current_node = next_node;
            next_node = next_node->left;


        }

        if (next_node == nullptr) {
            next_node = new Node(current_node, value);
            current_node->left = next_node;
            return;
        }

        current_node = next_node;
        next_node = current_node->right;
    }

    next_node = new Node(current_node, value);
    if (current_node->value > value)
        current_node->left = next_node;
    else
        current_node->right = next_node;
    return;

}

void BST::print(Node* node, bool isRight, string prefix)
{
    if (node != nullptr) {
        cout << prefix;
        cout << (isRight ? "|--" : "|__");
        cout << node->value << endl;
        print(node->right, true, prefix + ((node->parent && isRight && node->parent->left) ? "|  " : "   "));
        print(node->left, false, prefix + ((node->parent && isRight && node->parent->left) ? "|  " : "   "));
    }
}

void BST::print_tree() {

    if (!root)
        cout << "No tree!" << endl;
    else
        print(root, false, "");
}

Node* BST::find(char value)
{
    Node* node = root;


    while (true) {

        if (!node || node->value == value)
            break;

        else if (node->value > value)
            node = node->left;

        else
        {
            if (!node->right)
                break;

            node = node->right;
        }
    }

    if (!node || node->value < value && !node->right)
        return nullptr;

    else if (node->value == value)
        return node;

}


void BST::get_distance(char value)
{
    Node* node = root;

    int counter = 0;


    while (true) {

        if (!node || node->value == value)
            break;

        else if (node->value > value)
            node = node->left;

        else
        {
            if (!node->right)
                break;

            node = node->right;
        }

        counter++;
    }

    if (!node || node->value < value && !node->right)
        cout << "Value not found!" << endl;

    else if (node->value == value)
        cout << "Value distance: " << counter << endl;

    return;
}

int BST::recur_distance(Node* node, long long counter) {
    if (node) {
        counter++;
        return max(recur_distance(node->left, counter), recur_distance(node->right, counter));
    }
    return counter;
}



void BST::which_is_higher(char value1, char value2)
{
    int tree1 = recur_distance(find(value1), 0), tree2 = recur_distance(find(value2), 0);

    if (tree1 > tree2)
        cout << "First tree is higher" << endl;
    else if (tree2 > tree1)
        cout << "Second tree is higher" << endl;
    else
        cout << "Trees are the same" << endl;
};



void BST::delete_tree(char value)
{
    Node* node = find(value);

    if (node) {
        if (node == root)
            root = nullptr;
        delete(node);
        cout << "Node deleted!" << endl;

    }

    else
        cout << "Node not found!" << endl;
}

void BST::generate_tree(long long num) {
    srand(time(0));

    for (long long i = 0; i < num; i++) {
        if (i % 100000 == 0)
            cout << i << endl;
        insert(to_string(rand() % 10)[0]);
    }

}

