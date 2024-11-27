#include "gtest/gtest.h"
#include "tree.h"
#include <iostream>
#include <sstream>
#include <iomanip>
#include <fstream>

using namespace std;

// Конструктор
AVLTree::AVLTree() : root(nullptr) {}

// Деструктор
AVLTree::~AVLTree() {
    clear();
}

// Вспомогательная функция для получения высоты узла
int AVLTree::height(Node* n) const {
    return n ? n->height : 0;
}

// Вспомогательная функция для получения баланса узла
int AVLTree::getBalance(Node* n) const {
    return n ? height(n->left) - height(n->right) : 0;
}

// Вспомогательная функция для обновления высоты узла
void AVLTree::updateHeight(Node* n) {
    if (n) {
        n->height = 1 + max(height(n->left), height(n->right));
    }
}

AVLTree::Node* AVLTree::minValueNode(Node* node) const {
    Node* current = node;

    // Самый левый узел будет иметь минимальный ключ
    while (current && current->left != nullptr) {
        current = current->left;
    }

    return current;
}

// Правое вращение
AVLTree::Node* AVLTree::rotateRight(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;

    x->right = y;
    y->left = T2;

    updateHeight(y);
    updateHeight(x);

    return x;
}

// Левое вращение
AVLTree::Node* AVLTree::rotateLeft(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;

    y->left = x;
    x->right = T2;

    updateHeight(x);
    updateHeight(y);

    return y;
}

// Вставка элемента
void AVLTree::insert(int key) {
    root = insert(root, key);
}

AVLTree::Node* AVLTree::insert(Node* node, int key) {
    if (!node) return new Node(key);

    if (key < node->key) {
        node->left = insert(node->left, key);
    } else if (key > node->key) {
        node->right = insert(node->right, key);
    } else {
        return node; // Дубликаты не допускаются
    }

    updateHeight(node);

    int balance = getBalance(node);

    // Балансировка
    if (balance > 1 && key < node->left->key) {
        return rotateRight(node);
    }

    if (balance < -1 && key > node->right->key) {
        return rotateLeft(node);
    }

    if (balance > 1 && key > node->left->key) {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }

    if (balance < -1 && key < node->right->key) {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }

    return node;
}

// Поиск элемента
bool AVLTree::search(int key) const {
    return search(root, key) != nullptr;
}

AVLTree::Node* AVLTree::search(Node* node, int key) const {
    if (!node || node->key == key) {
        return node;
    }

    if (key < node->key) {
        return search(node->left, key);
    }

    return search(node->right, key);
}

// Удаление элемента
void AVLTree::remove(int key) {
    root = deleteNode(root, key);
}

AVLTree::Node* AVLTree::deleteNode(Node* root, int key) {
    if (!root) return root;

    if (key < root->key) {
        root->left = deleteNode(root->left, key);
    } else if (key > root->key) {
        root->right = deleteNode(root->right, key);
    } else {
        if (!root->left || !root->right) {
            Node* temp = root->left ? root->left : root->right;

            if (!temp) {
                temp = root;
                root = nullptr;
            } else {
                *root = *temp;
            }
            delete temp;
        } else {
            Node* temp = minValueNode(root->right);
            root->key = temp->key;
            root->right = deleteNode(root->right, temp->key);
        }
    }

    if (!root) return root;

    updateHeight(root);

    int balance = getBalance(root);

    // Балансировка
    if (balance > 1 && getBalance(root->left) >= 0) {
        return rotateRight(root);
    }

    if (balance < -1 && getBalance(root->right) <= 0) {
        return rotateLeft(root);
    }

    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = rotateLeft(root->left);
        return rotateRight(root);
    }

    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = rotateRight(root->right);
        return rotateLeft(root);
    }

    return root;
}

// Печать дерева
void AVLTree::print() const {
    print(root);
}

void AVLTree::print(Node* node, int space, int level) const {
    if (!node) return;

    space += 5;

    print(node->right, space, level + 1);

    cout << endl << setw(space) << node->key;

    print(node->left, space, level + 1);
}

// Очистка дерева
void AVLTree::clear() {
    free(root);
    root = nullptr;
}

void AVLTree::free(Node* node) {
    if (!node) return;

    free(node->left);
    free(node->right);

    delete node;
}

// Сохранение дерева в файл
void AVLTree::writeToFile(const string& filename) const {
    ofstream file(filename);

    if (!file.is_open()) {
        cerr << "Ошибка при открытии файла для записи" << endl;
        return;
    }

    writeToFile(root, file);
    file.close();
}

void AVLTree::writeToFile(Node* node, ofstream& file, int space, int level) const {
    if (!node) return;

    space += 5;

    writeToFile(node->right, file, space, level + 1);

    file << endl << setw(space) << node->key;

    writeToFile(node->left, file, space, level + 1);
}

// Тест конструктора
TEST(AVLTreeTest, Constructor) {
    AVLTree tree;
    // Очередь должна быть пуста
    EXPECT_FALSE(tree.search(10));  // Дерево пусто, 10 не должно быть найдено
}

// Тест метода insert
TEST(AVLTreeTest, Insert) {
    AVLTree tree;
    tree.insert(10);
    tree.insert(20);
    tree.insert(5);

    // Проверяем, что элементы были добавлены
    EXPECT_TRUE(tree.search(10));  // 10 должно быть найдено
    EXPECT_TRUE(tree.search(20));  // 20 должно быть найдено
    EXPECT_TRUE(tree.search(5));   // 5 должно быть найдено
}

// Тест метода insert для балансировки дерева
TEST(AVLTreeTest, InsertBalancing) {
    AVLTree tree;
    tree.insert(10);
    tree.insert(20);
    tree.insert(30);  // После вставки 30 дерево должно сбалансироваться

    // Проверяем, что дерево сбалансировалось
    EXPECT_TRUE(tree.search(10));  // 10 должно быть найдено
    EXPECT_TRUE(tree.search(20));  // 20 должно быть найдено
    EXPECT_TRUE(tree.search(30));  // 30 должно быть найдено
    tree.remove(30);
    tree.remove(20);
    tree.remove(10);

    tree.insert(30);
    tree.insert(20);
    tree.insert(10);
    EXPECT_TRUE(tree.search(10));  // 10 должно быть найдено
    EXPECT_TRUE(tree.search(20));  // 20 должно быть найдено
    EXPECT_TRUE(tree.search(30));  // 30 должно быть найдено
}

// Тест метода remove
TEST(AVLTreeTest, Remove) {
    AVLTree tree;
    tree.insert(10);
    tree.insert(20);
    tree.insert(5);
    tree.remove(10);

    // После удаления 10, он не должен быть найден
    EXPECT_FALSE(tree.search(10));  // 10 не должно быть найдено
    EXPECT_TRUE(tree.search(20));  // 20 должно быть найдено
    EXPECT_TRUE(tree.search(5));   // 5 должно быть найдено
}

// Тест метода remove для сбалансированного дерева
TEST(AVLTreeTest, RemoveBalancing) {
    AVLTree tree;
    tree.insert(10);
    tree.insert(20);
    tree.insert(5);
    tree.remove(10);  // После удаления 10, дерево должно оставаться сбалансированным

    // Проверяем, что элементы остались сбалансированными
    EXPECT_TRUE(tree.search(20));  // 20 должно быть найдено
    EXPECT_TRUE(tree.search(5));   // 5 должно быть найдено
}

// Тест метода clear
TEST(AVLTreeTest, Clear) {
    AVLTree tree;
    tree.insert(10);
    tree.insert(20);
    tree.insert(5);
    tree.clear();

    // После очистки дерева, все элементы должны быть удалены
    EXPECT_FALSE(tree.search(10));  // 10 не должно быть найдено
    EXPECT_FALSE(tree.search(20));  // 20 не должно быть найдено
    EXPECT_FALSE(tree.search(5));   // 5 не должно быть найдено
}

// Тест метода print (проверка вывода в консоль)
TEST(AVLTreeTest, Print) {
    AVLTree tree;
    tree.insert(10);
    tree.insert(20);
    tree.insert(5);

    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());  // Перехватываем вывод
    tree.print();  // Печатаем дерево
    std::cout.rdbuf(old);  // Восстанавливаем старый поток

    // Проверка вывода дерева
    std::string expected_output = "\n        20\n   10\n         5";
    EXPECT_EQ(buffer.str(), expected_output);  // Ожидаемый формат дерева
}

// Тест метода writeToFile
TEST(AVLTreeTest, WriteToFile) {
    AVLTree tree;
    tree.insert(10);
    tree.insert(20);
    tree.insert(5);

    tree.writeToFile("tree_output.txt");

    // Проверка, что файл существует и содержит правильные данные
    std::ifstream file("tree_output.txt");
    ASSERT_TRUE(file.is_open());

    std::string line;
    std::getline(file, line);
    std::getline(file, line);
    EXPECT_EQ(line, "        20");

    std::getline(file, line);
    EXPECT_EQ(line, "   10");

    std::getline(file, line);
    EXPECT_EQ(line, "         5");

    file.close();
    remove("tree_output.txt");  // Удаляем файл после теста
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}