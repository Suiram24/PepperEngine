#include "CPeParticleContact.h"
#include "CPeColliderComponent.h"

namespace engine {
	namespace physics {

		void CPeParticleContact::ResetValues()
		{
			m_contactNormal = ComputeContactNormal();
			m_penetration = ComputePenetration();
			m_separatingSpeed = ComputeSeparatingSpeed();
			m_separatingVelocity = ComputeSeparatingVelocity();
		}

		void CPeParticleContact::Resolve(double p_timeStep)
		{
			ResetValues();

			if (!IsContactAtRest(p_timeStep))
			{
				ResolveVelocity();
			}
			ResolvePenetration();
		}

		bool CPeParticleContact::CompareContactSeparationSpeed(CPeParticleContact* p_contact1, CPeParticleContact* p_contact2)
		{
			return p_contact1->GetSeparatingSpeed() < p_contact2->GetSeparatingSpeed();
		}

		double CPeParticleContact::GetSeparatingSpeed() const
		{
			return m_separatingSpeed;
		}


		double CPeParticleContact::ComputePenetration() const
		{
			return -CPeParticleContact::DistanceBetweenParticle(*m_particleA, *m_particleB);
		}

		double CPeParticleContact::DistanceBetweenParticle(CPeParticle& p_particleA, CPeParticle& p_particleB)
		{
			double r1 = p_particleA.GetOwner().GetComponent<CPeColliderComponent>()->GetRadius();
			double r2 = p_particleB.GetOwner().GetComponent<CPeColliderComponent>()->GetRadius();

			double dist = p_particleA.GetTransform().GetPosition().DistanceTo(p_particleB.GetTransform().GetPosition());

			return dist - r1 - r2;
		}


		pemaths::CPeVector3 CPeParticleContact::ComputeContactNormal() const
		{
			return (m_particleA->GetTransform().GetPosition() - m_particleB->GetTransform().GetPosition()).NormalizeVector();
		}

		pemaths::CPeVector3 CPeParticleContact::ComputeSeparatingVelocity() const
		{
			return m_contactNormal * ComputeSeparatingSpeed();
		}
		
		double CPeParticleContact::ComputeSeparatingSpeed() const
		{
			return pemaths::CPeVector3::ScalarProduct(m_particleA->GetVelocity() - m_particleB->GetVelocity(),m_contactNormal);
		}


		void CPeParticleContact::ResolveVelocity()
		{
			double k = (m_restitution + 1) * m_separatingSpeed/ (m_particleA->GetMassInverse() + m_particleB->GetMassInverse());
			m_particleA->SetVelocity(m_particleA->GetVelocity() - (m_contactNormal * k * m_particleA->GetMassInverse()));
			m_particleB->SetVelocity(m_particleB->GetVelocity() + (m_contactNormal * k * m_particleB->GetMassInverse()));
		}

		void CPeParticleContact::ResolvePenetration()
		{
			double d = m_penetration;
			double mA = m_particleA->GetMass();
			double mB = m_particleB->GetMass();

			if (mA != -1 && mB != -1)
			{
				m_particleA->SetPosition(m_particleA->GetTransform().GetPosition() + (m_contactNormal * (d * mB / (mA + mB))));
				m_particleB->SetPosition(m_particleB->GetTransform().GetPosition() - (m_contactNormal * (d * mA / (mA + mB))));
			}
			else if (mA == -1)
			{
				m_particleB->SetPosition(m_particleB->GetTransform().GetPosition() - (m_contactNormal * d));
			}
			else if (mB == -1)
			{
				m_particleA->SetPosition(m_particleA->GetTransform().GetPosition() + (m_contactNormal * d));
			}

		}

		bool CPeParticleContact::IsContactAtRest(double p_timeStep) const
		{
			return pemaths::CPeVector3::OrthographicProjection((m_particleA->GetGravity() * p_timeStep), m_separatingVelocity).GetNorm() > m_separatingVelocity.GetNorm();
		}

	}
}