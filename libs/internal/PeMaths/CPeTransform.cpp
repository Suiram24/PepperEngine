#include "CPeTransform.h"
#include <cassert>

namespace engine {
	namespace maths {
		const CPeVector3& CPeTransform::GetPosition() const
		{
			return m_position;
		}

        CPeVector3 CPeTransform::GetPositionPoint(const CPeVector3& p_localPoint)
        {
            return m_transformMatrix * p_localPoint;
        }

		CPeVector3 CPeTransform::GetPositionPointInLocal(const CPeVector3& p_globalPoint) const
		{
			if (!m_transformMatrix.IsInversible()) {
				assert("Matrix is not inversible" && false);
				return CPeVector3(0, 0, 0);
			}
			return m_transformMatrix * p_globalPoint;
		}

        const CPeQuaternion& CPeTransform::GetOrientation() const
		{
			return m_orientation;
		}

		const CPeVector3& CPeTransform::GetSize() const
		{
			return m_size;
		}

		CPeMatrix4 CPeTransform::GetTransformMatrix() const
		{
			return m_transformMatrix;
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