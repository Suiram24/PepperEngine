#include "CPeForce.h"

namespace engine {
	namespace physics {

		void CPeForce::Release()
		{
			m_isActive = false;
		}

		bool CPeForce::IsActive() const
		{
			return m_isActive;
		}

	}
}