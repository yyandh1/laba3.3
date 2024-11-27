#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "hashtable.h"
#include "List1.h"
#include "List2.h"
#include "massive.h"
#include "queue.h"
#include "stack.h"
#include "tree.h"

using namespace std;

void hashtableCmds(HashTable& hashTable) {
    string command;
    string key, value;

    cout << "Введите команду (INSERT, GET, REMOVE, PRINT, EXIT, SERIALIZE_TEXT, DESERIALIZE_TEXT, SERIALIZE_BINARY, DESERIALIZE_BINARY):" << endl;

    while (true) {
        cout << "> ";
        getline(cin, command);

        stringstream ss(command);
        string action;
        ss >> action;

        if (action == "INSERT") {
            if (ss >> key >> value && !key.empty() && !value.empty()) {
                hashTable.insert(key, value);
                hashTable.writeToFile("hashtable.txt");
            } 
            else {
                cout << "> Неверный ввод. Необходимо ввести: INSERT <ключ> <значение>" << endl;
            }
        } 
        else if (action == "GET") {
            if (ss >> key && !key.empty()) {
                cout << "Значение: " << hashTable.get(key) << endl;
            } else {
                cout << "> Неверный ввод. Необходимо ввести: GET <ключ>" << endl;
            }
        }
        else if (action == "REMOVE") {
            if (ss >> key && !key.empty()) {
                hashTable.remove(key);
                hashTable.writeToFile("hashtable.txt");
            } 
            else {
                cout << "> Неверный ввод. Необходимо ввести: REMOVE <ключ>" << endl;
            }
        } 
        else if (action == "PRINT") {
            hashTable.print();
        }
        else if (action == "SERIALIZE_TEXT") {
            hashTable.serializeToText("serialize_hashtable.txt");
        }
        else if (action == "DESERIALIZE_TEXT") {
            hashTable.deserializeFromText("serialize_hashtable.txt");
        }
        else if (action == "SERIALIZE_BINARY") {
            hashTable.serializeToBinary("serialize_hashtable.bin");
        }
        else if (action == "DESERIALIZE_BINARY") {
            hashTable.deserializeFromBinary("serialize_hashtable.bin");
        }
        else if (action == "EXIT") {
            break;
        } 
        else {
            cout << "> Неизвестная команда. Допутимые команды: INSERT, GET, REMOVE, PRINT, EXIT, SERIALIZE_TEXT, DESERIALIZE_TEXT, SERIALIZE_BINARY, DESERIALIZE_BINARY." << endl;
        }
    }
}

void list1Cmds (ListOne& listone) {
    string command;
    int value;

    cout << "Введите команду (ADDHEAD, ADDTAIL, REMOVEHEAD, REMOVETAIL, REMOVEVALUE, SEARCH, PRINT, EXIT, SERIALIZE_TEXT, DESERIALIZE_TEXT, SERIALIZE_BINARY, DESERIALIZE_BINARY):" << endl;

    while (true) {
        cout << "> ";
        getline(cin, command);

        stringstream ss(command);
        string action;
        ss >> action;

        if (action == "ADDHEAD") {
            ss >> value;
            if (!ss.fail()) {
                listone.addToHead(value);
                listone.writeToFile("list1.txt");
            } else {
                cout << "> Неверный ввод. Необходимо ввести: ADDHEAD <значение>" << endl;
            }
        } 
        else if (action == "ADDTAIL") {
            ss >> value;
            if (!ss.fail()) {
                listone.addToTail(value);
                listone.writeToFile("list1.txt");
            } 
            else {
                cout << "> Неверный ввод. Необходимо ввести: ADDTAIL <значение>" << endl;
            }
        } 
        else if (action == "REMOVEHEAD") {
            listone.removeHead();
            listone.writeToFile("list1.txt");
        } 
        else if (action == "REMOVETAIL") {
            listone.removeTail();
            listone.writeToFile("list1.txt");
        } 
        else if (action == "REMOVEVALUE") {
            ss >> value;
            if (!ss.fail()) {
                listone.removeByValue(value);
                listone.writeToFile("list1.txt");
            } 
            else {
                cout << "> Неверный ввод. Необходимо ввести: REMOVEVALUE <значение>" << endl;
            }
        } 
        else if (action == "SEARCH") {
            ss >> value;
            if (!ss.fail()) {
                cout << "Результат поиска для значения " << value << ": " 
                     << (listone.search(value) ? "Найдено" : "Не найдено") << endl;
            } 
            else {
                cout << "> Неверный ввод. Необходимо ввести: SEARCH <значение>" << endl;
            }
        } 
        else if (action == "PRINT") {
            cout << "Содержимое списка: ";
            listone.print();
        }
        else if (action == "SERIALIZE_TEXT") {
            listone.serializeToText("serialize_list1.txt");
        }
        else if (action == "DESERIALIZE_TEXT") {
            listone.deserializeFromText("serialize_list1.txt");
        }
        else if (action == "SERIALIZE_BINARY") {
            listone.serializeToBinary("serialize_list1.bin");
        }
        else if (action == "DESERIALIZE_BINARY") {
            listone.deserializeFromBinary("serialize_list1.bin");
        } 
        else if (action == "EXIT") {
            break;
        } 
        else {
            cout << "> Неизвестная команда. Допутимые команды: ADDHEAD, ADDTAIL, REMOVEHEAD, REMOVETAIL, REMOVEVALUE, SEARCH, PRINT, EXIT, SERIALIZE_TEXT, DESERIALIZE_TEXT, SERIALIZE_BINARY, DESERIALIZE_BINARY." << endl;
        }
    }
}

void list2Cmds (DoubleList& list) {
    string command;
    int value;

    cout << "Введите команду (ADDHEAD, ADDTAIL, REMOVEHEAD, REMOVETAIL, REMOVEVALUE, FIND, PRINT, EXIT, SERIALIZE_TEXT, DESERIALIZE_TEXT, SERIALIZE_BINARY, DESERIALIZE_BINARY):" << endl;

    while (true) {
        cout << "> ";
        getline(cin, command);

        stringstream ss(command);
        string action;
        ss >> action;

        if (action == "ADDHEAD") {
            ss >> value;
            if (!ss.fail()) {
                list.addToHead(value);
                list.writeToFile("list2.txt");
            } 
            else {
                cout << "> Неверный ввод. Необходимо ввести: ADDHEAD <значение>" << endl;
            }
        } 
        else if (action == "ADDTAIL") {
            ss >> value;
            if (!ss.fail()) {
                list.addToTail(value);
                list.writeToFile("list2.txt");
            } 
            else {
                cout << "> Неверный ввод. Необходимо ввести: addtail <value>" << endl;
            }
        } 
        else if (action == "REMOVEHEAD") {
            list.removeFromHead();
            list.writeToFile("list2.txt");
        } 
        else if (action == "REMOVETAIL") {
            list.removeFromTail();
            list.writeToFile("list2.txt");
        } 
        else if (action == "REMOVEVALUE") {
            ss >> value;
            if (!ss.fail()) {
                list.removeByValue(value);
                list.writeToFile("list2.txt");
            } 
            else {
                cout << "> Неверный ввод. Необходимо ввести: REMOVEVALUE <значение>" << endl;
            }
        } 
        else if (action == "FIND") {
            ss >> value;
            if (!ss.fail()) {
                bool result = list.find(value);
                cout << "Результат поиска для значения " << value << ": " 
                     << (result ? "Найдено" : "Не найдено") << endl;
            } 
            else {
                cout << "> Неверный ввод. Необходимо ввести: FIND <значение>" << endl;
            }
        } 
        else if (action == "PRINT") {
            cout << "Содержимое списка: ";
            list.print();
        }
        else if (action == "SERIALIZE_TEXT") {
            list.serializeToText("serialize_list2.txt");
        }
        else if (action == "DESERIALIZE_TEXT") {
            list.deserializeFromText("serialize_list2.txt");
        }
        else if (action == "SERIALIZE_BINARY") {
            list.serializeToBinary("serialize_list2.bin");
        }
        else if (action == "DESERIALIZE_BINARY") {
            list.deserializeFromBinary("serialize_list2.bin");
        }  
        else if (action == "EXIT") {
            break;
        } 
        else {
            cout << "> Неизвестная команда. Допутимые команды: ADDHEAD, ADDTAIL, REMOVEHEAD, REMOVETAIL, REMOVEVALUE, FIND, PRINT, EXIT, SERIALIZE_TEXT, DESERIALIZE_TEXT, SERIALIZE_BINARY, DESERIALIZE_BINARY." << endl;
        }
    }
}

void arrayCmds (Array& arr) {

    string command;
    int index, value;

    cout << "Введите команду (APPEND, INSERT, REMOVE, REPLACE, GET, DISPLAY, LENGTH, EXIT, SERIALIZE_TEXT, DESERIALIZE_TEXT, SERIALIZE_BINARY, DESERIALIZE_BINARY):" << endl;

    while (true) {
        cout << "> ";
        getline(cin, command);

        stringstream ss(command);
        string action;
        ss >> action;

        if (action == "APPEND") {
            ss >> value;
            if (!ss.fail()) {
                arr.append(value);
                arr.writeToFile("array.txt");
            } 
            else {
                cout << "> Неверный ввод. Необходимо ввести: APPEND <значение>" << endl;
            }
        } 
        else if (action == "INSERT") {
            ss >> index >> value;
            if (!ss.fail()) {
                arr.insert(index, value);
                arr.writeToFile("array.txt");
            } 
            else {
                cout << "> Неверный ввод. Необходимо ввести: insert <индекс> <значение>" << endl;
            }
        } 
        else if (action == "REMOVE") {
            ss >> index;
            if (!ss.fail()) {
                arr.remove(index);
                arr.writeToFile("array.txt");
            } 
            else {
                cout << "> Неверный ввод. Необходимо ввести: REMOVE <индекс>" << endl;
            }
        } 
        else if (action == "REPLACE") {
            ss >> index >> value;
            if (!ss.fail()) {
                arr.replace(index, value);
                arr.writeToFile("array.txt");
            } 
            else {
                cout << "> Неверный ввод. Необходимо ввести: REPLACE <индекс> <значение>" << endl;
            }
        } 
        else if (action == "GET") {
            ss >> index;
            if (!ss.fail()) {
                int result = arr.get(index);
                if (result != -1) {
                    cout << "Элемент по индексу " << index << ": " << result << endl;
                }
            } 
            else {
                cout << "> Неверный ввод. Необходимо ввести: GET <индекс>" << endl;
            }
        } 
        else if (action == "DISPLAY") {
            cout << "Содержимое массива: ";
            arr.display();
        } 
        else if (action == "LENGTH") {
            cout << "Длина массива: " << arr.length() << endl;
        }
        else if (action == "SERIALIZE_TEXT") {
            arr.serializeToText("serialize_massive.txt");
        }
        else if (action == "DESERIALIZE_TEXT") {
            arr.deserializeFromText("serialize_massive.txt");
        }
        else if (action == "SERIALIZE_BINARY") {
            arr.serializeToBinary("serialize_massive.bin");
        }
        else if (action == "DESERIALIZE_BINARY") {
            arr.deserializeFromBinary("serialize_massive.bin");
        }  
        else if (action == "EXIT") {
            break;
        } 
        else {
            cout << "> Неизвестная команда. Допутимые команды: APPEND, INSERT, REMOVE, REPLACE, GET, DISPLAY, LENGTH, EXIT, SERIALIZE_TEXT, DESERIALIZE_TEXT, SERIALIZE_BINARY, DESERIALIZE_BINARY." << endl;
        }
    }
}

void queueCmds (Queue& q) {

    string command;
    int value;

    cout << "Введите команду (ENQUEUE, DEQUEUE, PRINT, EXIT, SERIALIZE_TEXT, DESERIALIZE_TEXT, SERIALIZE_BINARY, DESERIALIZE_BINARY):" << endl;

    while (true) {
        cout << "> ";
        getline(cin, command);

        stringstream ss(command);
        string action;
        ss >> action;

        if (action == "ENQUEUE") {
            ss >> value;
            if (!ss.fail()) {
                q.enqueue(value);
                q.writeToFile("queue.txt");
            } 
            else {
                cout << "> Неверный ввод. Необходимо ввести: ENQUEUE <значение>" << endl;
            }
        } 
        else if (action == "DEQUEUE") {
            int result = q.dequeue();
            q.writeToFile("queue.txt");
        } 
        else if (action == "PRINT") {
            q.print();
        }
        else if (action == "SERIALIZE_TEXT") {
            q.serializeToText("serialize_queue.txt");
        }
        else if (action == "DESERIALIZE_TEXT") {
            q.deserializeFromText("serialize_queue.txt");
        }
        else if (action == "SERIALIZE_BINARY") {
            q.serializeToBinary("serialize_queue.bin");
        }
        else if (action == "DESERIALIZE_BINARY") {
            q.deserializeFromBinary("serialize_queue.bin");
        }  
        else if (action == "EXIT") {
            break;
        } 
        else {
            cout << "> Неизвестная команда. Допутимые команды: ENQUEUE, DEQUEUE, PRINT, EXIT, SERIALIZE_TEXT, DESERIALIZE_TEXT, SERIALIZE_BINARY, DESERIALIZE_BINARY." << endl;
        }
    }
}

void stackCmds (Stack& stack) {

    string command;
    int value;

    cout << "Введите команду (PUSH, POP, PRINT, EXIT, SERIALIZE_TEXT, DESERIALIZE_TEXT, SERIALIZE_BINARY, DESERIALIZE_BINARY):" << endl;

    while (true) {
        cout << "> ";
        getline(cin, command);

        stringstream ss(command);
        string action;
        ss >> action;

        if (action == "PUSH") {
            ss >> value;
            if (!ss.fail()) {
                stack.push(value);
                stack.writeToFile("stack.txt");
            } else {
                cout << "> Неверный ввод. Необходимо ввести: PUSH <значение>" << endl;
            }
        } 
        else if (action == "POP") {
            stack.pop();
            stack.writeToFile("stack.txt");
        } 
        else if (action == "PRINT") {
            stack.print();
        }
        else if (action == "SERIALIZE_TEXT") {
            stack.serializeToText("serialize_stack.txt");
        }
        else if (action == "DESERIALIZE_TEXT") {
            stack.deserializeFromText("serialize_stack.txt");
        }
        else if (action == "SERIALIZE_BINARY") {
            stack.serializeToBinary("serialize_stack.bin");
        }
        else if (action == "DESERIALIZE_BINARY") {
            stack.deserializeFromBinary("serialize_stack.bin");
        }  
        else if (action == "EXIT") {
            break;
        } 
        else {
            cout << "> Неизвестная команда. Допутимые команды: PUSH, POP, PRINT, EXIT, SERIALIZE_TEXT, DESERIALIZE_TEXT, SERIALIZE_BINARY, DESERIALIZE_BINARY." << endl;
        }
    }
}

void treeCmds (AVLTree& tree) {
    string command;
    int value;

    cout << "Введите команду (INSERT, DELETE, SEARCH, PRINT, EXIT, SERIALIZE_TEXT, DESERIALIZE_TEXT, SERIALIZE_BINARY, DESERIALIZE_BINARY):" << endl;

    while (true) {
        cout << "> ";
        getline(cin, command);

        stringstream ss(command);
        string action;
        ss >> action;

        if (action == "INSERT") {
            ss >> value;
            if (!ss.fail()) {
                tree.insert(value);
                tree.writeToFile("tree.txt");
            }
            else {
                cout << "> Неверный ввод. Необходимо ввести: INSERT <значение>" << endl;
            }
        } 
        else if (action == "DELETE") {
            ss >> value;
            if (!ss.fail()) {
                tree.remove(value);
                tree.writeToFile("tree.txt");
            } 
            else {
                cout << "> Неверный ввод. Необходимо ввести: DELETE <значение>" << endl;
            }
        } 
        else if (action == "SEARCH") {
            if (ss >> value) {
                bool result = tree.search(value);
                cout << "Результат поиска для значения " << value << ": " 
                     << (result ? "Найдено" : "Не найдено") << endl;
            } 
            else {
                cout << "> Неверный ввод. Необходимо ввести: SEARCH <значение>" << endl;
            }
        } 
        else if (action == "PRINT") {
            tree.print();
            cout << endl;
        }
        else if (action == "SERIALIZE_TEXT") {
            tree.serializeToText("serialize_tree.txt");
        }
        else if (action == "DESERIALIZE_TEXT") {
            tree.deserializeFromText("serialize_tree.txt");
        }
        else if (action == "SERIALIZE_BINARY") {
            tree.serializeToBinary("serialize_tree.bin");
        }
        else if (action == "DESERIALIZE_BINARY") {
            tree.deserializeFromBinary("serialize_tree.bin");
        }   
        else if (action == "EXIT") {
            break;
        } 
        else {
            cout << "> Неизвестная команда. Допутимые команды: INSERT, DELETE, SEARCH, PRINT, EXIT, SERIALIZE_TEXT, DESERIALIZE_TEXT, SERIALIZE_BINARY, DESERIALIZE_BINARY." << endl;
        }
    }
}

int main() {
    HashTable hashTable;
    ListOne listone;
    DoubleList list;
    Array arr;
    Queue q;
    Stack stack;
    AVLTree tree;

    string command;

    cout << "> Выберите структуру данных (HASHTABLE, LIST1, LIST2, ARRAY, QUEUE, STACK, AVLTREE, EXIT):" << endl;

    while (true) {
        cout << "> ";
        getline(cin, command);

        if (command == "HASHTABLE") {
            hashtableCmds(hashTable);
        } 
        else if (command == "LIST1") {
            list1Cmds(listone);
        } 
        else if (command == "LIST2") {
            list2Cmds(list);
        } 
        else if (command == "ARRAY") {
            arrayCmds(arr);
        } 
        else if (command == "QUEUE") {
            queueCmds(q);
        } 
        else if (command == "STACK") {
            stackCmds(stack);
        } 
        else if (command == "AVLTREE") {
            treeCmds(tree);
        } 
        else if (command == "EXIT") {
            break;
        } 
        else {
            cout << "> Неизвестная команда. Доступные команды: HASHTABLE, LIST1, LIST2, ARRAY, QUEUE, STACK, AVLTREE, EXIT." << endl;
        }
    }

    hashTable.clear();
    listone.clear();
    list.clear();
    q.clear();
    stack.clear();
    tree.clear();

    return 0;
}