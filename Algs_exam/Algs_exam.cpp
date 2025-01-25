#include <iostream>
#include <list>

#include "SinglyLinkedList.h"
#include "DoublyLinkedList.h"

int main()
{
    DoublyLinkedList<int> s;
    for (int i = 0; i < 20; i++)
        s.push_back(i);
    for (auto it = s.begin(); it != s.end(); ++it)
        std::cout << *it << ' ';
    std::cout << '\n';
    s.insert(--(--s.end()), -11);
    for (auto& i : s)
        std::cout << i << ' ';
}

