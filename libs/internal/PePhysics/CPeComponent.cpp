#include "CPeComponent.h"

namespace engine {
	namespace physics {

		void CPeComponent::SetActive(bool p_active)
		{
			m_isActive = p_active;
		}

		const CPeEntity* CPeComponent::GetOwner() const
		{
			return m_owner;
		}

		

	}
}