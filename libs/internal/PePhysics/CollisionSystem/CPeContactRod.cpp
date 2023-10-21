#include "CPeContactRod.h"

namespace engine {
	namespace physics {

		double CPeContactRod::GetSeparatingSpeed() const
		{
			double dist = CPeParticleContact::DistanceBetweenParticle(*m_particleA, *m_particleB);
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
			double dist = CPeParticleContact::DistanceBetweenParticle(*m_particleA, *m_particleB);
			if (dist > m_length)
			{
				return this->CPeParticleContact::ComputeContactNormal() * (- 1.);
			}
			return this->CPeParticleContact::ComputeContactNormal();
		}
	}
}