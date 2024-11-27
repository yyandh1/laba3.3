#pragma once
#include <string>

class AVLTree {
private:
    struct Node {
        int key;
        int height;
        Node* left;
        Node* right;

        Node(int k) : key(k), height(1), left(nullptr), right(nullptr) {}
    };

    Node* root; // Корневой узел дерева

    // Вспомогательные функции
    int height(Node* n) const;
    int getBalance(Node* n) const;
    void updateHeight(Node* n);
    Node* rotateRight(Node* y);
    Node* rotateLeft(Node* x);
    Node* insert(Node* node, int key);
    Node* search(Node* node, int key) const;
    Node* minValueNode(Node* node) const;
    Node* deleteNode(Node* root, int key);
    void print(Node* node, int space = 0, int level = 0) const;
    void free(Node* node);
    void writeToFile(Node* node, std::ofstream& file, int space = 0, int level = 0) const;

public:
    AVLTree();                     // Конструктор
    ~AVLTree();                    // Деструктор

    void insert(int key);          // Вставка элемента
    bool search(int key) const;    // Поиск элемента
    void remove(int key);          // Удаление элемента
    void print() const;            // Печать дерева
    void clear();                  // Очистка дерева
    void writeToFile(const std::string& filename) const; // Сохранение дерева в файл
};
