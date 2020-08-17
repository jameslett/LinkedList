
#include <iostream>
#include "LinkedList.h"
int main()
{
    Stack stack;
    stack.Push(1);
    stack.Push(2);
    stack.Push(3);
    stack.Pop();
    stack.Pop();


    for (auto it = stack.begin(); it != stack.end();++it) {
        std::cout << it.GetElement()->GetVal();
        
    }
    
}

