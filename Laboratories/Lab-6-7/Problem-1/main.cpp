#include <iostream>
#include <crtdbg.h>

#include "Shape.h"
#include "Circle.h"
#include "Square.h"

void exercise1() 
{
	// TODO your code here
	Circle c1{ 10, 10, 1 };
	Shape* c2{ new Circle{0, 0, 100 } };
	Circle c3{ -10, 0, 2 };

	Shape *s1{ new Square{ 0, 0, 2 }};
	Square s2{ 10, 20, 17 };
	Square s3{ 9, 100, 0.3 };

	// 1. create a polymorphic static array shapes with 6 elements that holds c1, c2, c3 and s1, s2 and s3

	Shape* shapes[] = { &c1, c2, &c3, s1, &s2, &s3 };
	const int numShapes = sizeof(shapes) / sizeof(shapes[0]);
	for (int i = 0; i < numShapes; i++)
		std::cout << shapes[i]->toString() << std::endl;

	
	// 2. display all the elements that have an area greater than 10

	for (int i = 0; i < numShapes; i++)
	{
		if (shapes[i]->area() > 10)
		{
			std::cout << "Shape at index " << i << " has area greater than 10: ";
			std::cout << shapes[i]->toString() << std::endl;
		}
	}

	
		
	// 3. display all the circles from the array shapes

	for (int i = 0; i < numShapes; i++)
	{
		if (dynamic_cast<Circle*>(shapes[i]))
		{
			std::cout << "Circle at index " << i << ": ";
			std::cout << shapes[i]->toString() << std::endl;
		}
	}

		
	delete s1;
	delete c2;
}

int main() 
{

	exercise1();
	_CrtDumpMemoryLeaks();
	return 0;
}

