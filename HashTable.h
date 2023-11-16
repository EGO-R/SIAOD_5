#ifndef SIAOD_5_HASHTABLE_H
#define SIAOD_5_HASHTABLE_H
#include "BinaryFile.h"

class HashTable
{
public:
    long long size;
    Discipline* table;
    bool* isOccupied;
    streampos* positions;
    long long filled;
    long long deleted;
    BinaryFile* file;

    HashTable(long long size);
    ~HashTable();
    void insertRecord(Discipline* discipline);
    void deleteRecord(int discipline_id);
    void findRecord(int discipline_id);
    void printHashTable();
    long hashFunction(int key);
    long hashSecondFunction(int key);
    void generateTable(long long num);
};




#endif //SIAOD_5_HASHTABLE_H
