#include "CPeBoxPrimitiveShape.h"

namespace engine {
	namespace physics {

		pemaths::CPeVector3 CPeBoxPrimitiveShape::GetHalfSize() const
		{
			return m_halfsize;
		}

		void CPeBoxPrimitiveShape::SetHalfSize(pemaths::CPeVector3 p_halfsize)
		{
			m_halfsize = p_halfsize;
		}

		void CPeBoxPrimitiveShape::GotAbstracted() {}
	}
}