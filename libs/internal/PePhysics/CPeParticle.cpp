#include "CPeParticle.h"

namespace engine {
	namespace physics {

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

		void CPeParticle::SetGravity(double p_gravity)
		{
			m_gravity = p_gravity;
		}

		void CPeParticle::SetVelocity(pemaths::CPeVector3& p_velocity)
		{
			m_velocity = p_velocity;
		}

		void CPeParticle::SetAcceleration(pemaths::CPeVector3& p_acceleration)
		{
			p_acceleration = p_acceleration;
		}
	}
}