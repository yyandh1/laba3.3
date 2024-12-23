#include "queue.h"
#include <iostream>
#include <fstream>
#include <stdexcept>

using namespace std;

// Конструктор узла
NodeQ::NodeQ(int val) : data(val), next(nullptr) {}

// Конструктор очереди
Queue::Queue() : head(nullptr), tail(nullptr) {}

// Деструктор очереди
Queue::~Queue() {
    clear();
}

// Добавить элемент в очередь
void Queue::enqueue(int item) {
    NodeQ* newNode = new NodeQ(item);
    if (tail == nullptr) {
        head = tail = newNode;
    } else {
        tail->next = newNode;
        tail = newNode;
    }
}

// Удалить элемент из очереди
int Queue::dequeue() {
    if (head == nullptr) {
        throw underflow_error("Очередь пуста");
    }
    NodeQ* temp = head;
    int item = head->data;
    head = head->next;
    if (head == nullptr) {
        tail = nullptr;
    }
    delete temp;
    return item;
}

// Вывести содержимое очереди
void Queue::print() const {
    if (head == nullptr) {
        cout << "Очередь пуста" << endl;
        return;
    }
    NodeQ* temp = head;
    cout << "Очередь: ";
    while (temp != nullptr) {
        cout << temp->data << " ";
        temp = temp->next;
    }
    cout << endl;
}

// Записать очередь в файл
void Queue::writeToFile(const std::string& filename) const {
    ofstream file(filename);
    if (!file.is_open()) {
        throw runtime_error("Ошибка при открытии файла для записи");
    }
    NodeQ* temp = head;
    while (temp != nullptr) {
        file << temp->data << endl;
        temp = temp->next;
    }
    file.close();
}

// Очистить очередь
void Queue::clear() {
    while (head != nullptr) {
        dequeue();
    }
}

void Queue::serializeToText(const std::string& filename) const {
    ofstream file(filename);

    if (!file.is_open()) {
        throw runtime_error("Ошибка при открытии текстового файла для записи");
    }

    NodeQ* temp = head;

    // Записываем элементы очереди в файл
    while (temp != nullptr) {
        file << temp->data << endl;
        temp = temp->next;
    }

    file.close();
}

// Загрузить очередь из текстового файла
void Queue::deserializeFromText(const std::string& filename) {
    ifstream file(filename);

    if (!file.is_open()) {
        throw runtime_error("Ошибка при открытии текстового файла для чтения");
    }

    clear(); // Очищаем текущую очередь

    int value;
    while (file >> value) {
        enqueue(value);
    }

    file.close();
}

// Сохранить очередь в бинарный файл
void Queue::serializeToBinary(const std::string& filename) const {
    ofstream file(filename, ios::binary);

    if (!file.is_open()) {
        throw runtime_error("Ошибка при открытии бинарного файла для записи");
    }

    NodeQ* temp = head;

    // Записываем элементы очереди в бинарный файл
    while (temp != nullptr) {
        file.write(reinterpret_cast<const char*>(&temp->data), sizeof(temp->data));
        temp = temp->next;
    }

    file.close();
}

// Загрузить очередь из бинарного файла
void Queue::deserializeFromBinary(const std::string& filename) {
    ifstream file(filename, ios::binary);

    if (!file.is_open()) {
        throw runtime_error("Ошибка при открытии бинарного файла для чтения");
    }

    clear(); // Очищаем текущую очередь

    int value;
    while (file.read(reinterpret_cast<char*>(&value), sizeof(value))) {
        enqueue(value);
    }

    file.close();
}

// Проверка на пустоту
bool Queue::isEmpty() const {
    return head == nullptr;
}

// Получение элемента в начале очереди
int Queue::peek() const {
    if (head == nullptr) {
        throw underflow_error("Очередь пуста");
    }
    return head->data;
}