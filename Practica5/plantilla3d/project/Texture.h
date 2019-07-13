#pragma once
#include <iostream>
#include <vector>
#include "../glm/glm.hpp"

class Texture
{
public:
	static std::shared_ptr<Texture> load(const char* filename);
	uint32_t     getId() const;
	const glm::ivec2&    getSize() const;
	void      bind() const;
	uint32_t Id;
	glm::ivec2 textureSize;
};