#ifndef HASH_MAP_H
#define HASH_MAP_H

#include <cstdint>
#include <vector>
#include <tuple>

struct Node
{  
    int value;
    std::string key; 

    void operator()(const std::string& k, const int& v) {key = k; value = v;}
};

class HashMap
{
private:
    std::vector<std::vector<Node>> table;
    size_t size_of;
    size_t num_duplicates;

    uint64_t fnv1a_64(const char* data, size_t len) 
    {
        const uint64_t FNV_prime = 1099511628211ULL;
        uint64_t hash = 14695981039346656037ULL; 

        for (size_t i = 0; i < len; ++i) 
        {
            hash ^= static_cast<uint8_t>(data[i]);
            hash *= FNV_prime;
        }
        return hash;
    }

public:
    HashMap(size_t sz) : size_of(sz)
    {  table.resize(size_of);  num_duplicates = 0; }
    HashMap()
    {
        size_of = 100;
        table.resize(size_of);
        num_duplicates = 0;
    }

    void rescale(size_t new_size) 
    {
        size_of = new_size;
        table.resize(size_of);
    }

    size_t scale(){return size_of;}

    size_t duplicateScale(){return num_duplicates;}

    void stow(std::string key, int val)
    {
        const char* data = key.c_str();
        int hash = fnv1a_64(data, key.length()) % size_of;

        Node node; node(key, val);
        table[hash].push_back(node);

        if(table[hash].size() > 1) num_duplicates++; // Duplicate added
    }

    std::vector<std::tuple<std::string, int>> duplicates()
    {
        // Base case
        if(num_duplicates < 1) return std::vector<std::tuple<std::string, int>>{{"NADA", -1}};

        // Assuming we have duplicates
        std::vector<std::tuple<std::string, int>> dups;
        for(auto& hash : table)
            if(hash.size() > 1)
            {
                for(int i = 0; i < hash.size(); i++)
                    for(int j = i + 1; j < hash.size(); j++)
                        if(hash[i].key == hash[j].key)
                        {
                            dups.push_back({hash[i].key, hash[i].value});
                            dups.push_back({hash[j].key, hash[j].value});
                        }
            }

        return dups;
    }

    std::string toString()
    {
        std::string str = "";

        for(auto& t : table)
            for(auto& n : t)
                str += std::to_string(n.value) + " " + n.key + '\n';
        
        return str;
    }
};
#endif