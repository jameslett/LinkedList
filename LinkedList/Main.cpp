
#include <iostream>
#include "LinkedList.h"

class testClass {
public:
	testClass() = default;
	int x = 1;
};

int main()
{
	testClass c;
	Stack<testClass> s;

		s.Push(c);
		s.Erase(s.begin());
		s.Push(c);
		s.Push(c);
		s.Push(c);
		std::cout << s.Size() << std::endl;
		testClass x = s.Pop();
		std::cout << x.x << std::endl;
		std::cout << s[0].x << std::endl;
		


	


	
	


}

