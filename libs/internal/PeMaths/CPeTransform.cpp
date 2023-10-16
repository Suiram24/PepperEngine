#include "CPeTransform.h"

namespace engine {
	namespace maths {
		const CPeVector3& CPeTransform::GetPosition() const
		{
			return m_position;
		}

		const CPeVector3& CPeTransform::GetOrientation() const
		{
			return m_orientation;
		}

		const CPeVector3& CPeTransform::GetSize() const
		{
			return m_size;
		}

		void CPeTransform::SetPosition(const CPeVector3& p_position)
		{
			m_position = p_position;
		}

		void CPeTransform::SetOrientation(const CPeVector3& p_orientation)
		{
			m_orientation = p_orientation;
		}

		void CPeTransform::SetSize(const CPeVector3& p_size)
		{
			m_size = p_size;
		}
	}
}