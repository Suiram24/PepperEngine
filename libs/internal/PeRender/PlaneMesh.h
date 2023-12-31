#ifndef PEENGINE_PLANE_MESH_H
#define PEENGINE_PLANE_MESH_H

#include "CPeGraphicalObjects.h"
#include "CPeBluePrints.h"

namespace vk {
	class PlaneMesh : public vk::ModelWatcher {
	public:
		PlaneMesh(vk::GenericRenderer& renderer, std::string texture);
		PlaneMesh(vk::GenericRenderer& renderer);

		void operator=(PlaneMesh const& plane);
	private:
		//std::string modelPathSphere = "models/sphere.obj";
	};
}

#endif