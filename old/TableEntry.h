#ifndef TABLEENTRY_H
#define TABLEENTRY_H

#include <string>
#include <ostream>

template <typename V>
class TableEntry
{
public:
    std::string key;
    V value;

    TableEntry(std::string key, V value);
    TableEntry(std::string key);
    TableEntry();

    V getValue() const;

    friend bool operator==(const TableEntry<V> &te1, const TableEntry<V> &te2);
    friend bool operator!=(const TableEntry<V> &te1, const TableEntry<V> &te2);
    friend std::ostream &operator<<(std::ostream &out, const TableEntry<V> &te);

    friend bool operator<(const TableEntry<V> &te1, const TableEntry<V> &te2);
    friend bool operator>(const TableEntry<V> &te1, const TableEntry<V> &te2);
};

template <typename V>
TableEntry<V>::TableEntry(std::string key, V value)
    : key(key), value(value) {}

template <typename V>
TableEntry<V>::TableEntry(std::string key)
    : key(key), value(V()) {}

template <typename V>
TableEntry<V>::TableEntry()
    : key(""), value(V()) {}

template <typename V>
V TableEntry<V>::getValue() const
{
    return value;
}

template <typename V>
bool operator==(const TableEntry<V> &te1, const TableEntry<V> &te2)
{
    return te1.key == te2.key;
}

template <typename V>
bool operator!=(const TableEntry<V> &te1, const TableEntry<V> &te2)
{
    return !(te1 == te2);
}

template <typename V>
std::ostream &operator<<(std::ostream &out, const TableEntry<V> &te)
{
    out << "Key: " << te.key << ", Value: " << te.value;
    return out;
}

template <typename V>
bool operator<(const TableEntry<V> &te1, const TableEntry<V> &te2)
{
    return te1.key < te2.key;
}

template <typename V>
bool operator>(const TableEntry<V> &te1, const TableEntry<V> &te2)
{
    return te1.key > te2.key;
}

#endif