#include <gtest/gtest.h>
#include "stack.h"
#include <iostream>
#include <fstream>
#include <stdexcept>

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

// Тест: создание стека
TEST(StackTest, StackCreation) {
    Stack stack;
    EXPECT_NO_THROW(stack.print()); // Печать пустого стека
}

// Тест: добавление элементов в стек
TEST(StackTest, PushElements) {
    Stack stack;
    stack.push(10);
    stack.push(20);
    stack.push(30);

    testing::internal::CaptureStdout(); // Перехват вывода в консоль
    stack.print();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "Элементы стека: 30 20 10 \n"); // Проверяем порядок
}

// Тест: удаление элементов из стека
TEST(StackTest, PopElements) {
    Stack stack;
    stack.push(10);
    stack.push(20);
    stack.pop();

    testing::internal::CaptureStdout();
    stack.print();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "Элементы стека: 10 \n"); // Проверяем оставшийся элемент

    stack.pop();
    EXPECT_THROW(stack.pop(), std::underflow_error); // Проверка исключения при удалении из пустого стека
}

// Тест: запись стека в файл
TEST(StackTest, WriteToFile) {
    Stack stack;
    stack.push(10);
    stack.push(20);
    stack.push(30);

    std::string filename = "stack_output.txt";
    stack.writeToFile(filename);

    // Проверяем содержимое файла
    std::ifstream file(filename);
    ASSERT_TRUE(file.is_open());
    
    std::string line;
    std::getline(file, line);
    EXPECT_EQ(line, "30"); // Первый элемент
    std::getline(file, line);
    EXPECT_EQ(line, "20"); // Второй элемент
    std::getline(file, line);
    EXPECT_EQ(line, "10"); // Третий элемент
    
    file.close();
    std::remove(filename.c_str()); // Удаляем тестовый файл
}

// Тест: очистка стека
TEST(StackTest, ClearStack) {
    Stack stack;
    stack.push(10);
    stack.push(20);
    stack.clear();

    testing::internal::CaptureStdout();
    stack.print();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "Стек пуст\n"); // Проверяем, что стек пуст
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}