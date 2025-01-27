#include <iostream>
#include <list>
#include <stack>
#include <deque>

#include "SinglyLinkedList.h"
#include "DoublyLinkedList.h"
#include "VectorStack.h"
#include "LLStack.h"
#include "VectorQueue.h"
#include "ListQueue.h"
#include "DLLDeque.h"
#include "TwoStackDeque.h"
#include "InsertionSort.h"
#include "mergeSort.h"
#include "QuickSort.h"
#include "CountingSort.h"
#include "MaxHeap.h"
#include "AVLTree.h"
#include "BinarySearchTree.h"
#include "RBTree.h"
#include "UniversalHash.h"
#include "ChainHashTable.h"

template<typename T>
void print_vector(const std::vector<T>& v)
{
    for (const auto& i : v)
        std::cout << i << ' ';
    std::cout << '\n';
}

int main()
{
    ChainHashTable<int, int, std::list<std::pair<int, int>>> h(100);
    for (int i = 0; i < 300; i++)
        h.insert(i, i);
    h.print();

    DoublyLinkedList<std::pair<int, int>> d = { {1, 0}, {2, 9} };
    for (auto& i : d)
        std::cout << i.first << ' '<<i.second<<'\n';
}

