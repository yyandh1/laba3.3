#include "gtest/gtest.h"
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
    Node* newNode = new Node(value, head);

    if (head) {
        head->previous = newNode;
    } else {
        tail = newNode;
    }
    head = newNode;
}

// Добавить элемент в конец
void DoubleList::addToTail(int value) {
    Node* newNode = new Node(value, nullptr, tail);

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

    Node* temp = head;
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

    Node* temp = tail;
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
    Node* temp = head;

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
void DoubleList::print() const {
    Node* temp = head;
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

    Node* temp = head;
    while (temp) {
        file << temp->data << endl;
        temp = temp->next;
    }

    file.close();
}

// Тест конструкторов и деструкторов
TEST(DoubleListTest, ConstructorAndDestructor) {
    DoubleList list;
    EXPECT_FALSE(list.find(10));  // Список пустой, 10 не найдено
}

// Тест добавления элемента в начало
TEST(DoubleListTest, AddToHead) {
    DoubleList list;
    list.addToHead(10);
    EXPECT_TRUE(list.find(10));  // Элемент добавлен в начало

    list.addToHead(20);
    EXPECT_TRUE(list.find(20));  // Новый элемент добавлен в начало
    EXPECT_TRUE(list.find(10));  // Существующий элемент остался
}

// Тест добавления элемента в конец
TEST(DoubleListTest, AddToTail) {
    DoubleList list;
    list.addToTail(10);
    EXPECT_TRUE(list.find(10));  // Элемент добавлен в конец

    list.addToTail(20);
    EXPECT_TRUE(list.find(20));  // Новый элемент добавлен в конец
    EXPECT_TRUE(list.find(10));  // Существующий элемент остался
}

// Тест удаления элемента с начала
TEST(DoubleListTest, RemoveFromHead) {
    DoubleList list;
    list.addToHead(10);
    list.addToHead(20);
    list.removeFromHead();
    EXPECT_FALSE(list.find(20));  // 20 должен быть удален
    EXPECT_TRUE(list.find(10));   // 10 остался
}

// Тест удаления элемента с конца
TEST(DoubleListTest, RemoveFromTail) {
    DoubleList list;
    list.addToTail(10);
    list.addToTail(20);
    list.removeFromTail();
    EXPECT_FALSE(list.find(20));  // 20 должен быть удален
    EXPECT_TRUE(list.find(10));   // 10 остался
}

// Тест удаления элемента по значению
TEST(DoubleListTest, RemoveByValue) {
    DoubleList list;
    list.addToHead(10);
    list.addToHead(20);
    list.removeByValue(20);
    EXPECT_FALSE(list.find(20));  // 20 должен быть удален
    EXPECT_TRUE(list.find(10));   // 10 остался
}

// Тест поиска элемента
TEST(DoubleListTest, Find) {
    DoubleList list;
    list.addToHead(10);
    EXPECT_TRUE(list.find(10));  // Элемент найден
    EXPECT_FALSE(list.find(20)); // Элемент не найден
}

// Тест очистки списка
TEST(DoubleListTest, Clear) {
    DoubleList list;
    list.addToHead(10);
    list.addToTail(20);
    list.clear();
    EXPECT_FALSE(list.find(10));  // 10 должен быть удален
    EXPECT_FALSE(list.find(20));  // 20 должен быть удален
}

TEST(DoubleListTest, Print) {
    // Создаем список
    DoubleList list;
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
TEST(DoubleListTest, WriteToFile) {
    DoubleList list;
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

// Тест удаления элемента из пустого списка
TEST(DoubleListTest, RemoveFromEmptyList) {
    DoubleList list;
    list.removeFromHead();
    list.removeFromTail();
    list.removeByValue(10); // Не должно быть ошибки
}

// Тест удаления всех элементов
TEST(DoubleListTest, RemoveAllElements) {
    DoubleList list;
    list.addToHead(10);
    list.addToTail(20);
    list.removeFromHead();
    list.removeFromTail();
    EXPECT_FALSE(list.find(10)); // 10 удален
    EXPECT_FALSE(list.find(20)); // 20 удален
}

// Тест добавления и удаления в пустом списке
TEST(DoubleListTest, AddAndRemoveInEmptyList) {
    DoubleList list;
    list.addToTail(10);
    EXPECT_TRUE(list.find(10));  // Элемент добавлен

    list.removeFromTail();
    EXPECT_FALSE(list.find(10)); // Элемент удален
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}