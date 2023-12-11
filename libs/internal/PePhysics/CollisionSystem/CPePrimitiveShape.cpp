#include "CPePrimitiveShape.h"

namespace engine {
	namespace physics {

		pemaths::CPeMatrix4 CPePrimitiveShape::GetWorldTransform() const
		{
			return m_shapeTransform.GetTransformMatrix() * m_owner.m_transform.GetTransformMatrix();
		}

		pemaths::CPeVector3 CPePrimitiveShape::GetWorldPosition() const
		{
			return GetWorldTransform() * pemaths::CPeVector3(0, 0, 0);
		}
	}
}