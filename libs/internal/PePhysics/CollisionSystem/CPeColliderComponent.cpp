#include "CPeColliderComponent.h"

namespace engine {
	namespace physics {

		void CPeColliderComponent::Initialise(pecore::CPeEntity* p_owner, double p_radius)
		{
			m_isActive = true;
			m_owner = p_owner;

			m_owner->AddComponent(this);
		}
		void CPeColliderComponent::SetActive(bool value)
		{
			if (!value)
			{
				m_owner = nullptr;
			}
		}

		bool CPeColliderComponent::isActive() const
		{
			return false;
		}

	}
}