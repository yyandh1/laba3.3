#include <gtest/gtest.h>
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

// Тестирование функции insert
TEST(HashTableTest, InsertAndGet) {
    HashTable ht;
    ht.insert("key1", "value1");
    ht.insert("key2", "value2");

    // Проверка правильности вставленных значений
    EXPECT_EQ(ht.get("key1"), "value1");
    EXPECT_EQ(ht.get("key2"), "value2");

    // Проверка на несуществующий ключ
    EXPECT_EQ(ht.get("nonexistent"), "Ключ не найден");
}

// Тестирование функции remove
TEST(HashTableTest, Remove) {
    HashTable ht;
    ht.insert("key1", "value1");
    ht.insert("key2", "value2");

    // Удаляем один ключ
    ht.remove("key1");

    // Проверка, что ключ удален
    EXPECT_EQ(ht.get("key1"), "Ключ не найден");
    EXPECT_EQ(ht.get("key2"), "value2");
}

// Тестирование функции обновления значения
TEST(HashTableTest, UpdateValue) {
    HashTable ht;
    ht.insert("key1", "value1");
    ht.insert("key1", "value2");  // Обновляем значение

    EXPECT_EQ(ht.get("key1"), "value2");
}

// Тестирование функции print (нельзя протестировать напрямую, но можно проверить вывод)
TEST(HashTableTest, Print) {
    HashTable ht;
    ht.insert("key1", "value1");
    ht.insert("key2", "value2");

    testing::internal::CaptureStdout();
    ht.print();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_TRUE(output.find("key1") != std::string::npos);
    EXPECT_TRUE(output.find("key2") != std::string::npos);
}

// Тестирование функции clear
TEST(HashTableTest, Clear) {
    HashTable ht;
    ht.insert("key1", "value1");
    ht.insert("key2", "value2");

    ht.clear();

    // Проверка после очистки
    EXPECT_EQ(ht.get("key1"), "Ключ не найден");
    EXPECT_EQ(ht.get("key2"), "Ключ не найден");
}

// Тестирование записи в файл
TEST(HashTableTest, WriteToFile) {
    HashTable ht;
    ht.insert("key1", "value1");
    ht.insert("key2", "value2");

    // Путь к временному файлу
    const std::string filename = "test.txt";
    ht.writeToFile(filename);

    std::ifstream file(filename);
    std::string line;
    bool foundKey1 = false;
    bool foundKey2 = false;

    while (std::getline(file, line)) {
        if (line.find("key1") != std::string::npos)
            foundKey1 = true;
        if (line.find("key2") != std::string::npos)
            foundKey2 = true;
    }

    EXPECT_TRUE(foundKey1);
    EXPECT_TRUE(foundKey2);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}