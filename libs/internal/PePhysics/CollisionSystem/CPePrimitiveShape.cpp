#include "CPePrimitiveShape.h"

namespace engine {
	namespace physics {

		pemaths::CPeMatrix4 CPePrimitiveShape::GetWorldTransform()
		{
			return m_shapeTransform.GetTransformMatrix() * m_owner.m_transform.GetTransformMatrix();
		}

	}
}