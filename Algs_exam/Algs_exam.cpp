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

template<typename T>
void print_vector(const std::vector<T>& v)
{
    for (const auto& i : v)
        std::cout << i << ' ';
    std::cout << '\n';
}

int main()
{
    std::vector<int> v = { 5, 4, 8, 9, 4, 5, 3, 1, 2, 0, 8 };
    MaxHeap<int> h(v);
    print_vector(h.deheap());
    h.insert(6);
    print_vector(h.deheap());
    h.pop_max();
    print_vector(h.deheap());
    h.pop_max();
    print_vector(h.deheap());
    h.insert(666);
    print_vector(h.deheap());
}

