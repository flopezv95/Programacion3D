#pragma once
#include "../glm/glm.hpp"
#include "Entity.h"

class Camera :public Entity
{
public:
	Camera();
	const glm::mat4& getProjection() const; 
	void setProjection(const glm::mat4& proj);
	const glm::ivec4& getViewport() const;
	void setViewport(const glm::ivec4& vp);
	const glm::vec3& getClearColor() const;
	void setClearColor(const glm::vec3& color);
	void prepare();
private:
	glm::mat4 mProjection;
	glm::vec3 mClearColor;
	glm::ivec4 mViewPort;
};