#include "Model.h"
#include "Mesh.h"

Model::Model(const std::shared_ptr<Mesh>& mesh)
{
	myMesh = mesh;
}

void Model::draw(float deltaTime)
{
	myMesh->draw(deltaTime);
}
