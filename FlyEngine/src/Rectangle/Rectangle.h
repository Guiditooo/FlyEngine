#ifndef RECTANGLE_H
#define RECTANGLE_H

#include <Shape/Shape.h>

class Rectangle : public Shape
{
private:
public:
	Rectangle();
	~Rectangle();
	void Draw() override;
};

#endif // !RECTANGLE_H