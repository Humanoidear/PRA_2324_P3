#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <ostream>
#include <stdexcept>
#include "Dict.h"
#include "TableEntry.h"

#include "../PRA_2425_P1/ListLinked.h" // ¡¡¡¡MODIFICAR!!!!

template <typename V>
class HashTable : public Dict<V>
{

private:
	int n;
	int max;
	ListLinked<TableEntry<V>> *table;

	int h(std::string key)
	{
		int sum = 0;
		for (char c : key)
		{
			sum += static_cast<int>(c); // Suma valores ASCII de los caracteres.
		}
		return sum % max;
	}

public:
	HashTable(int size) : n(0), max(size), table(new ListLinked<TableEntry<V>>[size]) {}

	~HashTable()
	{
		delete[] table;
	}

	void insert(std::string key, V value) override
	{
		int cubeta = h(key);
		TableEntry<V> entry(key, value);

		for (int i = 0; i < table[cubeta].size(); i++)
		{
			if (table[cubeta].get(i) == entry)
			{
				throw std::runtime_error("Llave duplicada");
			}
		}

		table[cubeta].insert(0, entry);
		n += 1;
	}

	V search(std::string key) override
	{
		int cubeta = h(key);
		TableEntry<V> searchKey(key);

		for (int i = 0; i < table[cubeta].size(); i++)
		{
			if (table[cubeta].get(i) == searchKey)
			{
				return table[cubeta].get(i).value;
			}
		}

		throw std::runtime_error("Key no encontrada");
	}

	V remove(std::string key) override
	{
		int cubeta = h(key);
		TableEntry<V> searchKey(key);

		for (int i = 0; i < table[cubeta].size(); ++i)
		{
			if (table[cubeta].get(i) == searchKey)
			{
				V value = table[cubeta].get(i).value;
				table[cubeta].remove(i); // Usa el índice para eliminar.
				--n;
				return value;
			}
		}

		throw std::runtime_error("Key no encontrada");
	}

	int entries() override
	{
		return n;
	}

	int capacity()
	{
		return max;
	}

	friend std::ostream &operator<<(std::ostream &out, const HashTable<V> &th)
	{
		for (int i = 0; i < th.max; i++)
		{
			out << "Cubeta " << i << ":" << th.table[i] << std::endl;
		}
		return out;
	}

	V operator[](std::string key)
	{
		return search(key);
	}
};

#endif
