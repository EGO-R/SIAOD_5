#ifndef SIAOD_5_BINARYFILE_H
#define SIAOD_5_BINARYFILE_H

#include <string>
#include <iostream>
#include <random>
#include <ctime>
#include <fstream>
using namespace std;

struct Discipline
{
    int discipline_id;
    int specification_id;
    char name[64];
    int term;
};

class BinaryFile {
    string filename;

    BinaryFile(string filename) { this->filename = filename;};
    streampos addRecordToFile(Discipline* discipline);
    void deleteRecordFromFile(streampos position);
    void printRecordsFromFile();
};


#endif //SIAOD_5_BINARYFILE_H
