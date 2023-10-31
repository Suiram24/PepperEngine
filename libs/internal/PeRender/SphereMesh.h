#ifndef PEENGINE_SPHERE_MESH_H
#define PEENGINE_SPHERE_MESH_H

#include "CPeGraphicalObjects.h"
#include "CPeBluePrints.h"

namespace vk {
	class SphereMesh : public vk::ModelWatcher {
	public:
        SphereMesh(vk::GenericRenderer& renderer, std::string texture);
        SphereMesh(vk::GenericRenderer& renderer);

		void operator=(SphereMesh const& sphere);
	private:
		//std::string modelPathSphere = "models/sphere.obj";
	};
}

#endif