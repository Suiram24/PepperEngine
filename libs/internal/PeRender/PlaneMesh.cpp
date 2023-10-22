#include "PlaneMesh.h"

vk::PlaneMesh::PlaneMesh(vk::GenericRenderer& renderer,  TextureObject& texture) : ModelWatcher(renderer, "models/plane.obj", texture)
{
}

void vk::PlaneMesh::operator=(PlaneMesh const& sphere)
{
	*this = sphere;
}
