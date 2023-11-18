#include "SplayTree.h"





SplayTree::SplayTree() : root(nullptr) {
    file = new BinaryFile("SplayTreebinfile.bin");
}

SplayTree::~SplayTree() {
    ofstream file(this->file->filename, ios::out | ios::trunc);
    file.close();
}


void SplayTree::insert(int value, Node* node) {
    Discipline* discipline = new Discipline();
    file->createRecord(discipline, value);

    if (!root) {
        root = new Node(nullptr, discipline, file->addRecordToFile(discipline));
        cout << "Insert in SplayTree succes" << endl;
        return;
    }

    if (discipline->discipline_id < node->discipline->discipline_id) {
        if (node->left)
            insert(value, node->left);

        else {
            Node* new_node = new Node(node, discipline, file->addRecordToFile(discipline));
            node->left = new_node;
            cout << "Insert in SplayTree succes" << endl;
        }
    }

    else {
        if (node->right)
            insert(value, node->right);

        else {
            Node* new_node = new Node(node, discipline, file->addRecordToFile(discipline));
            node->right = new_node;
            cout << "Insert in SplayTree succes" << endl;
        }
    }
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



void SplayTree::delete_node(int value)
{
    Node* node = find(value, root);

    if (node) {
        if (node->right) {
            Node* temp_node = node->right;
            while (temp_node->left)
                temp_node = temp_node->left;

            temp_node->parent->left == temp_node ? temp_node->parent->left = nullptr : temp_node->parent->right = nullptr;
            if (node->parent)
                node->parent->left == node ? node->parent->left = temp_node : node->parent->right = temp_node;

            temp_node->parent = node->parent;
            temp_node->left = node->left;
            temp_node->right = node->right;

            if (node == root)
                root = temp_node;
        }

        else if (node->left) {
            Node* temp_node = node->left;
            if (node->parent)
                node->parent->left == node ? node->parent->left = temp_node : node->parent->right = temp_node;

            if (node == root)
                root = temp_node;
        }

        else if (node == root)
            root = nullptr;
        file->deleteRecordFromFile(node->position);
        delete(node);
        cout << "Node deleted!" << endl;

    }

    else
        cout << "Node not found!" << endl;
}

void SplayTree::generate_tree(long long num) {
    srand(time(0));

    for (int i = 0; i < num; i++) {
        insert(rand(), root);
    }

}

void SplayTree::splay(Node *node) {
    while (root != node) {
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
        }

        else if (parent) {
            zig(node, parent);
            root = node;
        }
    }
}

void SplayTree::right_rotate(Node *child, Node *parent) {
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
    if (node == parent->left) {
        right_rotate(node, parent);
    }

    else {
        left_rotate(node, parent);
    }
}

void SplayTree::zig_zig(Node *node, Node *parent, Node* parent_parent) {
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
    if (parent == parent_parent->left) {
        left_rotate(node, parent);
        right_rotate(node, parent_parent);
    }

    else {
        right_rotate(node, parent);
        left_rotate(node, parent_parent);
    }
}