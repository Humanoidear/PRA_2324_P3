#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <ostream>
#include <stdexcept>
#include "Dict.h"
#include "TableEntry.h"

template <typename V>
class HashTable : public Dict<V>
{
private:
    int n;
    int max;
    TableEntry<V> *table;
    bool *occupied;

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
    HashTable(int size) : n(0), max(size), table(new TableEntry<V>[size]), occupied(new bool[size]())
    {
    }

    ~HashTable()
    {
        delete[] table;
        delete[] occupied;
    }

    // Inserta un valor en la tabla hash, si la llave ya existe, lanza una excepción.
    // Si la tabla está llena, lanza una excepción.
    // Si la cubeta está ocupada, se realiza un sondeo cuadrático (sumar i^2 a la cubeta actual hasta encontrar una vacía).
    void insert(std::string key, V value) override
    {
        int cubeta = h(key);
        int i = 0;

        while (i < max)
        {
            int newCubeta = (cubeta + i * i) % max;
            if (!occupied[newCubeta])
            {
                table[newCubeta] = TableEntry<V>(key, value);
                occupied[newCubeta] = true;
                n += 1;
                return;
            }
            else if (table[newCubeta].key == key)
            {
                throw std::runtime_error("Llave duplicada");
            }
            i++;
        }

        throw std::runtime_error("Tabla hash llena");
    }

    // Busca un valor en la tabla hash, recorriendo las cubetas hasta encontrar la llave.
    // Si no se encuentra, lanza una excepción.
    // Se utiliza sondeo cuadrático para manejar colisiones.
    V search(std::string key) override
    {
        int cubeta = h(key);
        int i = 0;

        while (i < max)
        {
            int newCubeta = (cubeta + i * i) % max;
            if (occupied[newCubeta] && table[newCubeta].key == key)
            {
                return table[newCubeta].value;
            }
            i++;
        }

        throw std::runtime_error("Key no encontrada");
    }

    // Lo mismo que search, pero elimina la llave de la tabla hash.
    // Se utiliza sondeo cuadrático para manejar colisiones.
    V remove(std::string key) override
    {
        int cubeta = h(key);
        int i = 0;

        while (i < max)
        {
            int newCubeta = (cubeta + i * i) % max;
            if (occupied[newCubeta] && table[newCubeta].key == key)
            {
                V value = table[newCubeta].value;
                occupied[newCubeta] = false;
                n -= 1;
                return value;
            }
            i++;
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
            if (th.occupied[i])
            {
                out << "Cubeta " << i << ": " << th.table[i] << std::endl;
            }
            else
            {
                out << "Cubeta " << i << ": [vacía]" << std::endl;
            }
        }
        return out;
    }

    V operator[](std::string key)
    {
        return search(key);
    }
};

#endif