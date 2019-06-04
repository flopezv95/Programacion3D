#pragma once
#include "../glm/glm.hpp"

class Entity
{
public:
	virtual ~Entity() {};
	const   glm::vec3& getPosition() const;
	void    setPosition(const glm::vec3& pos);
	const   glm::vec3& getRotation() const;
	const void  setRotation(const glm::vec3& rot);
	const   glm::vec3& getScale() const;
	void   setScale(const glm::vec3& scale);
	void   move(const glm::vec3& vec);
	virtual void update(float deltaTime) {};
	virtual void draw(float deltaTime) {};
private:
	glm::vec3 mPosition;
	glm::vec3 mRotation;
	glm::vec3 mScale;
};