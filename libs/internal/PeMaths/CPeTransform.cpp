#include "CPeTransform.h"

namespace engine {
	namespace maths {
		const CPeVector3& CPeTransform::GetPosition() const
		{
			return m_position;
		}

        CPeVector3 CPeTransform::GetPositionPoint(const CPeVector3& p_localPoint)
        {
			UpdateTransformMatrix();
			if (!m_transformMatrix.IsInversible()) return CPeVector3(0,0,0); 
			CPeVector3 globalPoint = m_transformMatrix.Inverse()*p_localPoint;
            return globalPoint;
        }

        const CPeQuaternion& CPeTransform::GetOrientation() const
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

		void CPeTransform::SetOrientation(const CPeQuaternion& p_orientation)
		{
			m_orientation = p_orientation;
		}

        void CPeTransform::UpdateTransformMatrix()
        {
			m_transformMatrix = CPeMatrix4(m_orientation.ToMatrix3(),m_position);
        }

        void CPeTransform::SetSize(const CPeVector3& p_size)
		{
			m_size = p_size;
		}
	}
}