#include "CPeColliderComponent.h"

namespace engine {
	namespace physics {
		float CPeColliderComponent::GetRadius() const
		{
			return m_radius;
		}

		void CPeColliderComponent::SetRadius(float p_radius)
		{
			m_radius = p_radius;
		}

	}
}