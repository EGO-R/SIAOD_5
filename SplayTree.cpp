#include "SplayTree.h"





SplayTree::SplayTree() : root(nullptr) {
    file = new BinaryFile("SplayTreebinfile.bin");
}


void SplayTree::print(Node* node, bool isRight, string prefix)
{
    if (!root) {
        cout << "No tree!" << endl;
        return;
    }

    if (node != nullptr) {
        cout << prefix;
        cout << (isRight ? "|--" : "|__");
        cout << " [Discipline id: " << node->discipline->discipline_id
             << "; Specification id: " << node->discipline->specification_id
             << "; Discipline name: " << node->discipline->name
             << "; Term number: " << node->discipline->term
             << "]\n";
        print(node->right, true, prefix + ((node->parent && isRight && node->parent->left) ? "|  " : "   "));
        print(node->left, false, prefix + ((node->parent && isRight && node->parent->left) ? "|  " : "   "));
    }
}

void SplayTree::print_simple(Node* node, bool isRight, string prefix)
{
    if (!root) {
        cout << "No tree!" << endl;
        return;
    }

    if (node != nullptr) {
        cout << prefix;
        cout << (isRight ? "|--" : "|__");
        cout << node->discipline->discipline_id << endl;
        print_simple(node->right, true, prefix + ((node->parent && isRight && node->parent->left) ? "|  " : "   "));
        print_simple(node->left, false, prefix + ((node->parent && isRight && node->parent->left) ? "|  " : "   "));
    }
}



Node* SplayTree::find(int value, Node* node)
{
    if (!node)
        return nullptr;

    if (value == node->discipline->discipline_id) {
        splay(node);
        return node;
    }

    if (value < node->discipline->discipline_id) {
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


void SplayTree::generate_tree(long long num) {
    turns = 0;
    elem_amount = num;
    srand(time(NULL));

    for (int i = 0; i < num; i++) {
        cout << "Number: " << i << endl;
        insert(rand() % 1000);
    }
    cout << "Среднее количество поворотов: " << turns  << " " << elem_amount << endl;
}

void SplayTree::splay(Node *node) {
    if (!node)
        return;
    while (node->parent) {

        Node* parent = node->parent;
        Node* parent_parent = nullptr;
        if (parent)
            parent_parent = parent->parent;

        if (parent_parent) {
            if (parent == parent_parent->left && node == parent->left ||
            parent == parent_parent->right && node == parent->right)
                zig_zig(node, parent, parent_parent);
            else
                zig_zag(node, parent, parent_parent);

            if (parent_parent == root)
                root = node;
        }

        else if (parent) {
            zig(node, parent);
            root = node;
        }
    }
}

void SplayTree::right_rotate(Node *child, Node *parent) {
    turns++;
    Node* parent_parent = parent->parent;

    parent->parent = child;
    parent->left = child->right;

    if (child->right)
        child->right->parent = parent;

    child->parent = parent_parent;
    child->right = parent;

    if (parent_parent && parent == parent_parent->left)
        parent_parent->left = child;

    else if (parent_parent)
        parent_parent->right = child;
}

void SplayTree::left_rotate(Node *child, Node *parent) {
    turns++;
    Node* parent_parent = parent->parent;

    parent->parent = child;
    parent->right = child->left;

    if (child->left)
        child->left->parent = parent;

    child->parent = parent_parent;
    child->left = parent;

    if (parent_parent && parent == parent_parent->left)
        parent_parent->left = child;

    else if (parent_parent)
        parent_parent->right = child;
}

void SplayTree::zig(Node *node, Node *parent) {
//    cout << "zig" << endl;
    if (node == parent->left) {
        right_rotate(node, parent);
    }

    else {
        left_rotate(node, parent);
    }
}

void SplayTree::zig_zig(Node *node, Node *parent, Node* parent_parent) {
//    cout << "zig-zig" << endl;
    if (node == parent->left) {
        right_rotate(parent, parent_parent);
        right_rotate(node, parent);
    }

    else {
        left_rotate(parent, parent_parent);
        left_rotate(node, parent);

    }
}

void SplayTree::zig_zag(Node *node, Node *parent, Node *parent_parent) {
//    cout << "zig-zag" << endl;
    if (parent == parent_parent->left) {
        left_rotate(node, parent);
        right_rotate(node, parent_parent);
    }

    else {
        right_rotate(node, parent);
        left_rotate(node, parent_parent);
    }
}


Node* SplayTree::find_closest(int value, Node *node) {
    if (!node)
        return nullptr;

    if (value == node->discipline->discipline_id) {
        splay(node);
        return node;
    }

    if (value < node->discipline->discipline_id) {
        if (node->left)
            return find_closest(value, node->left);

        else {
            splay(node);
            return node;
        }
    }

    else {
        if (node->right)
            return find_closest(value, node->right);

        else {
            splay(node);
            return node;
        }
    }
}

void SplayTree::split(int value, Node* nodes [2]) {
    Node* node = find_closest(value, root);
    if (!node){
        nodes[0] = nullptr;
        nodes[1] = nullptr;
        return;
    }

    if (node->discipline->discipline_id == value) {
        if (node->left)
            node->left->parent = nullptr;
        if (node->right)
            node->right->parent = nullptr;
        nodes[0] = node->left;
        nodes[1] = node->right;
        delete_node(node->discipline->discipline_id);
        return;
    }

    else if (node->discipline->discipline_id < value) {
        Node* right = node->right;
        node->right = nullptr;
        if (right)
            right->parent = nullptr;
        nodes[0] = node;
        nodes[1] = right;
        return;
    }

    else if (node->discipline->discipline_id > value) {
        Node* left = node->left;
        node->left = nullptr;
        if (left)
            left->parent = nullptr;
        nodes[0] = left;
        nodes[1] = node;
        return;
    }

}

void SplayTree::insert(int value) {
    cout << value << endl;
    Node* nodes [2];
    split(value, nodes);
    Node* left = nodes[0];
    Node* right = nodes[1];
    Discipline* discipline = new Discipline();
    file->createRecord(discipline, value);
    root = new Node(nullptr, discipline, file->addRecordToFile(discipline));
    root->left = left;
    root->right = right;
    if (left)
        left->parent = root;
    if (right)
        right->parent = root;
}

void SplayTree::merge(Node *left, Node *right) {
    Node* max_node = left;

    if (left) {
        while (max_node->right)
            max_node = max_node->right;

        splay(max_node);
        root = max_node;

        max_node->right = right;
        if (right)
            right->parent = max_node;
    }

    else if (right)
        root = right;
    else
        root = nullptr;
}

void SplayTree::delete_node(int value) {
    Node* node = find(value, root);

    if (!node) {
        cout << "Node not found!" << endl;
        return;
    }

    if (node->left)
        node->left->parent = nullptr;

    if (node->right)
        node->right->parent = nullptr;

    file->deleteRecordFromFile(node->position);
    merge(node->left, node->right);
    delete(node);
}