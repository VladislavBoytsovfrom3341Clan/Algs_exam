#include <iostream>

#include "SinglyLinkedList.h"
#include "DoublyLinkedList.h"

int main()
{
    SinglyLinkedList<int> s;
    for (int i = 0; i < 20; i++)
        s.push_back(i);
    for (auto it = s.begin(); it != s.end(); ++it)
        std::cout << *it << ' ';

}

