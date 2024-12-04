#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <ostream>
#include <stdexcept>
#include <list>
#include "Dict.h"
#include "TableEntry.h"

template <typename V>
class HashTable: public Dict<V> {

    private:
        int n;
        int max;
        std::list<TableEntry<V> >* table;

        int h(std::string key);

    public:
        HashTable(int size);
        ~HashTable();
        int capacity();
        friend std::ostream& operator<<(std::ostream &out, const HashTable<V> &th);
        V operator[](std::string key);

        // Implementación de métodos virtuales de Dict
        void insert(std::string key, V value) override;
        V search(std::string key) override;
        V remove(std::string key) override;
        int entries() override;
};

template <typename V>
HashTable<V>::HashTable(int size) {
    this->n = 0;
    this->max = size;
    this->table = new std::list<TableEntry<V> >[size];
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
    for (char c : key) {
        sum += static_cast<int>(c);
    }
    return sum % this->max;
}

template <typename V>
std::ostream& operator<<(std::ostream &out, const HashTable<V> &th) {
    for (int i = 0; i < th.max; i++) {
        out << i << ": ";
        for (const auto& entry : th.table[i]) {
            out << entry << " ";
        }
        out << std::endl;
    }
    return out;
}

template <typename V>
V HashTable<V>::operator[](std::string key) {
    int pos = this->h(key);
    TableEntry<V> te(key);
    for (const auto& entry : this->table[pos]) {
        if (entry == te) {
            return entry.getValue();
        }
    }
    throw std::runtime_error("Key not found");
}

template <typename V>
void HashTable<V>::insert(std::string key, V value) {
    int pos = this->h(key);
    TableEntry<V> te(key, value);
    for (const auto& entry : this->table[pos]) {
        if (entry == te) {
            throw std::runtime_error("Key already exists");
        }
    }
    this->table[pos].push_back(te);
    this->n++;
}

template <typename V>
V HashTable<V>::search(std::string key) {
    int pos = this->h(key);
    TableEntry<V> te(key);
    for (const auto& entry : this->table[pos]) {
        if (entry == te) {
            return entry.getValue();
        }
    }
    throw std::runtime_error("Key not found");
}

template <typename V>
V HashTable<V>::remove(std::string key) {
    int pos = this->h(key);
    TableEntry<V> te(key);
    auto& entries = this->table[pos];
    for (auto it = entries.begin(); it != entries.end(); ++it) {
        if (*it == te) {
            V value = it->getValue();
            entries.erase(it);
            this->n--;
            return value;
        }
    }
    throw std::runtime_error("Key not found");
}

template <typename V>
int HashTable<V>::entries() {
    return this->n;
}

#endif