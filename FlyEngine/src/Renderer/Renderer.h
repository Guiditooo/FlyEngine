#ifndef RENDERER_H
#define RENDERER_H

#include <list>
#include <FlyFunctions/Color/Color.h>

using namespace FLY_ENGINE;

class Entity;

class Renderer
{
private:
	static Color* bgColor;

	static std::list<Entity*> renderizableObjectList;
	static void ReOrderRenderizableList();
public:
	static void DrawRenderizableObjects();
	static void AddToRenderizableList(Entity* newRenderizableObject);
	
	
	static void SetBackgroundColor(Color* newBgColor);
	static Color* GetBackgroundColor();

};

#endif // !