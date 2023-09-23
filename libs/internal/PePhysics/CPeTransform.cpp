#include "CPeTransform.h"

namespace engine {
	namespace physics {
		const pemaths::CPeVector3& CPeTransform::GetPosition() const
		{
			return m_position;
		}

		const pemaths::CPeVector3& CPeTransform::GetOrientation() const
		{
			return m_orientation;
		}

		const pemaths::CPeVector3& CPeTransform::GetSize() const
		{
			return m_size;
		}

		void CPeTransform::SetPosition(const pemaths::CPeVector3& p_position)
		{
			m_position = p_position;
		}

		void CPeTransform::SetOrientation(const pemaths::CPeVector3& p_orientation)
		{
			m_orientation = p_orientation;
		}

		void CPeTransform::SetSize(const pemaths::CPeVector3& p_size)
		{
			m_size = p_size;
		}
	}
}