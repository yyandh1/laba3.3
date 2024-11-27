#pragma once
#include <string>

using namespace std;
const int TABLE_SIZE = 10;

class HashTable {
private:
    struct Node {
        string key;
        string value;
        Node* next;

        Node(const string& k, const string& v, Node* n = nullptr)
            : key(k), value(v), next(n) {}
    };

    Node* table[TABLE_SIZE];

    int hashFunction(const string& key) const;

public:
    HashTable();
    ~HashTable();

    void insert(const string& key, const string& value);
    string get(const string& key) const;
    void remove(const string& key);
    void print() const;
    void clear();
    void writeToFile(const string& filename) const;
    void serializeToText(const std::string& filename) const;
    void deserializeFromText(const std::string& filename);
    void serializeToBinary(const std::string& filename) const;
    void deserializeFromBinary(const std::string& filename);
};
