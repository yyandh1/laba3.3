#include "gtest/gtest.h"
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

// Тест конструкторов и деструкторов
TEST(ListOneTest, ConstructorAndDestructor) {
    ListOne list;
    EXPECT_FALSE(list.search(10));  // Список пустой, 10 не найдено
}

// Тест добавления элемента в начало
TEST(ListOneTest, AddToHead) {
    ListOne list;
    list.addToHead(10);
    EXPECT_TRUE(list.search(10));  // Элемент добавлен в начало

    list.addToHead(20);
    EXPECT_TRUE(list.search(20));  // Новый элемент добавлен в начало
    EXPECT_TRUE(list.search(10));  // Существующий элемент остался
}

// Тест добавления элемента в конец
TEST(ListOneTest, AddToTail) {
    ListOne list;
    list.addToTail(10);
    EXPECT_TRUE(list.search(10));  // Элемент добавлен в конец

    list.addToTail(20);
    EXPECT_TRUE(list.search(20));  // Новый элемент добавлен в конец
    EXPECT_TRUE(list.search(10));  // Существующий элемент остался
}

// Тест удаления элемента с начала
TEST(ListOneTest, RemoveHead) {
    ListOne list;
    list.addToHead(10);
    list.addToHead(20);
    list.removeHead();
    EXPECT_FALSE(list.search(20));  // 20 должен быть удален
    EXPECT_TRUE(list.search(10));   // 10 остался
}

// Тест удаления элемента с конца
TEST(ListOneTest, RemoveTail) {
    ListOne list;
    list.addToTail(10);
    list.addToTail(20);
    list.removeTail();
    EXPECT_FALSE(list.search(20));  // 20 должен быть удален
    EXPECT_TRUE(list.search(10));   // 10 остался
}

// Тест удаления элемента по значению
TEST(ListOneTest, RemoveByValue) {
    ListOne list;
    list.addToHead(10);
    list.addToHead(20);
    list.removeByValue(20);
    EXPECT_FALSE(list.search(20));  // 20 должен быть удален
    EXPECT_TRUE(list.search(10));   // 10 остался
    list.addToHead(20);
    list.removeByValue(10);
    EXPECT_FALSE(list.search(10));  // 20 должен быть удален
    EXPECT_TRUE(list.search(20));   // 10 остался
}

// Тест очистки списка
TEST(ListOneTest, Clear) {
    ListOne list;
    list.addToHead(10);
    list.addToTail(20);
    list.clear();
    EXPECT_FALSE(list.search(10));  // 10 должен быть удален
    EXPECT_FALSE(list.search(20));  // 20 должен быть удален
}

TEST(ListOneTest, Print) {
    // Создаем список
    ListOne list;
    list.addToHead(10);
    list.addToTail(20);
    list.addToTail(30);

    // Перехватываем вывод в строковый поток
    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());  // Перенаправляем cout в stringstream

    // Вызываем функцию print
    list.print();

    // Восстанавливаем старый поток
    std::cout.rdbuf(old);

    // Проверяем, что вывод в buffer соответствует ожидаемому
    std::string expected_output = "10 20 30 \n";
    EXPECT_EQ(buffer.str(), expected_output);
}

// Тест записи в файл и чтения
TEST(ListOneTest, WriteToFile) {
    ListOne list;
    list.addToHead(10);
    list.addToTail(20);
    list.writeToFile("test.txt");

    // Проверяем, что файл существует и содержит ожидаемые данные
    std::ifstream file("test.txt");
    ASSERT_TRUE(file.is_open());

    int value;
    file >> value;
    EXPECT_EQ(value, 10);  // Первый элемент списка

    file >> value;
    EXPECT_EQ(value, 20);  // Второй элемент списка

    file.close();
}

// Тест поиска элемента
TEST(ListOneTest, Search) {
    ListOne list;
    list.addToHead(10);
    EXPECT_TRUE(list.search(10));  // Элемент найден
    EXPECT_FALSE(list.search(20)); // Элемент не найден
}

// Тест удаления элемента из пустого списка
TEST(ListOneTest, RemoveFromEmptyList) {
    ListOne list;
    list.removeHead();
    list.removeTail();
    list.removeByValue(10); // Не должно быть ошибки
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}