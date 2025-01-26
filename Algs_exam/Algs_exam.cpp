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

template<typename T>
void print_vector(const std::vector<T>& v)
{
    for (const auto& i : v)
        std::cout << i << ' ';
    std::cout << '\n';
}

//int main()
//{
//    std::vector<int> v = { 5, 4, 8, 9, 4, 5, 3, 1, 2, 0, 8 };
//    AVLTree<int> avl;
//    for (auto& i : v)
//    {
//        avl.insert(i);
//        std::cout << avl.in_order()<<'\n';
//    }
//    for (auto& i : v)
//    {
//        avl.remove(i);
//        std::cout << avl.in_order() << '\n';
//    }
//}

