#pragma once
#include <iostream>
#include <string>
#include "node.h"

// Класс Очередь
class Queue {
private:
    Node* head;      // Указатель на начало очереди
    Node* tail;      // Указатель на конец очереди

public:
    // Конструкторы и деструктор
    Queue();                      // Конструктор
    ~Queue();                     // Деструктор

    // Операции с очередью
    void enqueue(int item);       // Добавить элемент в очередь
    int dequeue();                // Удалить элемент из очереди
    void print() const;           // Вывести содержимое очереди
    void writeToFile(const std::string& filename) const; // Записать очередь в файл

    // Управление памятью
    void clear();                 // Очистить очередь
};
