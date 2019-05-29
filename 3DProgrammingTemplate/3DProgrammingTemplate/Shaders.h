#pragma once
#include <iostream>
#include "Vertex.h"

class Shader
{
public:

	Shader(const std::string& vertexPath, const std::string& fragmentPath);
	~Shader() {};
	uint32_t getId() const;
	const char* getError(uint32_t shader) const;
	void  setupAttribs() const;
	int  getLocation(const char* name);
	void  setInt(int loc, int val); 
	void  setFloat(int loc, float val); 
	void  setVec3(int loc, const glm::vec3& vec); 
	void  setVec4(int loc, const glm::vec4& vec); 
	void  setMatrix(int loc, const glm::mat4& matrix);
	int getMatrix(const char* name);
	void  use();
private:
	uint32_t vertexShader;
	uint32_t fragmentShader;
	uint32_t idShader;
	uint32_t m_vposLoc;
	uint32_t m_vcolorLoc;
	glm::mat4 m_mvp;
};

std::string readString(const std::string& filename);