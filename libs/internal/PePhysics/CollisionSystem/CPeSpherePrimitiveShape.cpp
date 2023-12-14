#include "CPeSpherePrimitiveShape.h"

namespace engine {
	namespace physics {

		double CPeSpherePrimitiveShape::GetRadius() const
		{
			return m_radius;
		}

		void CPeSpherePrimitiveShape::SetRadius(double p_radius)
		{
			m_radius = p_radius;
		}

		EShapeTypes CPeSpherePrimitiveShape::GetType() const{
			return SPHERE;
		}
	}
}