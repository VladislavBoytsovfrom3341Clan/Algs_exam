#include <iostream>
#include <list>

#include "SinglyLinkedList.h"
#include "DoublyLinkedList.h"
#include "VectorStack.h"
#include "LLStack.h"

int main()
{
    LLStack<int> s = { 1, 2, 4, 5 };
    std::cout << s.top() << '\n';
    s.pop();
    std::cout << s.top()<<'\n';
    int a = 9;
    s.push(a);
    std::cout << s.top();
}

