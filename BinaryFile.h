#ifndef SIAOD_5_BINARYFILE_H
#define SIAOD_5_BINARYFILE_H

#include <string>
#include <iostream>
#include <random>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <string.h>
using namespace std;

struct Discipline
{
    int discipline_id;
    int specification_id;
    char name[64];
    int term;
};

class BinaryFile {
public:
    string filename;

    BinaryFile(string filename) { this->filename = filename;};
    streampos addRecordToFile(Discipline* discipline);
    void deleteRecordFromFile(streampos position);
    void printRecordsFromFile();
    void createRecord(Discipline* discipline, int num);
};


#endif //SIAOD_5_BINARYFILE_H
