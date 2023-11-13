#include "BST.h"



int main()
{

    const string filename = "binfile.bin";

    int action;
    char value;
    BST tree;

    while (true) {
        cout << endl << "-------------------" << endl;
        cout << "1. Isert node" << endl
             << "2. Print tree" << endl
             << "3. Define level" << endl
             << "4. Find higher tree" << endl
             << "5. Delete tree" << endl
             << "6. Generate tree" << endl
             << endl << "Choose option: ";
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
                tree.print_tree();
                break;

            case 3:
                cout << "Value: ";
                cin >> value;
                tree.get_distance(value);
                break;

            case 4:
                char value1, value2;
                cout << "Value 1: ";
                cin >> value1;
                cout << "Value 2: ";
                cin >> value2;

                tree.which_is_higher(value1, value2);
                break;

            case 5:
                cout << "Value: ";
                cin >> value;
                tree.delete_tree(value);
                break;

            case 6:
                long long num;

                cout << "Amount: ";
                cin >> num;
                cout << num << endl;
                tree.generate_tree(num);
                break;


            default:
                cout << "Wrong option!" << endl;
        }

    }
    return 0;


}
