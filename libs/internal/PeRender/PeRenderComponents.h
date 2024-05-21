#pragma once

#include "../PeEngineCore/PeEngineCore.h"

struct MeshRenderer
{
	int32_t ModelWatcherID;
};

struct MeshPlaceholder
{
	std::string m_modelPath;
	std::string m_texturePath;
};