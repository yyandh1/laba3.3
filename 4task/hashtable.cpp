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

// Сериализация хеш-таблицы в текстовый файл
void HashTable::serializeToText(const std::string& filename) const {
    std::ofstream file(filename);

    if (!file.is_open()) {
        throw std::runtime_error("Ошибка при открытии текстового файла для записи");
    }

    for (int i = 0; i < TABLE_SIZE; ++i) {
        Node* current = table[i];
        while (current) {
            file << current->key << ":" << current->value << "\n"; // Сохраняем ключ:значение
            current = current->next;
        }
    }

    file.close();
}

// Десериализация хеш-таблицы из текстового файла
void HashTable::deserializeFromText(const std::string& filename) {
    std::ifstream file(filename);

    if (!file.is_open()) {
        throw std::runtime_error("Ошибка при открытии текстового файла для чтения");
    }

    clear(); // Очищаем текущую таблицу перед загрузкой новых данных

    std::string line;
    while (std::getline(file, line)) {
        size_t delimiterPos = line.find(':');
        if (delimiterPos == std::string::npos) {
            throw std::runtime_error("Неверный формат данных в текстовом файле");
        }
        std::string key = line.substr(0, delimiterPos);
        std::string value = line.substr(delimiterPos + 1);
        insert(key, value);
    }

    file.close();
}

// Сериализация хеш-таблицы в бинарный файл
void HashTable::serializeToBinary(const std::string& filename) const {
    std::ofstream file(filename, std::ios::binary);

    if (!file.is_open()) {
        throw std::runtime_error("Ошибка при открытии бинарного файла для записи");
    }

    for (int i = 0; i < TABLE_SIZE; ++i) {
        Node* current = table[i];
        while (current) {
            size_t keySize = current->key.size();
            size_t valueSize = current->value.size();

            // Сохраняем длины строк, сами строки и их значения
            file.write(reinterpret_cast<const char*>(&keySize), sizeof(keySize));
            file.write(current->key.data(), keySize);
            file.write(reinterpret_cast<const char*>(&valueSize), sizeof(valueSize));
            file.write(current->value.data(), valueSize);

            current = current->next;
        }
    }

    file.close();
}

// Десериализация хеш-таблицы из бинарного файла
void HashTable::deserializeFromBinary(const std::string& filename) {
    std::ifstream file(filename, std::ios::binary);

    if (!file.is_open()) {
        throw std::runtime_error("Ошибка при открытии бинарного файла для чтения");
    }

    clear(); // Очищаем текущую таблицу перед загрузкой новых данных

    while (file.peek() != EOF) {
        size_t keySize, valueSize;
        file.read(reinterpret_cast<char*>(&keySize), sizeof(keySize));

        std::string key(keySize, '\0');
        file.read(&key[0], keySize);

        file.read(reinterpret_cast<char*>(&valueSize), sizeof(valueSize));
        std::string value(valueSize, '\0');
        file.read(&value[0], valueSize);

        insert(key, value);
    }

    file.close();
}