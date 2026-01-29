#pragma once

#include "../PeEngineCore/PeEngineCore.h"
#include <string.h>

namespace engine
{
	namespace render
	{
		struct MeshRenderer
		{
			PECOMPONENT("MeshRenderer")
			int32_t ModelWatcherID;
		};

		struct MeshPlaceholder
		{
			PECOMPONENT("MeshPlaceholder")
			char m_modelPath[128];
			char m_texturePath[128];

			MeshPlaceholder& operator=(const MeshPlaceholder& other)
			{
				std::strcpy(m_modelPath,other.m_modelPath);
				std::strcpy(m_texturePath, other.m_texturePath);
				return *this;
			}
		};
	}
}

