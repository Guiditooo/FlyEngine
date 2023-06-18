#include "Renderer.h"
#include <Entity/Entity.h>
#include <GLFW/glfw3.h>

#include <vector>
#include <iostream>

std::list<Entity*> Renderer::renderizableObjectList;
Color* Renderer::bgColor;

void Renderer::DrawRenderizableObjects()
{
	for (auto renderizableObject : renderizableObjectList)		
	{
		renderizableObject->Draw();
	}
}

#pragma region ORDER RENDERIZABLE OBJECTS

bool CompareByDrawLayer(Entity* a, Entity* b)
{
	return a->GetDrawLayer() < b->GetDrawLayer();
}

void Renderer::ReOrderRenderizableList()
{
	renderizableObjectList.sort(CompareByDrawLayer);
}

#pragma endregion

void Renderer::AddToRenderizableList(Entity* newRenderizableObject)
{
	renderizableObjectList.push_back(newRenderizableObject);
}


void Renderer::SetBackgroundColor(Color* newBgColor)
{
	bgColor = newBgColor;
	glClearColor(bgColor->GetColor().r, bgColor->GetColor().g, bgColor->GetColor().b, bgColor->GetColor().a);

	glClear(GL_COLOR_BUFFER_BIT);
}

Color* Renderer::GetBackgroundColor()
{
	return bgColor;
}