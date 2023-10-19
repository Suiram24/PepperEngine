#include "SphereMesh.h"

vk::SphereMesh::SphereMesh(vk::GenericRenderer& renderer) : ModelWatcher(renderer, "models/sphere.obj")
{
}

void vk::SphereMesh::operator=(SphereMesh const& sphere)
{
	*this = sphere;
}
