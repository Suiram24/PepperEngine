#include "CPeComponent.h"

namespace engine {
	namespace physics {

		void CPeComponent::SetActive(bool p_active)
		{
			m_isActive = p_active;
		}

		CPeEntity& CPeComponent::GetOwner()
		{
			return m_owner;
		}

		

	}
}