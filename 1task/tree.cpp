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
int AVLTree::height(NodeAVL* n) const {
    return n ? n->height : 0;
}

// Вспомогательная функция для получения баланса узла
int AVLTree::getBalance(NodeAVL* n) const {
    return n ? height(n->left) - height(n->right) : 0;
}

// Вспомогательная функция для обновления высоты узла
void AVLTree::updateHeight(NodeAVL* n) {
    if (n) {
        n->height = 1 + max(height(n->left), height(n->right));
    }
}

NodeAVL* AVLTree::minValueNode(NodeAVL* node) const {
    NodeAVL* current = node;

    // Самый левый узел будет иметь минимальный ключ
    while (current && current->left != nullptr) {
        current = current->left;
    }

    return current;
}

// Правое вращение
NodeAVL* AVLTree::rotateRight(NodeAVL* y) {
    NodeAVL* x = y->left;
    NodeAVL* T2 = x->right;

    x->right = y;
    y->left = T2;

    updateHeight(y);
    updateHeight(x);

    return x;
}

// Левое вращение
NodeAVL* AVLTree::rotateLeft(NodeAVL* x) {
    NodeAVL* y = x->right;
    NodeAVL* T2 = y->left;

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

NodeAVL* AVLTree::insert(NodeAVL* node, int key) {
    if (!node) return new NodeAVL(key);

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

NodeAVL* AVLTree::search(NodeAVL* node, int key) const {
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

NodeAVL* AVLTree::deleteNode(NodeAVL* root, int key) {
    if (!root) return root;

    if (key < root->key) {
        root->left = deleteNode(root->left, key);
    } else if (key > root->key) {
        root->right = deleteNode(root->right, key);
    } else {
        if (!root->left || !root->right) {
            NodeAVL* temp = root->left ? root->left : root->right;

            if (!temp) {
                temp = root;
                root = nullptr;
            } else {
                *root = *temp;
            }
            delete temp;
        } else {
            NodeAVL* temp = minValueNode(root->right);
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

void AVLTree::print(NodeAVL* node, int space, int level) const {
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

void AVLTree::free(NodeAVL* node) {
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

void AVLTree::writeToFile(NodeAVL* node, ofstream& file, int space, int level) const {
    if (!node) return;

    space += 5;

    writeToFile(node->right, file, space, level + 1);

    file << endl << setw(space) << node->key;

    writeToFile(node->left, file, space, level + 1);
}