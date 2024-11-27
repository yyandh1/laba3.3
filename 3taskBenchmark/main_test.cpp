#include <benchmark/benchmark.h>
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

static void BenchmarkInsertH(benchmark::State& state) {
    HashTable table;
    for (auto _ : state) {
        for (int i = 0; i < 100; ++i) {
            table.insert("key" + std::to_string(i), "value" + std::to_string(i));
        }
    }
}

static void BenchmarkGetH(benchmark::State& state) {
    HashTable table;
    for (int i = 0; i < 100; ++i) {
        table.insert("key" + std::to_string(i), "value" + std::to_string(i));
    }

    for (auto _ : state) {
        for (int i = 0; i < 100; ++i) {
            table.get("key" + std::to_string(i));
        }
    }
}

static void BenchmarkRemoveH(benchmark::State& state) {
    HashTable table;
    for (int i = 0; i < 100; ++i) {
        table.insert("key" + std::to_string(i), "value" + std::to_string(i));
    }

    for (auto _ : state) {
        for (int i = 0; i < 100; ++i) {
            table.remove("key" + std::to_string(i));
        }
    }
}

static void BenchmarkClearH(benchmark::State& state) {
    HashTable table;
    for (int i = 0; i < 100; ++i) {
        table.insert("key" + std::to_string(i), "value" + std::to_string(i));
    }

    for (auto _ : state) {
        table.clear();
    }
}

// Бенчмарк для добавления элементов в начало
static void BenchmarkAddToHeadL1(benchmark::State& state) {
    for (auto _ : state) {
        ListOne list;
        for (int i = 0; i < 100; ++i) {
            list.addToHead(i);
        }
    }
}

// Бенчмарк для добавления элементов в конец
static void BenchmarkAddToTailL1(benchmark::State& state) {
    for (auto _ : state) {
        ListOne list;
        for (int i = 0; i < 100; ++i) {
            list.addToTail(i);
        }
    }
}

// Бенчмарк для удаления элементов с головы
static void BenchmarkRemoveHeadL1(benchmark::State& state) {
    for (auto _ : state) {
        ListOne list;
        for (int i = 0; i < 100; ++i) {
            list.addToHead(i);
        }
        for (int i = 0; i < 100; ++i) {
            list.removeHead();
        }
    }
}

// Бенчмарк для удаления элементов с хвоста
static void BenchmarkRemoveTailL1(benchmark::State& state) {
    for (auto _ : state) {
        ListOne list;
        for (int i = 0; i < 100; ++i) {
            list.addToTail(i);
        }
        for (int i = 0; i < 100; ++i) {
            list.removeTail();
        }
    }
}

// Бенчмарк для поиска элемента
static void BenchmarkSearchL1(benchmark::State& state) {
    ListOne list;
    for (int i = 0; i < 100; ++i) {
        list.addToTail(i);
    }

    for (auto _ : state) {
        list.search(100 / 2); // Ищем элемент в середине списка
    }
}

// Бенчмарк для удаления элемента по значению
static void BenchmarkRemoveByValueL1(benchmark::State& state) {
    for (auto _ : state) {
        ListOne list;
        for (int i = 0; i < 100; ++i) {
            list.addToTail(i);
        }
        list.removeByValue(100 / 2); // Удаляем элемент в середине списка
    }
}

// Бенчмарк для очистки списка
static void BenchmarkClearL1(benchmark::State& state) {
    for (auto _ : state) {
        ListOne list;
        for (int i = 0; i < 100; ++i) {
            list.addToTail(i);
        }
        list.clear();
    }
}

static void BenchmarkAddToHeadL2(benchmark::State& state) {
    for (auto _ : state) {
        DoubleList list;
        for (int i = 0; i < 100; ++i) {
            list.addToHead(i);
        }
    }
}

// Бенчмарк для добавления элементов в конец
static void BenchmarkAddToTailL2(benchmark::State& state) {
    for (auto _ : state) {
        DoubleList list;
        for (int i = 0; i < 100; ++i) {
            list.addToTail(i);
        }
    }
}

// Бенчмарк для удаления элементов с головы
static void BenchmarkRemoveFromHeadL2(benchmark::State& state) {
    for (auto _ : state) {
        DoubleList list;
        for (int i = 0; i < 100; ++i) {
            list.addToHead(i);
        }
        for (int i = 0; i < 100; ++i) {
            list.removeFromHead();
        }
    }
}

// Бенчмарк для удаления элементов с хвоста
static void BenchmarkRemoveFromTailL2(benchmark::State& state) {
    for (auto _ : state) {
        DoubleList list;
        for (int i = 0; i < 100; ++i) {
            list.addToTail(i);
        }
        for (int i = 0; i < 100; ++i) {
            list.removeFromTail();
        }
    }
}

// Бенчмарк для поиска элемента
static void BenchmarkFindL2(benchmark::State& state) {
    DoubleList list;
    for (int i = 0; i < 100; ++i) {
        list.addToTail(i);
    }

    for (auto _ : state) {
        list.find(100 / 2); // Ищем элемент в середине списка
    }
}

// Бенчмарк для удаления элемента по значению
static void BenchmarkRemoveByValueL2(benchmark::State& state) {
    for (auto _ : state) {
        DoubleList list;
        for (int i = 0; i < 100; ++i) {
            list.addToTail(i);
        }
        list.removeByValue(100 / 2); // Удаляем элемент в середине списка
    }
}

// Бенчмарк для очистки списка
static void BenchmarkClearL2(benchmark::State& state) {
    for (auto _ : state) {
        DoubleList list;
        for (int i = 0; i < 100; ++i) {
            list.addToTail(i);
        }
        list.clear();
    }
}

// Бенчмарк для добавления элементов в конец массива
static void BenchmarkAppendArr(benchmark::State& state) {
    for (auto _ : state) {
        Array arr(100);
        for (int i = 0; i < 100; ++i) {
            arr.append(i);
        }
    }
}

// Бенчмарк для вставки элемента в середину массива
static void BenchmarkInsertMiddleArr(benchmark::State& state) {
    for (auto _ : state) {
        Array arr(100);
        for (int i = 0; i < 100; ++i) {
            arr.append(i);
        }
        arr.insert(100 / 2, 42); // Вставка в середину
    }
}

// Бенчмарк для вставки элемента в начало массива
static void BenchmarkInsertBeginningArr(benchmark::State& state) {
    for (auto _ : state) {
        Array arr(100);
        for (int i = 0; i < 100; ++i) {
            arr.append(i);
        }
        arr.insert(0, 42); // Вставка в начало
    }
}

// Бенчмарк для удаления элемента из конца массива
static void BenchmarkRemoveLastArr(benchmark::State& state) {
    for (auto _ : state) {
        Array arr(100);
        for (int i = 0; i < 100; ++i) {
            arr.append(i);
        }
        arr.remove(100 - 1); // Удаление последнего элемента
    }
}

// Бенчмарк для удаления элемента из начала массива
static void BenchmarkRemoveFirstArr(benchmark::State& state) {
    for (auto _ : state) {
        Array arr(100);
        for (int i = 0; i < 100; ++i) {
            arr.append(i);
        }
        arr.remove(0); // Удаление первого элемента
    }
}

// Бенчмарк для доступа к элементу массива
static void BenchmarkGetArr(benchmark::State& state) {
    Array arr(100);
    for (int i = 0; i < 100; ++i) {
        arr.append(i);
    }

    for (auto _ : state) {
        benchmark::DoNotOptimize(arr.get(100 / 2)); // Доступ к середине
    }
}

// Бенчмарк для замены элемента массива
static void BenchmarkReplaceArr(benchmark::State& state) {
    Array arr(100);
    for (int i = 0; i < 100; ++i) {
        arr.append(i);
    }

    for (auto _ : state) {
        arr.replace(100 / 2, 42); // Замена элемента в середине
    }
}

// Бенчмарк для очистки массива
static void BenchmarkFreeArr(benchmark::State& state) {
    for (auto _ : state) {
        Array arr(100);
        for (int i = 0; i < 100; ++i) {
            arr.append(i);
        }
        arr.free();
    }
}

// Бенчмарк для добавления элементов в очередь
static void BenchmarkEnqueueQue(benchmark::State& state) {
    for (auto _ : state) {
        Queue q;
        for (int i = 0; i < 100; ++i) {
            q.enqueue(i);
        }
    }
}

// Бенчмарк для удаления элементов из очереди
static void BenchmarkDequeueQue(benchmark::State& state) {
    for (auto _ : state) {
        Queue q;
        for (int i = 0; i < 100; ++i) {
            q.enqueue(i);
        }
        for (int i = 0; i < 100; ++i) {
            q.dequeue();
        }
    }
}

// Бенчмарк для очистки очереди
static void BenchmarkClearQue(benchmark::State& state) {
    for (auto _ : state) {
        Queue q;
        for (int i = 0; i < 100; ++i) {
            q.enqueue(i);
        }
        q.clear();
    }
}

// Бенчмарк для добавления элементов в стек
static void BenchmarkPushStack(benchmark::State& state) {
    for (auto _ : state) {
        Stack stack;
        for (int i = 0; i < 100; ++i) {
            stack.push(i);
        }
    }
}

// Бенчмарк для удаления элементов из стека
static void BenchmarkPopStack(benchmark::State& state) {
    for (auto _ : state) {
        Stack stack;
        for (int i = 0; i < 100; ++i) {
            stack.push(i);
        }
        for (int i = 0; i < 100; ++i) {
            stack.pop();
        }
    }
}

// Бенчмарк для очистки стека
static void BenchmarkClearStack(benchmark::State& state) {
    for (auto _ : state) {
        Stack stack;
        for (int i = 0; i < 100; ++i) {
            stack.push(i);
        }
        stack.clear();
    }
}

static void BenchmarkInsertTree(benchmark::State& state) {
    for (auto _ : state) {
        AVLTree tree;
        for (int i = 0; i < 100; ++i) {
            tree.insert(i);
        }
    }
}

static void BenchmarkSearchTree(benchmark::State& state) {
    AVLTree tree;
    for (int i = 0; i < 100; ++i) {
        tree.insert(i);
    }
    for (auto _ : state) {
        for (int i = 0; i < 100; ++i) {
            tree.search(i);
        }
    }
}

static void BenchmarkRemoveTree(benchmark::State& state) {
    AVLTree tree;
    for (int i = 0; i < 100; ++i) {
        tree.insert(i);
    }
    for (auto _ : state) {
        for (int i = 0; i < 100; ++i) {
            tree.remove(i);
        }
    }
}

BENCHMARK(BenchmarkInsertH);
BENCHMARK(BenchmarkGetH);
BENCHMARK(BenchmarkRemoveH);
BENCHMARK(BenchmarkClearH);
BENCHMARK(BenchmarkAddToHeadL2);
BENCHMARK(BenchmarkAddToTailL2);
BENCHMARK(BenchmarkRemoveFromHeadL2);
BENCHMARK(BenchmarkRemoveFromTailL2);
BENCHMARK(BenchmarkFindL2);
BENCHMARK(BenchmarkRemoveByValueL2);
BENCHMARK(BenchmarkClearL2);
BENCHMARK(BenchmarkAddToHeadL1);
BENCHMARK(BenchmarkAddToTailL1);
BENCHMARK(BenchmarkRemoveHeadL1);
BENCHMARK(BenchmarkRemoveTailL1);
BENCHMARK(BenchmarkSearchL1);
BENCHMARK(BenchmarkRemoveByValueL1);
BENCHMARK(BenchmarkClearL1);
BENCHMARK(BenchmarkAppendArr);
BENCHMARK(BenchmarkInsertMiddleArr);
BENCHMARK(BenchmarkInsertBeginningArr);
BENCHMARK(BenchmarkRemoveLastArr);
BENCHMARK(BenchmarkRemoveFirstArr);
BENCHMARK(BenchmarkGetArr);
BENCHMARK(BenchmarkReplaceArr);
BENCHMARK(BenchmarkFreeArr);
BENCHMARK(BenchmarkEnqueueQue);
BENCHMARK(BenchmarkDequeueQue);
BENCHMARK(BenchmarkClearQue);
BENCHMARK(BenchmarkPushStack);
BENCHMARK(BenchmarkPopStack);
BENCHMARK(BenchmarkClearStack);
BENCHMARK(BenchmarkInsertTree);
BENCHMARK(BenchmarkSearchTree);
BENCHMARK(BenchmarkRemoveTree);

BENCHMARK_MAIN();