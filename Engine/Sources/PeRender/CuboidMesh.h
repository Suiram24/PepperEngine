#ifndef PEENGINE_CUBOID_MESH_H
#define PEENGINE_CUBOID_MESH_H

#include "CPeGraphicalObjects.h"
#include "CPeBluePrints.h"

namespace vk {
	class CuboidMesh : public vk::ModelWatcher {
	public:
        CuboidMesh(vk::GenericRenderer& renderer, std::string texture);
        CuboidMesh(vk::GenericRenderer& renderer);

		void operator=(CuboidMesh const& cuboid);
	private:
		//std::string modelPathSphere = "models/sphere.obj";
	};
}

#endif