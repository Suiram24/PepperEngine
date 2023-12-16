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

		pemaths::CPeVector3 CPePrimitiveShape::ConvertWorldToLocal(const pemaths::CPeVector3& p_worldCoordinates) const
		{
			pemaths::CPeMatrix4 worldTransform = GetWorldTransform();
			if (worldTransform.IsInversible()) {
				pemaths::CPeMatrix4 localTransform = GetWorldTransform().Inverse();
				
				return localTransform * p_worldCoordinates;
			}
			return pemaths::CPeVector3();
		}

		const pecore::CPeEntity& CPePrimitiveShape::GetOwningEntity() const
		{
			return m_owner;
		}


		CPeRigidBody* CPePrimitiveShape::GetRigidbody() const
		{
			return m_owner.GetComponent<CPeRigidBody>();
		}
	}
}