#include <iostream>

#include "SinglyLinkedList.h"
#include "DoublyLinkedList.h"

int main()
{
    DoublyLinkedList<int> m;
    m.push_front(8);
    std::cout<<m.back()<<m.front();
    
}

