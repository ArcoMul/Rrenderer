#include "Object.h"

Rr::Object::Object()
{
}

Rr::Object::~Object()
{
}

void Rr::Object::setMesh(Mesh mesh)
{
	this->mesh = mesh;
}

Rr::Mesh* Rr::Object::getMesh()
{
	return &this->mesh;
}

void Rr::Object::setMaterial(Material material)
{
	this->material = material;
}

Rr::Material* Rr::Object::getMaterial()
{
	return &this->material;
}

void Rr::Object::setPosition(Rr::Vector3 position)
{
	modelMatrix[3] = position.x();
	modelMatrix[7] = position.y();
	modelMatrix[11] = position.z();
}

Rr::Vector3 Rr::Object::getPosition()
{
	return Rr::Vector3(modelMatrix[3], modelMatrix[7], modelMatrix[11]);
}

Rr::Matrix4* Rr::Object::getModelMatrix()
{
	return &modelMatrix;
}