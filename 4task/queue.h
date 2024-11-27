#pragma once
#include <iostream>
#include <string>

// Узел очереди
class NodeQ {
public:
    int data;         // Значение узла
    NodeQ* next;      // Указатель на следующий узел

    NodeQ(int val);   // Конструктор узла
};

// Класс Очередь
class Queue {
private:
    NodeQ* head;      // Указатель на начало очереди
    NodeQ* tail;      // Указатель на конец очереди

    bool isEmpty() const;
    int peek() const;
public:
    // Конструкторы и деструктор
    Queue();                      // Конструктор
    ~Queue();                     // Деструктор

    // Операции с очередью
    void enqueue(int item);       // Добавить элемент в очередь
    int dequeue();                // Удалить элемент из очереди
    void print() const;           // Вывести содержимое очереди
    void writeToFile(const std::string& filename) const; // Записать очередь в файл
    void serializeToText(const std::string& filename) const;
    void deserializeFromText(const std::string& filename);
    void serializeToBinary(const std::string& filename) const;
    void deserializeFromBinary(const std::string& filename);

    // Управление памятью
    void clear();                 // Очистить очередь
};
