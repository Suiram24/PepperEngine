#ifndef PEENGINE_SPHERE_MESH_H
#define PEENGINE_SPHERE_MESH_H

#include "CPeGraphicalObjects.h"

namespace vk {
	class SphereMesh : public vk::ModelWatcher {
	public:
        SphereMesh(vk::GenericRenderer& renderer);
	private:
		//std::string modelPathSphere = "models/sphere.obj";
	};
}

#endif