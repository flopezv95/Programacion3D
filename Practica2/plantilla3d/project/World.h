#pragma once
#include <iostream>
#include <vector>

class Camera;
class Entity;

class World
{
	void addEntity(const std::shared_ptr<Entity>& entity);
	void removeEntity(const std::shared_ptr<Entity>& entity);
	size_t getNumEntities() const;
	const std::shared_ptr<Entity>& getEntity(size_t index) const;
	std::shared_ptr<Entity>& getEntity(size_t index);
	void update(float deltaTime); 
	void draw(float deltaTime, float angle);

private:
	std::vector <std::shared_ptr<Entity>> myEntityList;
	std::vector <std::shared_ptr<Camera>> myCameraList;
};