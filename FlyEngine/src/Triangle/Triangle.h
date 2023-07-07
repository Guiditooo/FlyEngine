#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <Shape/Shape.h>

class Triangle : public Shape
{
private:
	//int* triangleCount;
public:
	Triangle();
	~Triangle();

	//int GetTriangleCount();

	void Draw();
};

#endif // !TRIANGLE_H