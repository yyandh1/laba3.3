#include "stack.h"
#include <iostream>
#include <fstream>

using namespace std;

// Конструктор узла
NodeS::NodeS(int value) : data(value), next(nullptr) {}

// Конструктор стека
Stack::Stack() : top(nullptr) {}

// Деструктор стека
Stack::~Stack() {
    clear();
}

// Добавить элемент на вершину стека
void Stack::push(int value) {
    NodeS* newNode = new NodeS(value);
    newNode->next = top; // Новый узел указывает на текущую вершину
    top = newNode;       // Новый узел становится вершиной
}

// Удалить элемент с вершины стека
void Stack::pop() {
    if (top == nullptr) {
        throw underflow_error("Стек пуст");
    }
    NodeS* temp = top;
    top = top->next;
    delete temp;
}

// Вывести содержимое стека
void Stack::print() const {
    if (top == nullptr) {
        cout << "Стек пуст" << endl;
        return;
    }
    NodeS* temp = top;
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

    NodeS* temp = top;
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

void Stack::serializeToText(const std::string& filename) const {
    ofstream file(filename);
    if (!file.is_open()) {
        throw runtime_error("Ошибка при открытии текстового файла для записи");
    }

    NodeS* temp = top;
    while (temp != nullptr) {
        file << temp->data << "\n"; // Сохраняем каждый элемент на новой строке
        temp = temp->next;
    }

    file.close();
}

// Десериализация стека из текстового файла
void Stack::deserializeFromText(const std::string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        throw runtime_error("Ошибка при открытии текстового файла для чтения");
    }

    clear(); // Очищаем стек перед загрузкой новых данных

    int value;
    while (file >> value) { // Читаем числа построчно
        push(value);        // Добавляем в стек
    }

    file.close();
}

// Сериализация стека в бинарный файл
void Stack::serializeToBinary(const std::string& filename) const {
    ofstream file(filename, ios::binary);
    if (!file.is_open()) {
        throw runtime_error("Ошибка при открытии бинарного файла для записи");
    }

    NodeS* temp = top;
    while (temp != nullptr) {
        file.write(reinterpret_cast<const char*>(&temp->data), sizeof(temp->data));
        temp = temp->next;
    }

    file.close();
}

// Десериализация стека из бинарного файла
void Stack::deserializeFromBinary(const std::string& filename) {
    ifstream file(filename, ios::binary);
    if (!file.is_open()) {
        throw runtime_error("Ошибка при открытии бинарного файла для чтения");
    }

    clear(); // Очищаем стек перед загрузкой новых данных

    int value;
    while (file.read(reinterpret_cast<char*>(&value), sizeof(value))) {
        push(value); // Добавляем в стек
    }

    file.close();
}