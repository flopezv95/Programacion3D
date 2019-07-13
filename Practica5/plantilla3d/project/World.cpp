
#include "World.h"
#include "Entity.h"
#include "Camera.h"
#include "../project/State.h"

void World::addEntity(const std::shared_ptr<Entity>& entity)
{
	myEntityList.push_back(entity);
	if (std::shared_ptr<Camera> camera = std::dynamic_pointer_cast<Camera>(entity))
	{
		myCameraList.push_back(camera);
	}
	else if (std::shared_ptr<Light> camera = std::dynamic_pointer_cast<Light>(entity))
	{
		m_myLightList.push_back(camera);
	}

}

void World::removeEntity(const std::shared_ptr<Entity>& entity)
{
	std::vector<std::shared_ptr<Entity>>::iterator it = std::find(myEntityList.begin(), myEntityList.end(), entity);
	if (it != myEntityList.end())
	{
		myEntityList.erase(it);
	}

	std::vector<std::shared_ptr<Camera>>::iterator it2 = std::find(myCameraList.begin(), myCameraList.end(), entity);
	if (it2 != myCameraList.end())
	{
		myCameraList.erase(it2);
	}

	std::vector<std::shared_ptr<Light>>::iterator it3 = std::find(m_myLightList.begin(), m_myLightList.end(), entity);
	if (it3 != m_myLightList.end())
	{
		m_myLightList.erase(it3);
	}

}

size_t World::getNumEntities() const
{
	return myEntityList.size();
}

const std::shared_ptr<Entity>& World::getEntity(size_t index) const
{
	return myEntityList.at(index);
}

std::shared_ptr<Entity>& World::getEntity(size_t index)
{
	return myEntityList.at(index);
}

const glm::vec3& World::getAmbient() 
{
	return m_ambientLight;
}

void World::setAmbient(const glm::vec3 & ambient)
{
	m_ambientLight = ambient;
}

void World::update(float deltaTime)
{
	for (std::shared_ptr<Entity> entity : myEntityList)
	{
		entity.get()->update(deltaTime);
	}
}

void World::draw(float deltaTime, float angle, bool rotateInTime)
{
	for (std::shared_ptr<Light> light : m_myLightList)
	{
		State::lights.push_back(light);
	}
	State::ambient = m_ambientLight;

	for (std::shared_ptr<Camera> camera : myCameraList)
	{
		camera.get()->prepare();

		for (std::shared_ptr<Entity> entity : myEntityList)
		{
			entity.get()->draw(deltaTime, angle, rotateInTime);
		}
	}
}
