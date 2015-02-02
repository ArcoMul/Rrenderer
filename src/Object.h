#pragma once

#include "Rrenderer.h"
#include "Mesh.h"
#include "Material.h"
#include "Vector3.h"
#include "Matrix4.h"

namespace Rr
{
	class RRENDERER_API Object
	{
	public:
		Object();
		~Object();

		// Sets the one and only mesh of this object
		void setMesh(Mesh mesh);

		// Sets the one and only material of this object
		void setMaterial(Material material);

		void setPosition(Vector3 position);

		Mesh* getMesh();
		Material* getMaterial();
		Vector3 getPosition();
		Matrix4* getModelMatrix();
	private:
		Mesh mesh;
		Material material;
		Matrix4 modelMatrix;
	};
}
