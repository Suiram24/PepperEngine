#include "CPeParticle.h"

namespace engine {
	namespace physics {
		double CPeParticle::GetMassInverse() const
		{
			return m_massInverse;
		}

		pemaths::CPeTransform& CPeParticle::GetTransform()
		{
			return m_owner.m_transform;
		}


		const pemaths::CPeVector3& CPeParticle::GetVelocity() const
		{
			return m_velocity;
		}

		const pemaths::CPeVector3& CPeParticle::GetAcceleration() const
		{
			return m_acceleration;
		}

		void CPeParticle::SetMassInverse(double p_massInverse)
		{
			if (p_massInverse < 0.)
			{
				throw "A mass inverse cannot have negative value.";
			}
			m_massInverse = p_massInverse;
		}

		void CPeParticle::SetMass(double p_mass)
		{
			if (p_mass <= 0.)
			{
				throw "A mass cannot have zero or negative value.";
			}
			SetMassInverse(1 / p_mass);
		}

		void CPeParticle::SetVelocity(const pemaths::CPeVector3& p_velocity)
		{
			m_velocity = p_velocity;
		}

		void CPeParticle::SetAcceleration(const pemaths::CPeVector3& p_acceleration)
		{
			m_acceleration = p_acceleration;
		}

		void CPeParticle::SetPosition(const pemaths::CPeVector3& p_position) const
		{
			m_owner.m_transform.SetPosition(p_position);
		}

		void CPeParticle::Update(double p_timeStep)
		{
			UpdatePosition(p_timeStep);
			UpdateAcceleration();
			UpdateVelocity(p_timeStep);
		}

		void CPeParticle::UpdatePrecisely(double p_timeStep) {
			UpdatePositionPrecisely(p_timeStep);
			UpdateAcceleration();
			UpdateVelocity(p_timeStep);
		}

		void CPeParticle::UpdateAcceleration()
		{
			m_acceleration = m_sumForces * m_massInverse;
		}

		void CPeParticle::UpdateVelocity(double p_timeStep)
		{
			m_velocity = (m_velocity * m_damping) + (m_acceleration * p_timeStep);
		}

		void CPeParticle::UpdatePosition(double p_timeStep)
		{
			m_owner.m_transform.SetPosition(m_owner.m_transform.GetPosition() + (m_velocity * p_timeStep));
			
		}

		void CPeParticle::UpdatePositionPrecisely(double p_timeStep)
		{
			m_owner.m_transform.SetPosition(
				m_owner.m_transform.GetPosition() +
				(m_velocity * p_timeStep) +
				m_acceleration * (p_timeStep*p_timeStep/2)
			);
		}

		void CPeParticle::SetSumForces(const pemaths::CPeVector3& p_sumForces)
		{
			m_sumForces = p_sumForces;
		}

		void CPeParticle::AddForce(const pemaths::CPeVector3& p_forceValue)
		{
			m_sumForces += p_forceValue;
		}

	}
}