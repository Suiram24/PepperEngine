#include "CPeContactRod.h"

namespace engine {
	namespace physics {

		float CPeContactRod::GetSeparatingSpeed() const
		{
			float dist = CPeParticleContact::DistanceBetweenParticle(*m_particleA, *m_particleB);
			if ((dist - m_length) > 0.01)
			{
				return -m_separatingSpeed;
			}
			if ((dist - m_length) <  - 0.01)
			{
				return m_separatingSpeed;
			}
			return 0.;
		}
		
		pemaths::CPeVector3 CPeContactRod::ComputeContactNormal() const
		{
			float dist = CPeParticleContact::DistanceBetweenParticle(*m_particleA, *m_particleB);
			if (dist > m_length)
			{
				return this->CPeParticleContact::ComputeContactNormal() * (- 1.);
			}
			return this->CPeParticleContact::ComputeContactNormal();
		}
	}
}