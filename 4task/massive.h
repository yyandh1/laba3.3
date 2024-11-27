#pragma once
#include <iostream>
#include <string>

class Array {
private:
    int* data;          // Динамический массив данных
    int size;           // Текущий размер массива
    int capacity;       // Максимальная вместимость массива

    void resize();      // Вспомогательная функция для увеличения емкости массива

public:
    // Конструкторы и деструктор
    Array(int initialCapacity = 10); // Конструктор с параметром по умолчанию
    ~Array();                        // Деструктор

    // Методы для работы с массивом
    void append(int value);               // Добавить элемент в конец
    void insert(int index, int value);    // Вставить элемент по индексу
    int get(int index) const;             // Получить элемент по индексу
    void remove(int index);               // Удалить элемент по индексу
    void replace(int index, int value);   // Заменить элемент по индексу
    int length() const;                   // Получить текущий размер массива
    void display() const;                 // Вывести массив в консоль
    void writeToFile(const std::string& filename) const; // Записать массив в файл
    void serializeToText(const std::string& filename) const;
    void deserializeFromText(const std::string& filename);
    void serializeToBinary(const std::string& filename) const;
    void deserializeFromBinary(const std::string& filename);
    // Управление памятью
    void free();                          // Очистить массив
};