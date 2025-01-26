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

int main()
{
    TwoStackDeque<int, LLStack> s = {666};
    std::cout << s.front()<<' ' << s.back()<<'\n';
    for (int i = 0; i < 100; i++)
        s.push_front(i);
    std::cout << s.front() << ' ' << s.back() << '\n';
    for (int i = 0; i < 75; i++)
        s.pop_back();
    std::cout << s.front() << ' ' << s.back() << '\n';

    /*SinglyLinkedList<int> s;
    s.push_back(7);
    s.pop_back();
    std::cout << s.empty();*/
}

