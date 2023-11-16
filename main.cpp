#include "BST.h"
#include "HashTable.h"


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

    long long size;
    cout << "Size of table: ";
    cin >> size;
    HashTable table(size);

    while (action != 6) {
        cout << endl << "-------------------" << endl;
        cout << "1. Insert record" << endl
             << "2. Print table" << endl
             << "3. Delete record" << endl
             << "4. Generate table" << endl
             << "5. Print file" << endl
             << "6. Exit" << endl
             << endl << "Choose option: ";
        cin >> action;
        cout << endl;


        switch (action)
        {
            case 1:
                cout << "Value: ";
                cin >> value;
                Discipline discipline;
                table.file->createRecord(&discipline, value);
                table.insertRecord(&discipline);
                break;

            case 2:
                table.printHashTable();
                break;

            case 3:
                cout << "Value: ";
                cin >> value;
                table.deleteRecord(value);
                break;

            case 4:
                long long genValue;
                cout << "Value: ";
                cin >> genValue;
                table.generateTable(genValue);
                break;

            case 5:
                table.file->printRecordsFromFile();
                break;

            case 6:
                return;

            default:
                cout << "Wrong option!" << endl;
        }

    }
}


int main() {
    system("chcp 65001");

    int action = -1;
    int value;

    while (action != 7) {
        cout << endl << endl << "Working with:" << endl;
        cout << "1. Binary Search Tree" << endl
             << "2. Empty" << endl
             << "3. Hash table" << endl
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



    }
    return 0;
}