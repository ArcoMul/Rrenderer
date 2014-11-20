#pragma once

#include "Rrenderer.h"
#include "Mesh.h"
#include "Material.h"

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

		Mesh* getMesh();
		Material* getMaterial();
	private:
		Mesh mesh;
		Material material;
	};
}
