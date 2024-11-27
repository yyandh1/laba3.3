#pragma once
#include <string>

// Узел стека
class NodeS {
public:
    int data;         // Значение узла
    NodeS* next;      // Указатель на следующий узел

    NodeS(int value); // Конструктор узла
};

// Класс Стек
class Stack {
private:
    NodeS* top;       // Указатель на вершину стека

public:
    // Конструкторы и деструктор
    Stack();                      // Конструктор
    ~Stack();                     // Деструктор

    // Операции со стеком
    void push(int value);         // Добавить элемент на вершину стека
    void pop();                   // Удалить элемент с вершины стека
    void print() const;           // Вывести содержимое стека
    void writeToFile(const std::string& filename) const; // Записать стек в файл

    // Управление памятью
    void clear();                 // Очистить стек
};
