#include "CPePrimitiveShape.h"

namespace engine {
	namespace physics {

		pemaths::CPeMatrix4 CPePrimitiveShape::GetWorldTransform() const
		{
			return m_shapeTransform.GetTransformMatrix() * m_owner.m_transform.GetTransformMatrix();
		}

		const pemaths::CPeVector3& CPePrimitiveShape::GetWorldPosition()
		{
			if (m_owner.m_transform.GetTransformMatrix() != m_ownerTransformMat) //Compute world position only if the entity mooved
			{
				m_ownerTransformMat = m_owner.m_transform.GetTransformMatrix();
				m_worldPosition = m_shapeTransform.GetTransformMatrix() * m_ownerTransformMat * pemaths::CPeVector3(0, 0, 0);
			}

			return m_worldPosition;
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

		pemaths::CPeVector3 CPePrimitiveShape::ConvertLocalToWorld(const pemaths::CPeVector3& p_localCoordinates) const
		{
			return GetWorldTransform()*p_localCoordinates;
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