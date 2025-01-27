#pragma once

#include <vector>
#include <functional>
#include <optional>
#include <stdexcept>
#include <iostream>

#include "UniversalHash.h"

template<typename T>
class OAHashTable 
{
private:
    struct Entry 
    {
        T value;
        bool isOccupied; 
        bool isDeleted;  

        Entry() : isOccupied(false), isDeleted(false) {}
    };

    std::vector<Entry> table; 
    UniversalHash<T> hashFunction; 
    size_t tableSize; 
    size_t numElements; 

    size_t nextIndex(size_t currentIndex) const 
    {
        return (currentIndex + 1) % tableSize;
    }

public:
    OAHashTable(size_t size)
        : table(size), hashFunction(size), tableSize(size), numElements(0) 
    {
    }
    void insert(T value) 
    {
        if (numElements >= tableSize * 0.7) 
        { 
            rehash();
        }

        size_t index = hashFunction(value) % tableSize;
        while (table[index].isOccupied && !table[index].isDeleted) 
        {
            if (table[index].value == value) 
            {
                
                return;
            }
            index = nextIndex(index);
        }

        table[index].value = value;
        table[index].isOccupied = true;
        table[index].isDeleted = false;
        ++numElements;
    }

    bool find(T value)  
    {
        size_t index = hashFunction(value) % tableSize;
        size_t startIndex = index; 

        while (table[index].isOccupied || table[index].isDeleted) 
        {
            if (table[index].isOccupied && !table[index].isDeleted && table[index].value == value) 
            {
                return true;
            }
            index = nextIndex(index);
            if (index == startIndex) 
            {
                break; 
            }
        }

        return false;
    }

    bool erase(const T& value)
    {
        size_t index = hashFunction(value) % tableSize;
        size_t startIndex = index;

        while (table[index].isOccupied || table[index].isDeleted) 
        {
            if (table[index].isOccupied && !table[index].isDeleted && table[index].value == value) 
            {
                table[index].isDeleted = true;
                --numElements;
                return true;
            }
            index = nextIndex(index);
            if (index == startIndex) {
                break; 
            }
        }

        return false;
    }

    void print() const {
        for (size_t i = 0; i < tableSize; ++i) {
            if (table[i].isOccupied && !table[i].isDeleted) {
                std::cout << "[" << i << "]: " << table[i].value << "\n";
            }
            else if (table[i].isOccupied && table[i].isDeleted) {
                std::cout << "[" << i << "]: [DELETED]\n";
            }
            else {
                std::cout << "[" << i << "]: [EMPTY]\n";
            }
        }
    }

private:
    void rehash() {
        size_t newSize = tableSize * 2; 
        std::vector<Entry> oldTable = table;
        hashFunction = UniversalHash<T>(newSize);

        table.clear();
        table.resize(newSize);
        tableSize = newSize;
        numElements = 0;

        for (const auto& entry : oldTable) {
            if (entry.isOccupied && !entry.isDeleted) {
                insert(entry.value);
            }
        }
    }
};

