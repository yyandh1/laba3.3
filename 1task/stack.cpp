#include "stack.h"
#include <iostream>
#include <fstream>
#include <stdexcept>

using namespace std;

// Конструктор стека
Stack::Stack() : top(nullptr) {}

// Деструктор стека
Stack::~Stack() {
    clear();
}

// Добавить элемент на вершину стека
void Stack::push(int value) {
    Node* newNode = new Node(value);
    newNode->next = top; // Новый узел указывает на текущую вершину
    top = newNode;       // Новый узел становится вершиной
}

// Удалить элемент с вершины стека
void Stack::pop() {
    if (top == nullptr) {
        throw underflow_error("Стек пуст");
    }
    Node* temp = top;
    top = top->next;
    delete temp;
}

// Вывести содержимое стека
void Stack::print() const {
    if (top == nullptr) {
        cout << "Стек пуст" << endl;
        return;
    }
    Node* temp = top;
    cout << "Элементы стека: ";
    while (temp != nullptr) {
        cout << temp->data << " ";
        temp = temp->next;
    }
    cout << endl;
}

// Записать стек в файл
void Stack::writeToFile(const std::string& filename) const {
    ofstream file(filename);
    if (!file.is_open()) {
        throw runtime_error("Ошибка при открытии файла для записи");
    }

    Node* temp = top;
    while (temp != nullptr) {
        file << temp->data << endl;
        temp = temp->next;
    }
    file.close();
}

// Очистить стек
void Stack::clear() {
    while (top != nullptr) {
        pop();
    }
}