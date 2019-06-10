
#include "Entity.h"

const glm::vec3 & Entity::getPosition() const
{
	return mPosition;
}

void Entity::setPosition(const glm::vec3 & pos)
{
	mPosition = pos;
}

const glm::vec3 & Entity::getRotation() const
{
	return mRotation;
}

const void Entity::setRotation(const glm::vec3 & rot)
{
	mRotation = rot;
}

const glm::vec3 & Entity::getScale() const
{
	return mScale;
}

void Entity::setScale(const glm::vec3 & scale)
{
	mScale = scale;
}

void Entity::move(const glm::vec3 & vec)
{
	mPosition = getPosition() + vec;
}
