#include "BST.h"

Node::Node(Node* parent, char value) : parent(parent), value(value), left(nullptr), right(nullptr) {};

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


void BST::insert(char value, Node* node) {
    if (!root) {
        root = new Node(nullptr, value);
        cout << "Insert succes" << endl;
        return;
    }

    if (value < node->value) {
        if (node->left)
            insert(value, node->left);

        else {
            Node* new_node = new Node(node, value);
            node->left = new_node;
            cout << "Insert succes" << endl;
        }
    }

    else {
        if (node->right)
            insert(value, node->right);

        else {
            Node* new_node = new Node(node, value);
            node->right = new_node;
            cout << "Insert succes" << endl;
        }
    }
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

Node* BST::find(char value, Node* node)
{
    if (!node)
        return nullptr;

    if (value == node->value) {
        return node;
    }

    if (value < node->value) {
        if (node->left)
            return find(value, node->left);

        else
            return nullptr;
    }

    else {
        if (node->right)
            return find(value, node->right);

        else
            return nullptr;
    }

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

int BST::recur_distance(Node* node, int counter) {
    if (node) {
        counter++;
        return max(recur_distance(node->left, counter), recur_distance(node->right, counter));
    }
    return counter;
}



void BST::wich_is_higher(char value1, char value2)
{
    int tree1 = recur_distance(find(value1, root), 0), tree2 = recur_distance(find(value2, root), 0);

    if (tree1 > tree2)
        cout << "First tree is higher" << endl;
    else if (tree2 > tree1)
        cout << "Second tree is higher" << endl;
    else
        cout << "Trees are the same" << endl;
};



void BST::delete_tree(char value)
{
    Node* node = find(value, root);

    if (node) {
        if (node == root)
            root = nullptr;
        delete(node);
        cout << "Node deleted!" << endl;

    }

    else
        cout << "Node not found!" << endl;
}

void BST::generate_tree(int num) {
    srand(time(0));

    for (int i = 0; i < num; i++) {
        insert(to_string(rand() % 10)[0], root);
    }

}

