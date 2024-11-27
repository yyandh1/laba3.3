#pragma once
#include <string>
#include <fstream>

class NodeAVL {
public:
    int key;
    int height;
    NodeAVL* left;
    NodeAVL* right;

    NodeAVL(int k) : key(k), height(1), left(nullptr), right(nullptr) {}
};

class AVLTree {
private:
    NodeAVL* root; // Корневой узел дерева

    // Вспомогательные функции
    int height(NodeAVL* n) const;
    int getBalance(NodeAVL* n) const;
    void updateHeight(NodeAVL* n);
    NodeAVL* rotateRight(NodeAVL* y);
    NodeAVL* rotateLeft(NodeAVL* x);
    NodeAVL* insert(NodeAVL* NodeAVL, int key);
    NodeAVL* search(NodeAVL* NodeAVL, int key) const;
    NodeAVL* minValueNode(NodeAVL* node) const;
    NodeAVL* deleteNode(NodeAVL* root, int key);
    void print(NodeAVL* node, int space = 0, int level = 0) const;
    void free(NodeAVL* node);
    void writeToFile(NodeAVL* node, std::ofstream& file, int space = 0, int level = 0) const;

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