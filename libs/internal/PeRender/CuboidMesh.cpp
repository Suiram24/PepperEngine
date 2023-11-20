#include "CuboidMesh.h"

vk::CuboidMesh::CuboidMesh(vk::GenericRenderer& renderer, std::string texture) : ModelWatcher(renderer, "models/companion_cube.obj", texture)
{
}

vk::CuboidMesh::CuboidMesh(vk::GenericRenderer& renderer) : ModelWatcher(renderer, "models/companion_cube.obj")
{
}

void vk::CuboidMesh::operator=(CuboidMesh const& cuboid)
{
	*this = cuboid;
}
