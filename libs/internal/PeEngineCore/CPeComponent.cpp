#include "CPeComponent.h"

namespace engine {
	namespace core {

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