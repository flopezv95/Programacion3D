
#include "World.h"
#include "Entity.h"
#include "Camera.h"


void World::addEntity(const std::shared_ptr<Entity>& entity)
{
	myEntityList.push_back(entity);
	if (std::shared_ptr<Camera> camera = std::dynamic_pointer_cast<Camera>(entity))
	{
		myCameraList.push_back(camera);
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

void World::update(float deltaTime)
{
	for (std::shared_ptr<Entity> entity : myEntityList)
	{
		entity.get()->update(deltaTime);
	}
}

void World::draw(float deltaTime, float angle)
{
	for (std::shared_ptr<Camera> camera : myCameraList)
	{
		camera.get()->prepare();

		for (std::shared_ptr<Entity> entity : myEntityList)
		{
			entity.get()->draw(deltaTime, angle);
		}
	}
}
