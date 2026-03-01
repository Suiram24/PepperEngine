#include "CPeColliderComponent.h"

namespace engine {
	namespace physics {
	
		CPeSpherePrimitiveShape& CPeColliderComponent::GetGlobalVolume() {
			return *m_enclosingShape;
		}

		const std::vector<CPePrimitiveShape*>& CPeColliderComponent::GetPrimitives() const
		{
			return m_narrowShapes;
		}

		void CPeColliderComponent::AddPrimitive(CPePrimitiveShape* p_primitive)
		{
			m_narrowShapes.push_back(p_primitive);
		}


	}
}