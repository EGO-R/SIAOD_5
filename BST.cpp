#include "BST.h"





BST::BST() : root(nullptr) {
    file = new BinaryFile("BSTbinfile.bin");
}


void BST::insert(int value, Node* node) {
    Discipline* discipline = new Discipline();
    file->createRecord(discipline, value);

    if (!root) {
        root = new Node(nullptr, discipline, file->addRecordToFile(discipline));
//        cout << "Insert in BST succes" << endl;
        return;
    }

    if (discipline->discipline_id < node->discipline->discipline_id) {
        if (node->left)
            insert(value, node->left);

        else {
            Node* new_node = new Node(node, discipline, file->addRecordToFile(discipline));
            node->left = new_node;
//            cout << "Insert in BST succes" << endl;
        }
    }

    else {
        if (node->right)
            insert(value, node->right);

        else {
            Node* new_node = new Node(node, discipline, file->addRecordToFile(discipline));
            node->right = new_node;
//            cout << "Insert in BST succes" << endl;
        }
    }
}

void BST::print(Node* node, bool isRight, string prefix)
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

void BST::print_simple(Node* node, bool isRight, string prefix)
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



Node* BST::find(int value, Node* node)
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



void BST::delete_node(int value)
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

void BST::generate_tree(long long num) {
    srand(time(0));

    for (int i = 0; i < num; i++) {
        insert(rand() % 1000000, root);
    }

}

