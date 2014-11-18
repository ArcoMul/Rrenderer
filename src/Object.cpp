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

void Rr::Object::setMaterial(Material material)
{
	this->material = material;
}

Rr::Mesh* Rr::Object::getMesh()
{
	return &this->mesh;
}

Rr::Material* Rr::Object::getMaterial()
{
	return &this->material;
}
