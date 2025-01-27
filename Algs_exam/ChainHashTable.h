#pragma once

#include <vector>
#include <functional>
#include <list> 

#include "UniversalHash.h"

template<typename Key, typename Value, typename Container = std::list<std::pair<Key, Value>>>
class ChainHashTable {
private:
    using Bucket = Container;
    std::vector<Bucket> table;
    UniversalHash<Key> hashFunction;
    size_t tableSize;

public:

    ChainHashTable(size_t size): 
        table(size), hashFunction(size), tableSize(size) 
    {
    }

    void insert(const Key& key, const Value& value) 
    {
        unsigned int index = hashFunction(key) % tableSize;
        for (auto& pair : table[index]) 
        {
            if (pair.first == key) {
                pair.second = value;
                return;
            }
        }
        table[index].push_back({ key, value });
    }

    bool find(const Key& key, Value& result) const 
    {
        unsigned int index = hashFunction(key) % tableSize;
        for (const auto& pair : table[index]) {
            if (pair.first == key) {
                result = pair.second;
                return true;
            }
        }
        return false;
    }

    bool erase(const Key& key) 
    {
        unsigned int index = hashFunction(key) % tableSize; 
        auto& bucket = table[index];
        for (auto it = bucket.begin(); it != bucket.end(); ++it) 
        {
            if (it->first == key) 
            {
                bucket.erase(it);
                return true;
            }
        }
        return false;
    }

    void print() const 
    {
        for (size_t i = 0; i < tableSize; ++i) 
        {
            std::cout << "Bucket " << i << ": ";
            for (const auto& pair : table[i]) 
            {
                std::cout << "{" << pair.first << ": " << pair.second << "} ";
            }
            std::cout << "\n";
        }
    }
};
