#include "SphereMesh.h"

vk::SphereMesh::SphereMesh(vk::GenericRenderer& renderer, TextureObject& texture) : ModelWatcher(renderer, "models/sphere.obj", texture)
{
}

void vk::SphereMesh::operator=(SphereMesh const& sphere)
{
	*this = sphere;
}
