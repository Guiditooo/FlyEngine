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

void FlyEngine::Texture::Bind(unsigned int slot) const
{
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(GL_TEXTURE_2D, id);
}

void FlyEngine::Texture::UnBind() const
{
	glBindTexture(GL_TEXTURE_2D, 0);
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
