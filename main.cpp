#include "BST.h"


void workWithBST() {
    int action = -1;
    int value;
    BST tree;

    while (action != 7) {
        cout << endl << "-------------------" << endl;
        cout << "1. Insert node" << endl
             << "2. Print tree" << endl
             << "3. Print simple" << endl
             << "4. Delete tree" << endl
             << "5. Generate tree" << endl
             << "6. Print file" << endl
             << "7. Exit" << endl
             << endl << "Choose option: ";
        cin >> action;
        cout << endl;


        switch (action)
        {
            case 1:
                cout << "Value: ";
                cin >> value;
                tree.insert(value, tree.root);
                break;

            case 2:
                tree.print(tree.root, false, "");
                break;

            case 3:
                tree.print_simple(tree.root, false, "");
                break;

            case 4:
                cout << "Value: ";
                cin >> value;
                tree.delete_node(value);
                break;

            case 5:
                long long num;

                cout << "Amount: ";
                cin >> num;
                cout << num << endl;
                tree.generate_tree(num);
                break;
            case 6:
                tree.file->printRecordsFromFile();
                break;

            case 7:
                return;

            default:
                cout << "Wrong option!" << endl;
        }

    }
}

void workWithTable() {
    int action = -1;
    int value;
    BST tree;

    while (action != 7) {
        cout << endl << "-------------------" << endl;
        cout << "1. Isert node" << endl
             << "2. Print tree" << endl
             << "3. Print simple" << endl
             << "4. Delete tree" << endl
             << "5. Generate tree" << endl
             << "6. Print file" << endl
             << "7. Exit" << endl
             << endl << "Choose option: ";
        cin >> action;
        cout << endl;


        switch (action)
        {
            case 1:
                cout << "Value: ";
                cin >> value;
                tree.insert(value, tree.root);
                break;

            case 2:
                tree.print(tree.root, false, "");
                break;

            case 3:
                tree.print_simple(tree.root, false, "");
                break;

            case 4:
                cout << "Value: ";
                cin >> value;
                tree.delete_node(value);
                break;

            case 5:
                long long num;

                cout << "Amount: ";
                cin >> num;
                cout << num << endl;
                tree.generate_tree(num);
                break;
            case 6:
                tree.file->printRecordsFromFile();
                break;

            case 7:
                return;

            default:
                cout << "Wrong option!" << endl;
        }

    }
}


int main()
{
    system("chcp 65001");

    int action = -1;
    int value;

    while (action != 7) {
        cout << endl << endl << "Working with:" << endl;
        cout << "1. Binary Search Tree" << endl
             << "2. Empty" << endl
             << "3. Hash table" << endl
             << "4. No work" << endl
             << endl << "Choose option: ";
        cin >> action;
        cout << endl;

        switch (action) {
            case 1:
                workWithBST();
                break;

            case 3:
                workWithTable();
                break;
        }

    return 0;


}
