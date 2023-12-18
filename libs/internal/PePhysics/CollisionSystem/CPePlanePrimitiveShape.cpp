#include "CPePlanePrimitiveShape.h"

namespace engine {
	namespace physics {

		pemaths::CPeVector3 CPePlanePrimitiveShape::GetNormal() const
		{
			return m_normal;
		}
		double CPePlanePrimitiveShape::GetOffset() const
		{
			return m_offset;
		}

		void CPePlanePrimitiveShape::SetNormal(pemaths::CPeVector3 p_normal)
		{
			m_normal = p_normal;
		}
		void CPePlanePrimitiveShape::SetOffset(double p_offset)
		{
			m_offset = p_offset;
		}

		EShapeTypes CPePlanePrimitiveShape::GetType() const {
			return PLANE;
		}
	}
}