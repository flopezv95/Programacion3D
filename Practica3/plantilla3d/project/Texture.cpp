#ifndef   STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION

#include "Texture.h"
#include "../stb_image.h"
#include "GL/glew.h" 


std::shared_ptr<Texture> Texture::load(const char * filename)
{
	int*comp = NULL; //Variable para la funcion para recuperar la textura
	int reqcomp = 4;
	Texture* myTexture = new Texture;
	unsigned char* arrayBytes = stbi_load(filename, &myTexture->textureSize.x, &myTexture->textureSize.y, comp, reqcomp);
	if (arrayBytes != nullptr)
	{
		glGenTextures(1, &myTexture->Id);
		myTexture->bind();
	}
	return std::shared_ptr<Texture>();
}

uint32_t Texture::getId() const
{
	return Id;
}

const glm::ivec2 & Texture::getSize() const
{
	return textureSize;
}

void Texture::bind() const
{
	glBindTexture(GL_TEXTURE_2D, getId());
}

#endif