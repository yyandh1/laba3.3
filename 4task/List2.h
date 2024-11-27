#pragma once
#include <string>

class DoubleList {
private:
    struct Node {
        int data;
        Node* next;
        Node* previous;

        Node(int value, Node* nextNode = nullptr, Node* prevNode = nullptr)
            : data(value), next(nextNode), previous(prevNode) {}
    };

    Node* head; // Указатель на начало списка
    Node* tail; // Указатель на конец списка

public:
    DoubleList();                      // Конструктор
    ~DoubleList();                     // Деструктор

    void addToHead(int value);         // Добавить элемент в начало
    void addToTail(int value);         // Добавить элемент в конец
    void removeFromHead();             // Удалить элемент с начала
    void removeFromTail();             // Удалить элемент с конца
    void removeByValue(int value);     // Удалить элемент по значению
    bool find(int value) const;        // Найти элемент по значению
    void print() const;                // Печать всех элементов
    void clear();                      // Очистить список
    void writeToFile(const std::string& filename) const; // Сохранить список в файл
    void serializeToText(const std::string& filename) const;
    void deserializeFromText(const std::string& filename);
    void serializeToBinary(const std::string& filename) const;
    void deserializeFromBinary(const std::string& filename);
};
