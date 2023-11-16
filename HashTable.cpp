#include "HashTable.h"

using namespace std;


// Заполнение хеш-таблицы
HashTable::HashTable(long long size)
{
    this->size = size;
    this->table = new Discipline[size];
    this->isOccupied = new bool[size];
    this->positions = new streampos[size];
    this->filled = 0;
    this->deleted = 0;
    this->file = new BinaryFile("TableBinfile");
    for (long i = 0; i < size; i++)
    {
        this->table[i].discipline_id = -1;
        this->isOccupied[i] = false;
    }
}

HashTable::~HashTable() {
    delete[] table;
    delete[] isOccupied;
    delete[] positions;
    ofstream file(this->file->filename, ios::out | ios::trunc);
    file.close();
}

// Вставка записи
void HashTable::insertRecord(Discipline* discipline)
{
    if (filled >= (3 * size) / 4)
    {
        cout << "Rehashing..." << endl;
        size = size * 2;
        filled = 0;
        deleted = 0;
        Discipline* temp_table = table;
        bool* temp_isOccupied = isOccupied;
        streampos * temp_positions = positions;

        this->table = new Discipline[size];
        this->isOccupied = new bool[size];
        this->positions = new streampos[size];

        for (long long i = 0; i < size; i++) {
            this->table[i].discipline_id = -1;
            this->isOccupied[i] = false;
            this->positions[i] = -1;
        }

        ofstream file(this->file->filename, ios::out | ios::trunc);
        file.close();

        for (long long i = 0; i < size / 2; i++)
        {
            if (temp_isOccupied[i] && temp_table[i].discipline_id != -1)
            {
                insertRecord(&temp_table[i]);
            }
        }

        delete[] temp_table;
        delete[] temp_isOccupied;
    }

    long long position = hashFunction(discipline->discipline_id);
    long long increment = hashSecondFunction(discipline->discipline_id);
    long long k = 1;

    while (isOccupied[position] && table[position].discipline_id != -1)
    {
        position = (position + k * increment) % size;
        k++;
    }

    table[position] = *discipline;
    isOccupied[position] = true;
    positions[position] = file->addRecordToFile(discipline);
    filled++;
    cout << "Write added to table" << endl;
}



// Генерация записей
void HashTable::generateTable(long long num)
{
    srand(time(NULL));
    for (long long i = 0; i < num; i++)
    {
        Discipline* discipline = new Discipline();
        file->createRecord(discipline, rand());
        insertRecord(discipline);
    }
}

// Удаление записи из хеш-таблицы
void HashTable::deleteRecord(int discipline_id)
{
    long long position = hashFunction(discipline_id);
    long long increment = hashSecondFunction(discipline_id);
    long long k = 1;

    while (isOccupied[position])
    {
        if (table[position].discipline_id == discipline_id)
        {

            file->deleteRecordFromFile(positions[position]);
            table[position].discipline_id = -1;

            deleted++;
            cout << "Discipline with id: " << discipline_id << " has been deleted from table." << endl;

            if (deleted * 2 >= size) {
                cout << "Rehashing..." << endl;

                size = size - deleted;
                filled = 0;
                long long temp_deleted = deleted;
                deleted = 0;
                Discipline* temp_table = table;
                bool* temp_isOccupied = isOccupied;
                streampos * temp_positions = positions;

                this->table = new Discipline[size];
                this->isOccupied = new bool[size];
                this->positions = new streampos[size];

                for (long long i = 0; i < size; i++) {
                    this->table[i].discipline_id = -1;
                    this->isOccupied[i] = false;
                    this->positions[i] = -1;
                }

                ofstream file(this->file->filename, ios::out | ios::trunc);
                file.close();

                for (long i = 0; i < size - temp_deleted; i++)
                {
                    if (temp_isOccupied[i] && temp_table[i].discipline_id != -1)
                    {
                        insertRecord(&temp_table[i]);
                    }
                }

                delete[] temp_table;
                delete[] temp_isOccupied;
                delete[] temp_positions;

            }
            return;
        }
        position = (position + k * increment) % size;
        k++;
    }
    cout << "Discipline with id: " << discipline_id << " not found in table." << endl;
}

// Поиск записи в хеш-таблице
void HashTable::findRecord(int discipline_id)
{
    long long position = hashFunction(discipline_id);
    long long increment = hashSecondFunction(discipline_id);
    long long k = 1;

    while (isOccupied[position])
    {
        if (table[position].discipline_id == discipline_id)
        {
            cout << "Discipline with id: " << discipline_id << " has been found in table: "
                 << table[position].discipline_id << " "
                 << table[position].specification_id << " "
                 << table[position].name << " "
                 << table[position].term << " "
                 << " at position " << position << endl;
            return;
        }
        position = (position + k * increment) % size;
        k++;

        if (k >= size)
        {
            cout << "Discipline with id: " << discipline_id << " not found in table." << endl;
            return;
        }
    }
    cout << "Discipline with id: " << discipline_id << " not found in table." << endl;
}

// Вывод хеш-таблицы
void HashTable::printHashTable()
{
    for (long i = 0; i < size; i++)
    {
        if (!isOccupied[i])
            cout << "position: " << i << " is empty." << endl;

        else if(isOccupied[i] && table[i].discipline_id == -1)
            cout << "position: " << i << " is deleted." << endl;

        else
        {
            cout << "position: " << i
                 << " [Discipline id: " << table[i].discipline_id
                 << "; Specification id: " << table[i].specification_id
                 << "; Discipline name: " << table[i].name
                 << "; Term number: " << table[i].term
                 << "]\n";
        }
    }
}


// Первая хеш-функция
long HashTable::hashFunction(int key)
{
    return key % size;
}

// Вторая хеш-функция
long HashTable::hashSecondFunction(int key)
{
    return (key * size + 4) % size;
}
