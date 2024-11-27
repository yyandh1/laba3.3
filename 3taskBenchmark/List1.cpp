#include "List1.h"
#include <iostream>
#include <sstream>
#include <fstream>

using namespace std;

// Конструктор
ListOne::ListOne() : head(nullptr) {}

// Деструктор
ListOne::~ListOne() {
    clear();
}

// Добавить элемент в начало
void ListOne::addToHead(int value) {
    head = new Node(value, head);
}

// Добавить элемент в конец
void ListOne::addToTail(int value) {
    Node* newNode = new Node(value);

    if (!head) {
        head = newNode;
    } else {
        Node* temp = head;
        while (temp->next) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}

// Удалить элемент с начала
void ListOne::removeHead() {
    if (head) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
}

// Удалить элемент с конца
void ListOne::removeTail() {
    if (!head) return;

    if (!head->next) {
        delete head;
        head = nullptr;
    } else {
        Node* temp = head;
        while (temp->next->next) {
            temp = temp->next;
        }
        delete temp->next;
        temp->next = nullptr;
    }
}

// Удалить элемент по значению
void ListOne::removeByValue(int value) {
    if (!head) return;

    if (head->data == value) {
        Node* temp = head;
        head = head->next;
        delete temp;
        return;
    }

    Node* temp = head;
    while (temp->next && temp->next->data != value) {
        temp = temp->next;
    }

    if (temp->next) {
        Node* toDelete = temp->next;
        temp->next = temp->next->next;
        delete toDelete;
    }
}

// Поиск элемента по значению
bool ListOne::search(int value) const {
    Node* temp = head;
    while (temp) {
        if (temp->data == value) {
            return true;
        }
        temp = temp->next;
    }
    return false;
}

// Печать всех элементов
void ListOne::print() const {
    Node* temp = head;
    while (temp) {
        cout << temp->data << " ";
        temp = temp->next;
    }
    cout << endl;
}

// Очистить список
void ListOne::clear() {
    while (head) {
        removeHead();
    }
}

// Сохранить список в файл
void ListOne::writeToFile(const std::string& filename) const {
    ofstream file(filename);

    if (!file.is_open()) {
        cerr << "Ошибка при открытии файла для записи" << endl;
        return;
    }

    Node* temp = head;
    while (temp) {
        file << temp->data << endl;
        temp = temp->next;
    }

    file.close();
}