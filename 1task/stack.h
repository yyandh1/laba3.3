#pragma once
#include <string>
#include "node.h"

// Класс Стек
class Stack {
private:
    Node* top;       // Указатель на вершину стека

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