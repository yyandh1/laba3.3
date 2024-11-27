#include "hashtable.h"
#include <iostream>
#include <fstream>

HashTable::HashTable() {
    for (int i = 0; i < TABLE_SIZE; ++i) {
        table[i] = nullptr;
    }
}

HashTable::~HashTable() {
    clear();
}

int HashTable::hashFunction(const std::string& key) const {
    int hash = 0;
    for (char ch : key) {
        hash += ch;
    }
    return hash % TABLE_SIZE;
}

void HashTable::insert(const std::string& key, const std::string& value) {
    int index = hashFunction(key);
    Node* newNode = new Node(key, value);

    if (!table[index]) {
        table[index] = newNode;
    } else {
        Node* current = table[index];
        while (current) {
            if (current->key == key) {
                current->value = value; // Обновляем значение, если ключ найден
                delete newNode;
                return;
            }
            if (!current->next) break;
            current = current->next;
        }
        current->next = newNode;
    }
}

std::string HashTable::get(const std::string& key) const {
    int index = hashFunction(key);
    Node* current = table[index];

    while (current) {
        if (current->key == key) return current->value;
        current = current->next;
    }
    return "Ключ не найден";
}

void HashTable::remove(const std::string& key) {
    int index = hashFunction(key);
    Node* current = table[index];
    Node* prev = nullptr;

    while (current) {
        if (current->key == key) {
            if (prev) {
                prev->next = current->next;
            } else {
                table[index] = current->next;
            }
            delete current;
            return;
        }
        prev = current;
        current = current->next;
    }
}

void HashTable::print() const {
    for (int i = 0; i < TABLE_SIZE; ++i) {
        std::cout << "Index " << i << ": ";
        Node* current = table[i];
        while (current) {
            std::cout << "[" << current->key << ": " << current->value << "] ";
            current = current->next;
        }
        std::cout << std::endl;
    }
}

void HashTable::clear() {
    for (int i = 0; i < TABLE_SIZE; ++i) {
        Node* current = table[i];
        while (current) {
            Node* toDelete = current;
            current = current->next;
            delete toDelete;
        }
        table[i] = nullptr;
    }
}

void HashTable::writeToFile(const std::string& filename) const {
    std::ofstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Ошибка при открытии файла для записи" << std::endl;
        return;
    }

    for (int i = 0; i < TABLE_SIZE; ++i) {
        Node* current = table[i];
        while (current) {
            file << "[" << current->key << ": " << current->value << "] ";
            current = current->next;
        }
        file << std::endl;
    }

    file.close();
}