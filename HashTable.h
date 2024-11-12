#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <ostream>
#include <stdexcept>
#include "Dict.h"
#include "TableEntry.h"

#include "/Users/alejandrogonzalez/Desktop/PRA_2324_P1/ListLinked.h"

template <typename V>
class HashTable: public Dict<V> {

    private:
        int n;
        int max;
        ListLinked<TableEntry<V> >* table;

        int h(std::string key);

    public:
        HashTable(int size);
        ~HashTable();
        int capacity();
        friend std::ostream& operator<<(std::ostream &out, const HashTable<V> &th);
        V operator[](std::string key);
};


template <typename V>
HashTable<V>::HashTable(int size) {
    this->n = 0;
    this->max = size;
    this->table = new ListLinked<TableEntry<V> >[size];
}

template <typename V>
HashTable<V>::~HashTable() {
    delete[] this->table;
}

template <typename V>
int HashTable<V>::capacity() {
    return this->max;
}

template <typename V>
int HashTable<V>::h(std::string key) {
    int sum = 0;
    for (int i = 0; i < key.length(); i++) {
        sum += key[i];
    }
    return sum % this->max;
}

template <typename V>
std::ostream& operator<<(std::ostream &out, const HashTable<V> &th) {
    for (int i = 0; i < th.max; i++) {
        out << i << ": " << th.table[i] << std::endl;
    }
    return out;
}

template <typename V>
V HashTable<V>::operator[](std::string key) {
    int pos = this->h(key);
    TableEntry<V> te(key);
    if (this->table[pos].search(te) == nullptr) {
        throw std::invalid_argument("Key not found");
    }
    return this->table[pos].search(te)->value;
}


#endif