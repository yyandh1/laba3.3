#include "massive.h"
#include <iostream>
#include <fstream>
#include <stdexcept>

using namespace std;

// Конструктор
Array::Array(int initialCapacity) {
    if (initialCapacity <= 0) {
        throw invalid_argument("Вместимость должна быть положительным числом");
    }
    capacity = initialCapacity;
    size = 0;
    data = new int[capacity];
}

// Деструктор
Array::~Array() {
    delete[] data;
}

// Вспомогательная функция для увеличения емкости массива
void Array::resize() {
    capacity *= 2;
    int* newData = new int[capacity];
    for (int i = 0; i < size; ++i) {
        newData[i] = data[i];
    }
    delete[] data;
    data = newData;
}

// Добавить элемент в конец
void Array::append(int value) {
    if (size >= capacity) {
        resize();
    }
    data[size++] = value;
}

// Вставить элемент по индексу
void Array::insert(int index, int value) {
    if (index < 0 || index > size) {
        throw out_of_range("Индекс за пределами допустимого диапазона");
    }
    if (size >= capacity) {
        resize();
    }
    for (int i = size; i > index; --i) {
        data[i] = data[i - 1];
    }
    data[index] = value;
    ++size;
}

// Получить элемент по индексу
int Array::get(int index) const {
    if (index < 0 || index >= size) {
        throw out_of_range("Индекс за пределами допустимого диапазона");
    }
    return data[index];
}

// Удалить элемент по индексу
void Array::remove(int index) {
    if (index < 0 || index >= size) {
        throw out_of_range("Индекс за пределами допустимого диапазона");
    }
    for (int i = index; i < size - 1; ++i) {
        data[i] = data[i + 1];
    }
    --size;
}

// Заменить элемент по индексу
void Array::replace(int index, int value) {
    if (index < 0 || index >= size) {
        throw out_of_range("Индекс за пределами допустимого диапазона");
    }
    data[index] = value;
}

// Получить текущий размер массива
int Array::length() const {
    return size;
}

// Вывести массив в консоль
void Array::display() const {
    for (int i = 0; i < size; ++i) {
        cout << data[i] << " ";
    }
    cout << endl;
}

// Записать массив в файл
void Array::writeToFile(const std::string& filename) const {
    ofstream file(filename);
    if (!file.is_open()) {
        throw runtime_error("Ошибка при открытии файла для записи");
    }
    for (int i = 0; i < size; ++i) {
        file << data[i] << endl;
    }
    file.close();
}

// Очистить массив
void Array::free() {
    delete[] data;
    data = nullptr;
    size = 0;
    capacity = 0;
}

// Сохранить массив в текстовый файл
void Array::serializeToText(const std::string& filename) const {
    ofstream file(filename);

    if (!file.is_open()) {
        throw runtime_error("Ошибка при открытии текстового файла для записи");
    }

    // Сначала записываем размер массива
    file << size << endl;

    // Затем записываем элементы массива
    for (int i = 0; i < size; ++i) {
        file << data[i] << endl;
    }

    file.close();
}

// Загрузить массив из текстового файла
void Array::deserializeFromText(const std::string& filename) {
    ifstream file(filename);

    if (!file.is_open()) {
        throw runtime_error("Ошибка при открытии текстового файла для чтения");
    }

    // Считываем размер массива
    int newSize;
    file >> newSize;

    if (newSize <= 0) {
        throw runtime_error("Некорректный размер массива в файле");
    }

    // Освобождаем старые данные и создаем новый массив
    delete[] data;
    capacity = newSize;
    size = newSize;
    data = new int[capacity];

    // Считываем элементы массива
    for (int i = 0; i < size; ++i) {
        if (!(file >> data[i])) {
            throw runtime_error("Ошибка при чтении элементов массива из файла");
        }
    }

    file.close();
}

// Сохранить массив в бинарный файл
void Array::serializeToBinary(const std::string& filename) const {
    ofstream file(filename, ios::binary);

    if (!file.is_open()) {
        throw runtime_error("Ошибка при открытии бинарного файла для записи");
    }

    // Сначала записываем размер массива
    file.write(reinterpret_cast<const char*>(&size), sizeof(size));

    // Затем записываем элементы массива
    file.write(reinterpret_cast<const char*>(data), size * sizeof(int));

    file.close();
}

// Загрузить массив из бинарного файла
void Array::deserializeFromBinary(const std::string& filename) {
    ifstream file(filename, ios::binary);

    if (!file.is_open()) {
        throw runtime_error("Ошибка при открытии бинарного файла для чтения");
    }

    // Считываем размер массива
    int newSize;
    file.read(reinterpret_cast<char*>(&newSize), sizeof(newSize));

    if (newSize <= 0) {
        throw runtime_error("Некорректный размер массива в файле");
    }

    // Освобождаем старые данные и создаем новый массив
    delete[] data;
    capacity = newSize;
    size = newSize;
    data = new int[capacity];

    // Считываем элементы массива
    file.read(reinterpret_cast<char*>(data), size * sizeof(int));

    file.close();
}