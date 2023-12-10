#include "CPeColliderComponent.h"

namespace engine {
	namespace physics {

		//void CPeColliderComponent::Initialise(pecore::CPeEntity* p_owner, double p_radius)
		//{
		//	m_isActive = true;
		//	m_owner = p_owner;
		//	m_radius = p_radius;

		//	m_owner->AddComponent(this);
		//}

		pemaths::CPeVector3 CPeColliderComponent::GetBoundingSphereCenter() const
		{
			return GetOwner().m_transform.GetPosition() + m_boundingSphere.GetOffset();
		}

		double CPeColliderComponent::GetBoundingSphereRadius() const
		{
			return m_boundingSphere.GetRadius();
		}

	}
}