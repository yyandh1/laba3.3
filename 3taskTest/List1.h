#pragma once
#include <string>

class ListOne {
private:
    struct Node {
        int data;
        Node* next;

        Node(int value, Node* nextNode = nullptr)
            : data(value), next(nextNode) {}
    };

    Node* head; // Указатель на начало списка

public:
    ListOne();             // Конструктор
    ~ListOne();            // Деструктор

    void addToHead(int value);       // Добавить элемент в начало
    void addToTail(int value);       // Добавить элемент в конец
    void removeHead();               // Удалить элемент с начала
    void removeTail();               // Удалить элемент с конца
    void removeByValue(int value);   // Удалить элемент по значению
    bool search(int value) const;    // Поиск элемента по значению
    void print() const;              // Печать всех элементов
    void clear();                    // Очистить список
    void writeToFile(const std::string& filename) const; // Сохранить список в файл
};
