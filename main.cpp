#include "BST.h"
#include "HashTable.h"
#include "SplayTree.h"


void workWithBST() {
    int action = -1;
    int value;
    BST tree;

    auto start = chrono::steady_clock::now();
    auto end = chrono::steady_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(end - start).count();
    Node* x;

    while (action != 7) {
        cout << endl << "-------------------" << endl;
        cout << "1. Insert node" << endl
             << "2. Print tree" << endl
             << "3. Find" << endl
             << "4. Print simple" << endl
             << "5. Delete tree" << endl
             << "6. Generate tree" << endl
             << "7. Print file" << endl
             << "8. Exit" << endl
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
                cout << "Value: ";
                cin >> value;

                start = chrono::steady_clock::now();
                x = tree.find(value, tree.root);
                if (x)
                    cout << "Found" << endl;
                else
                    cout << "Not found" << endl;

                end = chrono::steady_clock::now();
                duration = chrono::duration_cast<chrono::microseconds>(end - start).count();

                cout << "Reading record time: " << duration << " ms" << endl;
                break;

            case 4:
                tree.print_simple(tree.root, false, "");
                break;

            case 5:
                cout << "Value: ";
                cin >> value;
                tree.delete_node(value);
                break;

            case 6:
                long long num;

                cout << "Amount: ";
                cin >> num;
                cout << num << endl;


                tree.generate_tree(num);

                break;
            case 7:
                tree.file->printRecordsFromFile();
                break;

            case 8:
                return;

            default:
                cout << "Wrong option!" << endl;
        }

    }
}

void workWithSplay() {
    int action = -1;
    int value;
    SplayTree tree;
    Node* x;

    auto start = chrono::steady_clock::now();
    auto end = chrono::steady_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(end - start).count();

    while (action != 7) {
        cout << endl << "-------------------" << endl;
        cout << "1. Insert node" << endl
        << "2. Print tree" << endl
        << "3. Find" << endl
        << "4. Delete" << endl
        << "5. Generate tree" << endl
        << "6. Print file" << endl
        << "7. Exit" << endl;
        cin >> action;
        cout << endl;


        switch (action)
        {
            case 1:
                cout << "Value: ";
                cin >> value;
                tree.insert(value);
                break;


            case 2:
                tree.print_simple(tree.root, false, "");
                break;

            case 3:
                cout << "Value: ";
                cin >> value;

                start = chrono::steady_clock::now();
                x = tree.find(value, tree.root);
                end = chrono::steady_clock::now();
                duration = chrono::duration_cast<chrono::microseconds>(end - start).count();


                if (x)
                    cout << " [Discipline id: " << x->discipline->discipline_id
                        << "; Specification id: " << x->discipline->specification_id
                        << "; Discipline name: " << x->discipline->name
                        << "; Term number: " << x->discipline->term
                        << "]\n";
                else
                    cout << "Not found!" << endl;

                cout << "Reading record time: " << duration << " ms" << endl;
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
    Discipline* x;

    auto start = chrono::steady_clock::now();
    auto end = chrono::steady_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(end - start).count();

    while (action != 6) {
        cout << endl << "-------------------" << endl;
        cout << "1. Insert record" << endl
             << "2. Print table" << endl
             << "3. Find" << endl
             << "4. Delete record" << endl
             << "5. Generate table" << endl
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

                start = chrono::steady_clock::now();
                table.findRecord(value);
                end = chrono::steady_clock::now();
                duration = chrono::duration_cast<chrono::microseconds>(end - start).count();

                cout << "Reading record time: " << duration << " ms" << endl;
                break;

            case 4:
                cout << "Value: ";
                cin >> value;
                table.deleteRecord(value);
                break;

            case 5:
                long long genValue;
                cout << "Value: ";
                cin >> genValue;

                table.generateTable(genValue);
                break;

            case 6:
                table.file->printRecordsFromFile();
                break;

            case 7:
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
             << "2. Splay tree" << endl
             << "3. Hash table" << endl
             << endl << "Choose option: ";
        cin >> action;
        cout << endl;

        switch (action) {
            case 1:
                workWithBST();
                break;

            case 2:
                workWithSplay();
                break;

            case 3:
                workWithTable();
                break;
        }



    }
    return 0;
}