#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <Shape/Shape.h>

class Triangle : public Shape
{
private:
public:
	Triangle();
	~Triangle();
	void Draw() override;
};

#endif // !TRIANGLE_H