#include "Texture.h"


FlyEngine::Texture::Texture(unsigned int textureID, int textureWidth, int textureHeight, const std::string& texturePath)
{
	id = textureID;
	path = texturePath;
	width = textureWidth;
	height = textureHeight;
}

FlyEngine::Texture::~Texture()
{
	glDeleteTextures(1, &id);
}

/*
void FlyEngine::Texture::Bind(unsigned int slot) const
{
	
}
*/
void FlyEngine::Texture::UnBind() const
{
	glBindTexture(GL_TEXTURE_2D, 0);
}

void FlyEngine::Texture::SetType(std::string type)
{
	this->type = type;
}

unsigned int FlyEngine::Texture::GetID() const
{
	return id;
}

const std::string& FlyEngine::Texture::GetPath()
{
	return path;
}

int FlyEngine::Texture::GetWidth()
{
	return width;
}

int FlyEngine::Texture::GetHeight()
{
	return height;
}

bool FlyEngine::Texture::IsActive()
{
	return isActive;
}
