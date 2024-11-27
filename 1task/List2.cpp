#include "List2.h"
#include <iostream>
#include <sstream>
#include <fstream>

using namespace std;

// Конструктор
DoubleList::DoubleList() : head(nullptr), tail(nullptr) {}

// Деструктор
DoubleList::~DoubleList() {
    clear();
}

// Добавить элемент в начало
void DoubleList::addToHead(int value) {
    NodeL2* newNode = new NodeL2(value, head);

    if (head) {
        head->previous = newNode;
    } else {
        tail = newNode;
    }
    head = newNode;
}

// Добавить элемент в конец
void DoubleList::addToTail(int value) {
    NodeL2* newNode = new NodeL2(value, nullptr, tail);

    if (tail) {
        tail->next = newNode;
    } else {
        head = newNode;
    }
    tail = newNode;
}

// Удалить элемент с начала
void DoubleList::removeFromHead() {
    if (!head) return;

    NodeL2* temp = head;
    head = head->next;

    if (head) {
        head->previous = nullptr;
    } else {
        tail = nullptr;
    }
    delete temp;
}

// Удалить элемент с конца
void DoubleList::removeFromTail() {
    if (!tail) return;

    NodeL2* temp = tail;
    tail = tail->previous;

    if (tail) {
        tail->next = nullptr;
    } else {
        head = nullptr;
    }
    delete temp;
}

// Удалить элемент по значению
void DoubleList::removeByValue(int value) {
    NodeL2* temp = head;

    while (temp) {
        if (temp->data == value) {
            if (temp->previous) {
                temp->previous->next = temp->next;
            } else {
                head = temp->next; // Удаляемый элемент - это голова
            }

            if (temp->next) {
                temp->next->previous = temp->previous;
            } else {
                tail = temp->previous; // Удаляемый элемент - это хвост
            }

            delete temp;
            return;
        }
        temp = temp->next;
    }
}

// Найти элемент по значению
bool DoubleList::find(int value) const {
    NodeL2* temp = head;
    while (temp) {
        if (temp->data == value) {
            return true;
        }
        temp = temp->next;
    }
    return false;
}

// Печать всех элементов
void DoubleList::print() const {
    NodeL2* temp = head;
    while (temp) {
        cout << temp->data << " ";
        temp = temp->next;
    }
    cout << endl;
}

// Очистить список
void DoubleList::clear() {
    while (head) {
        removeFromHead();
    }
}

// Сохранить список в файл
void DoubleList::writeToFile(const std::string& filename) const {
    ofstream file(filename);

    if (!file.is_open()) {
        cerr << "Ошибка при открытии файла для записи" << endl;
        return;
    }

    NodeL2* temp = head;
    while (temp) {
        file << temp->data << endl;
        temp = temp->next;
    }

    file.close();
}