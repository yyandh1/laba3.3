#include "gtest/gtest.h"
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

// Тест конструктора (положительная и отрицательная вместимость)
TEST(ArrayTest, Constructor) {
    // Проверка корректного создания с положительной вместимостью
    Array arr(5);
    EXPECT_EQ(arr.length(), 0);  // Размер массива после создания должен быть 0

    // Проверка исключения на некорректную вместимость
    EXPECT_THROW(Array arr(-1), std::invalid_argument);
    EXPECT_THROW(Array arr(0), std::invalid_argument);
}

// Тест метода append (добавление элементов в конец)
TEST(ArrayTest, Append) {
    Array arr(2);
    arr.append(10);
    arr.append(20);
    arr.append(30);  // Это приведет к увеличению емкости

    EXPECT_EQ(arr.length(), 3);  // Размер массива должен быть 3
    EXPECT_EQ(arr.get(0), 10);   // Первый элемент должен быть 10
    EXPECT_EQ(arr.get(1), 20);   // Второй элемент должен быть 20
    EXPECT_EQ(arr.get(2), 30);   // Третий элемент должен быть 30
}

// Тест метода insert (вставка элемента по индексу)
TEST(ArrayTest, Insert) {
    Array arr(2);
    arr.append(10);
    arr.append(20);

    arr.insert(1, 15);  // Вставляем 15 на вторую позицию

    EXPECT_EQ(arr.length(), 3);  // Размер массива должен быть 3
    EXPECT_EQ(arr.get(0), 10);   // Первый элемент должен быть 10
    EXPECT_EQ(arr.get(1), 15);   // Второй элемент должен быть 15
    EXPECT_EQ(arr.get(2), 20);   // Третий элемент должен быть 20

    // Проверка на выход за пределы диапазона
    EXPECT_THROW(arr.insert(4, 25), std::out_of_range);
}

// Тест метода get (получение элемента по индексу)
TEST(ArrayTest, Get) {
    Array arr(3);
    arr.append(10);
    arr.append(20);
    arr.append(30);

    EXPECT_EQ(arr.get(0), 10);  // Должен вернуть 10
    EXPECT_EQ(arr.get(1), 20);  // Должен вернуть 20
    EXPECT_EQ(arr.get(2), 30);  // Должен вернуть 30

    // Проверка выхода за пределы диапазона
    EXPECT_THROW(arr.get(3), std::out_of_range);
}

// Тест метода remove (удаление элемента по индексу)
TEST(ArrayTest, Remove) {
    Array arr(3);
    arr.append(10);
    arr.append(20);
    arr.append(30);

    arr.remove(1);  // Удаляем второй элемент (20)

    EXPECT_EQ(arr.length(), 2);  // Размер массива должен быть 2
    EXPECT_EQ(arr.get(0), 10);   // Первый элемент должен быть 10
    EXPECT_EQ(arr.get(1), 30);   // Второй элемент должен быть 30

    // Проверка выхода за пределы диапазона
    EXPECT_THROW(arr.remove(2), std::out_of_range);
}

// Тест метода replace (замена элемента по индексу)
TEST(ArrayTest, Replace) {
    Array arr(3);
    arr.append(10);
    arr.append(20);
    arr.append(30);

    arr.replace(1, 25);  // Заменяем второй элемент на 25

    EXPECT_EQ(arr.get(1), 25);  // Второй элемент должен быть 25

    // Проверка выхода за пределы диапазона
    EXPECT_THROW(arr.replace(3, 35), std::out_of_range);
}

// Тест метода display (вывод массива в консоль)
TEST(ArrayTest, Display) {
    Array arr(3);
    arr.append(10);
    arr.append(20);
    arr.append(30);

    // Перехватываем вывод в строковый поток
    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());  // Перенаправляем cout

    arr.display();  // Печатаем массив

    std::cout.rdbuf(old);  // Восстанавливаем старый поток

    // Проверяем, что вывод соответствует ожиданиям
    EXPECT_EQ(buffer.str(), "10 20 30 \n");
}

// Тест метода writeToFile (запись массива в файл)
TEST(ArrayTest, WriteToFile) {
    Array arr(3);
    arr.append(10);
    arr.append(20);
    arr.append(30);

    arr.writeToFile("test_output.txt");

    // Проверка, что файл существует и содержит правильные данные
    std::ifstream file("test_output.txt");
    ASSERT_TRUE(file.is_open());

    int value;
    file >> value;
    EXPECT_EQ(value, 10);  // Первый элемент массива должен быть 10

    file >> value;
    EXPECT_EQ(value, 20);  // Второй элемент массива должен быть 20

    file >> value;
    EXPECT_EQ(value, 30);  // Третий элемент массива должен быть 30

    file.close();
    remove("test_output.txt");  // Удаляем файл после теста
}

// Тест метода free (очистка массива)
TEST(ArrayTest, Free) {
    Array arr(3);
    arr.append(10);
    arr.append(20);
    arr.append(30);

    arr.free();  // Очищаем массив

    EXPECT_EQ(arr.length(), 0);  // Размер массива должен быть 0
}

// Тест метода resize (увеличение вместимости)
TEST(ArrayTest, Resize) {
    Array arr(2);
    arr.append(10);
    arr.append(20);
    arr.append(30);  // Это вызовет увеличение емкости массива

    EXPECT_EQ(arr.length(), 3);  // Размер массива должен быть 3
    EXPECT_EQ(arr.get(0), 10);   // Первый элемент должен быть 10
    EXPECT_EQ(arr.get(1), 20);   // Второй элемент должен быть 20
    EXPECT_EQ(arr.get(2), 30);   // Третий элемент должен быть 30
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}