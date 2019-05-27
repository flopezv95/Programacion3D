#pragma once
#include <iostream>
#include <array>
#include <vector>

class Vertex;
class Shader;

class Buffer
{
public:
	Buffer(std::vector<Vertex> myVertex, std::vector<unsigned int> indices);
	void draw(Shader& shader);
private:
	std::array<uint32_t, 2>m_ids;

	GLuint m_VAO;
	GLuint m_IBO;
	GLuint m_VBO;

};