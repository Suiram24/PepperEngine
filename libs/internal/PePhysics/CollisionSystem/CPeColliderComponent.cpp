#include "CPeColliderComponent.h"

namespace engine {
	namespace physics {

		void CPeColliderComponent::Initialise(pecore::CPeEntity* p_owner, double p_radius)
		{
			m_isActive = true;
			m_owner = p_owner;
			m_radius = p_radius;

			m_owner->AddComponent(this);
		}
		void CPeColliderComponent::SetActive(bool value)
		{
			if (!value)
			{
				m_radius = -1;
				m_owner = nullptr;
			}
		}

		bool CPeColliderComponent::isActive() const
		{
			return m_radius != -1;
		}

		double CPeColliderComponent::GetRadius() const
		{
			return m_radius;
		}

		void CPeColliderComponent::SetRadius(double p_radius)
		{
			m_radius = p_radius;
		}

	}
}