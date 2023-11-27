#include "CPePrimitiveShape.h"

namespace engine {
	namespace physics {

		pemaths::CPeMatrix4 CPePrimitiveShape::GetWorldTransform(pecore::CPeEntity& p_owner)
		{
			return m_shapeTransform.GetTransformMatrix() * p_owner.m_transform.GetTransformMatrix();
		}

	}
}