#include "CPeParticleContact.h"
#include "CPeColliderComponent.h"

namespace engine {
	namespace physics {

		void CPeParticleContact::Resolve(float p_duration)
		{
			m_contactNormal = ComputeContactNormal();
			m_separatingVelocity = ComputeSeparatingVelocity();
			m_separatingSpeed = ComputeSeparatingSpeed();

			if (!IsContactAtRest(p_duration))
			{
				ResolveVelocity();
			}
			ResolvePenetration();
		}

		bool CPeParticleContact::CompareContactSeparationSpeed(CPeParticleContact* p_contact1, CPeParticleContact* p_contact2)
		{
			return p_contact1->GetSeparatingSpeed() < p_contact2->GetSeparatingSpeed();
		}

		float CPeParticleContact::GetSeparatingSpeed() const
		{
			return m_separatingSpeed;
		}


		float CPeParticleContact::ComputePenetration() const
		{
			return -CPeParticleContact::DistanceBetweenParticle(*m_particleA, *m_particleB);
		}

		float CPeParticleContact::DistanceBetweenParticle(CPeParticle& p_particleA, CPeParticle& p_particleB)
		{
			float r1 = p_particleA.GetOwner().GetComponent<CPeColliderComponent>()->GetRadius();
			float r2 = p_particleB.GetOwner().GetComponent<CPeColliderComponent>()->GetRadius();

			float dist = p_particleA.GetTransform().GetPosition().DistanceTo(p_particleB.GetTransform().GetPosition());

			return dist - r1 - r2;
		}


		pemaths::CPeVector3 CPeParticleContact::ComputeContactNormal() const
		{
			return (m_particleA->GetTransform().GetPosition() - m_particleB->GetTransform().GetPosition()).NormalizeVector();
		}

		pemaths::CPeVector3 CPeParticleContact::ComputeSeparatingVelocity() const
		{
			return m_particleA->GetVelocity() - m_particleB->GetVelocity();
		}
		
		float CPeParticleContact::ComputeSeparatingSpeed() const
		{
			return pemaths::CPeVector3::ScalarProduct(m_separatingVelocity,m_contactNormal);
		}


		void CPeParticleContact::ResolveVelocity()
		{
			float k = (m_restitution + 1) * m_separatingSpeed/ (m_particleA->GetMassInverse() + m_particleB->GetMassInverse());
			m_particleA->SetVelocity(m_particleA->GetVelocity() - (m_contactNormal * k * m_particleA->GetMassInverse()));
			m_particleB->SetVelocity(m_particleB->GetVelocity() - (m_contactNormal * k * m_particleB->GetMassInverse()));
		}

		void CPeParticleContact::ResolvePenetration()
		{
			float d = m_penatration;
			float mA = m_particleA->GetMass();
			float mB = m_particleB->GetMass();

			m_particleA->SetPosition(m_particleA->GetTransform().GetPosition() + (m_contactNormal * (d * mB / (mA + mB))));
			m_particleB->SetPosition(m_particleB->GetTransform().GetPosition() + (m_contactNormal * (d * mA / (mA + mB))));
		}

		bool CPeParticleContact::IsContactAtRest(float p_duration) const
		{
			return pemaths::CPeVector3::OrthographicProjection((m_particleA->GetGravity() * p_duration), m_separatingVelocity).GetNorm() > m_separatingVelocity.GetNorm();
		}

	}
}