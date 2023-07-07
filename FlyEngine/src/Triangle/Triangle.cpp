#include "Triangle.h"

#include <iostream>

//int Triangle::triangleCount = 0;

Triangle::Triangle()
{
	//triangleCount++;
}

Triangle::~Triangle()
{
	//triangleCount--;
}

/*int Triangle::GetTriangleCount()
{
	return triangleCount;
}*/

void Triangle::Draw()
{
	std::cout << " Estoy dibujando un triangulo \n";
}
