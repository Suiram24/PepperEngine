#include "CPeComponent.h"

namespace engine {
	namespace core {

		void CPeComponent::SetActive(bool p_active)
		{
			m_isActive = p_active;
		}

		CPeEntity& CPeComponent::GetOwner() const
		{
			return *m_owner;
		}

		bool CPeComponent::IsActive() const
		{
			return m_isActive;
		}

		

	}
}