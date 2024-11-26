#ifndef BSTREEDICT_H
#define BSTREEDICT_H

#include <ostream>
#include <stdexcept>
#include "Dict.h"
#include "BSTree.h"
#include "TableEntry.h"

template <typename V>
class BSTreeDict: public Dict<V> {

    private:
        BSTree<TableEntry<V> >* tree;

    public:
        BSTreeDict();
        ~BSTreeDict();
        friend std::ostream& operator<<(std::ostream &out, const BSTreeDict<V> &bs);
        V operator[](std::string key);

        // Implementación de métodos virtuales de Dict
        void insert(std::string key, V value) override;
        V search(std::string key) override;
        V remove(std::string key) override;
        int entries() override;
};

template <typename V>
BSTreeDict<V>::BSTreeDict() {
    tree = new BSTree<TableEntry<V> >();
}

template <typename V>
BSTreeDict<V>::~BSTreeDict() {
    delete tree;
}

template <typename V>
void BSTreeDict<V>::insert(std::string key, V value) {
    TableEntry<V> entry(key, value);
    tree->insert(entry);
}

template <typename V>
V BSTreeDict<V>::search(std::string key) {
    TableEntry<V> entry(key);
    TableEntry<V> result = tree->search(entry);
    return result.getValue();
}

template <typename V>
V BSTreeDict<V>::remove(std::string key) {
    TableEntry<V> entry(key);
    TableEntry<V> result = tree->search(entry);
    tree->remove(entry);
    return result.getValue();
}

template <typename V>
int BSTreeDict<V>::entries() {
    return tree->size();
}

template <typename V>
std::ostream& operator<<(std::ostream &out, const BSTreeDict<V> &bs) {
    out << *(bs.tree);
    return out;
}

template <typename V>
V BSTreeDict<V>::operator[](std::string key) {
    return search(key);
}

#endif