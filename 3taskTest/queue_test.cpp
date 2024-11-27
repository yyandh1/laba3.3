#include "gtest/gtest.h"
#include "Queue.h"
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

// Тест конструктора очереди
TEST(QueueTest, Constructor) {
    Queue q;
    // Очередь должна быть пуста после создания
    EXPECT_THROW(q.dequeue(), std::underflow_error);
    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());  // Перехватываем вывод
    q.print();
    std::cout.rdbuf(old);  // Восстанавливаем старый поток
    EXPECT_EQ(buffer.str(), "Очередь пуста\n");  // Ожидаемый вывод
}

// Тест метода enqueue (добавление элементов в очередь)
TEST(QueueTest, Enqueue) {
    Queue q;
    q.enqueue(10);
    q.enqueue(20);
    q.enqueue(30);

    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());  // Перехватываем вывод
    q.print();  // Печатаем очередь
    std::cout.rdbuf(old);  // Восстанавливаем старый поток
    EXPECT_EQ(buffer.str(), "Очередь: 10 20 30 \n");  // Проверка вывода очереди
}

// Тест метода dequeue (удаление элементов из очереди)
TEST(QueueTest, Dequeue) {
    Queue q;
    q.enqueue(10);
    q.enqueue(20);
    q.enqueue(30);

    // Удаляем элементы по очереди
    EXPECT_EQ(q.dequeue(), 10);  // Первый элемент, 10
    EXPECT_EQ(q.dequeue(), 20);  // Второй элемент, 20
    EXPECT_EQ(q.dequeue(), 30);  // Третий элемент, 30

    // Попытка удалить из пустой очереди
    EXPECT_THROW(q.dequeue(), std::underflow_error);  // Очередь пуста, выбрасывается исключение
}

// Тест метода writeToFile (запись в файл)
TEST(QueueTest, WriteToFile) {
    Queue q;
    q.enqueue(10);
    q.enqueue(20);
    q.enqueue(30);

    q.writeToFile("queue_output.txt");

    // Проверка, что файл существует и содержит правильные данные
    std::ifstream file("queue_output.txt");
    ASSERT_TRUE(file.is_open());

    int value;
    file >> value;
    EXPECT_EQ(value, 10);  // Первый элемент очереди должен быть 10

    file >> value;
    EXPECT_EQ(value, 20);  // Второй элемент очереди должен быть 20

    file >> value;
    EXPECT_EQ(value, 30);  // Третий элемент очереди должен быть 30

    file.close();
    remove("queue_output.txt");  // Удаляем файл после теста
}

// Тест метода clear (очистка очереди)
TEST(QueueTest, Clear) {
    Queue q;
    q.enqueue(10);
    q.enqueue(20);
    q.enqueue(30);

    q.clear();  // Очищаем очередь

    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());  // Перехватываем вывод
    q.print();  // Печатаем очередь
    std::cout.rdbuf(old);  // Восстанавливаем старый поток
    EXPECT_EQ(buffer.str(), "Очередь пуста\n");  // Очередь должна быть пуста
}

// Тест метода enqueue и dequeue на граничных значениях
TEST(QueueTest, EnqueueDequeueEdgeCases) {
    Queue q;

    // Добавляем одно значение и сразу удаляем
    q.enqueue(100);
    EXPECT_EQ(q.dequeue(), 100);  // Должен вернуть 100

    // Попытка удаления из пустой очереди
    EXPECT_THROW(q.dequeue(), std::underflow_error);  // Очередь пуста
}

// Тест метода enqueue и dequeue с большим количеством элементов
TEST(QueueTest, EnqueueDequeueLarge) {
    Queue q;

    // Добавляем 1000 элементов
    for (int i = 0; i < 1000; ++i) {
        q.enqueue(i);
    }

    // Проверяем, что все элементы можно удалить корректно
    for (int i = 0; i < 1000; ++i) {
        EXPECT_EQ(q.dequeue(), i);  // Должен вернуть i
    }

    // Попытка удаления из пустой очереди
    EXPECT_THROW(q.dequeue(), std::underflow_error);  // Очередь пуста
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}