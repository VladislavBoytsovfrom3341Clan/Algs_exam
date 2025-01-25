#include <iostream>
#include <list>

#include "SinglyLinkedList.h"
#include "DoublyLinkedList.h"
#include "VectorStack.h"
#include "LLStack.h"
#include "VectorQueue.h"
#include "ListQueue.h"
#include "DLLDeque.h"

int main()
{
    DLLDeque<int> s = { 666, 2, 4, 5 };
    std::cout << s.front()<<' ' << s.back()<<'\n';
    for (int i = 0; i < 100; i++)
        s.push_back(i);
    std::cout << s.front() << ' ' << s.back() << '\n';
    for (int i = 0; i < 75; i++)
        s.pop_back();
    std::cout << s.front() << ' ' << s.back() << '\n';
}

