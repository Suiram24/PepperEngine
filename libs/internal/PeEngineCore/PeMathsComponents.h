#pragma once

#include "PeECSDefinitions.h"
#include "../PeMaths/PeMaths.h"


namespace engine
{
	namespace core
	{
		struct Position
		{
			PECOMPONENT("Position")
			engine::maths::CPeVector3 m_position;

			void PrintString()
			{
				printf("Position : %f,%f,%f \n", m_position.GetX(), m_position.GetY(), m_position.GetZ());
			}
		};

		struct Rotation
		{
			PECOMPONENT("Rotation")
			engine::maths::CPeQuaternion m_rotation;
		};

		struct Scale
		{
			PECOMPONENT("Scale")
			engine::maths::CPeVector3 m_scale;
		};
	}
}

