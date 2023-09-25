#include "CPeMovable.h"

namespace engine {
	namespace physics {

		const CPeTransform& CPeMovable::GetTransform() const
		{
			return m_transform;
		}

	}
}