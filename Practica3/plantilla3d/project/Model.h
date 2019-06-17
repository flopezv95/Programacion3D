#pragma once
#include "Entity.h"
#include <iostream>

class Mesh;

class Model : public Entity
{
public:
	Model(const std::shared_ptr<Mesh>& mesh); 
	virtual void draw(float deltaTime, float angle, bool rotateInTime = false) override;
private:
	std::shared_ptr<Mesh> myMesh;
};