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

		void setMesh(Mesh mesh);
		void setMaterial(Material material);
		Mesh* getMesh();
		Material* getMaterial();
	private:
		Mesh mesh;
		Material material;
	};
}
