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
    print_vector(v);
    insertionSort(v.begin()+2, v.end() - 1);
    print_vector(v);
}

