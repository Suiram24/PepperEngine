#include "CPePlanePrimitiveShape.h"

namespace engine {
	namespace physics {

		pemaths::CPeVector3 CPePlanePrimitiveShape::GetNormal() const
		{
			return m_normal;
		}
		pemaths::CPeVector3 CPePlanePrimitiveShape::GetOffset() const
		{
			return m_offset;
		}

		void CPePlanePrimitiveShape::SetNormal(pemaths::CPeVector3 p_normal)
		{
			m_normal = p_normal;
		}
		void CPePlanePrimitiveShape::SetOffset(pemaths::CPeVector3 p_offset)
		{
			m_offset = p_offset;
		}

		void CPePlanePrimitiveShape::GotAbstracted() {}
	}
}