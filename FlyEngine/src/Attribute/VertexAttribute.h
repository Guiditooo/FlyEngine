#ifndef VERTEX_ATTRIBUTE_H
#define VERTEX_ATTRIBUTE_H

#include <GLEW/glew.h>
#include <GLFW/glfw3.h>

struct VertexAttribute
{
	unsigned int elementSize = 0;
	unsigned int variableType = 0;
	unsigned int isNormalized = 0;
	unsigned int sizeOfVertex = 0;
	unsigned int offset = 0;
};

#endif // !ATTRIBUTE_H