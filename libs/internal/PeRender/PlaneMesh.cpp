#include "PlaneMesh.h"

vk::PlaneMesh::PlaneMesh(vk::GenericRenderer& renderer,  std::string texture) : ModelWatcher(renderer, "models/plane.obj", texture)
{
}

vk::PlaneMesh::PlaneMesh(vk::GenericRenderer& renderer) : ModelWatcher(renderer, "models/plane.obj")
{
}

void vk::PlaneMesh::operator=(PlaneMesh const& sphere)
{
	*this = sphere;
}
