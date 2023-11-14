#include "BinaryFile.h"


streampos BinaryFile::addRecordToFile(Discipline* discipline) {
    ofstream file(filename, ios::binary | ios::ate);
    if (!file) {
        cout << "Error file opening!" << endl;
        return -1;
    }

    streampos position = file.tellp();
    file.write(reinterpret_cast<const char*>(discipline), sizeof(Discipline));
    cout << "Record succesfully added to file." << endl;
    return position;
}






void BinaryFile::deleteRecordFromFile(streampos position) {
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

        if (file.tellp() != position) {
            tempFile.write(reinterpret_cast<const char*>(&discipline), sizeof(Discipline));
        }
        else {
            flag = true;
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