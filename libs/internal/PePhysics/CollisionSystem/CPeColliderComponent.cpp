#include "CPeColliderComponent.h"

namespace engine {
	namespace physics {
		double CPeColliderComponent::GetRadius() const
		{
			m_owner;
			return m_radius;
		}

		void CPeColliderComponent::SetRadius(double p_radius)
		{
			m_radius = p_radius;
		}

	}
}