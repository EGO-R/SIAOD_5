#include "BinaryFile.h"


Node::Node(Node* parent, Discipline* discipline, streampos position) : parent(parent), discipline(discipline), position(position), left(nullptr), right(nullptr) {};

Node::~Node() {
    delete(discipline);
}

char names[][64] = {"Матлог", "Информатика", "История", "Философия"};

streampos BinaryFile::addRecordToFile(Discipline* discipline) {
    fstream fs(filename, ios::binary | ios::app | ios::ate);

    if (!fs.is_open()) {
        cout << "Failed to open file" <<endl;
    }

    fs.write(reinterpret_cast<const char*>(discipline), sizeof(Discipline));

    streampos currentPos = fs.tellp();

    fs.close();

    return currentPos;
}






void BinaryFile::deleteRecordFromFile(streampos position) {
    cout << position << endl << endl;
    fstream file(filename, ios::binary | ios::in | ios::out);
    if (!file) {
        cout << "Error file opening!" << endl;
        return;
    }

    ofstream tempFile("temp.bin", ios::binary);
    if (!tempFile) {
        cout << "Error creating temporary file!" << endl;
        file.close();
        return;
    }

    bool flag = false;
    Discipline discipline;
    while (file.read(reinterpret_cast<char*>(&discipline), sizeof(Discipline))) {
        if (file.tellg() != position) {
            tempFile.write(reinterpret_cast<const char*>(&discipline), sizeof(Discipline));
        }
        else {
            flag = true;
            discipline.discipline_id = -1;
            tempFile.write(reinterpret_cast<const char*>(&discipline), sizeof(Discipline));
            cout << "Discipline has been deleted from file." << endl;
        }

    }

    if (!flag)
        cout << "Discipline not found in file." << endl;

    file.close();
    tempFile.close();

    if (remove(filename.c_str()) != 0) {
        cout << "Error deleting temporary file!" << endl;
        return;
    }

    if (rename("temp.bin", filename.c_str()) != 0) {
        cout << "Error renaming temporary file!" << endl;
        return;
    }
}







void BinaryFile::printRecordsFromFile() {
    ifstream file(filename, ios::binary);
    if (!file) {
        cout << "Error opening file!" << endl;
        return;
    }

    Discipline discipline;
    while (file.read(reinterpret_cast<char*>(&discipline), sizeof(Discipline))) {
        cout << " [Discipline id: " << discipline.discipline_id
             << "; Specification id: " << discipline.specification_id
             << "; Discipline name: " << discipline.name
             << "; Term number: " << discipline.term
             << "]\n";
    }

    file.close();
}


void BinaryFile::createRecord(Discipline* discipline, int num)
{
    int random_id = num % 15000;
    int random_specification_id = random_id % 30 + 1;
    char name[64];
    int random_term = random_id % 8 + 1;
    strcpy_s(name, names[random_id % 4]);

    discipline->discipline_id = random_id;
    discipline->specification_id = random_specification_id;
    strcpy_s(discipline->name, name);
    discipline->term = random_term;
}