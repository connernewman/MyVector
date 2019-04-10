#include <iostream>

#include "MyVector.h"

int main()
{
	MyVector<int> v(10);
	for(int i = 0; i < 10; ++i)
		v.at(i) = i;

	MyVector<int> v2 = {1, 2, 3};
	std::cout << "v2: ";
	for(int i = 0; i < v2.size(); ++i)
		std::cout << v2[i] << " ";
	std::cout << "\n";

	v2 = v;
	std::cout << "v2 = v;\nv2: ";
	for(int i = 0; i < v2.size(); ++i)
		std::cout << v2[i] << " ";
	std::cout << "\n";
}
