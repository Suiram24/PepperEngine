#include "CPeContactRod.h"
#include <math.h>

namespace engine {
	namespace physics {

		double CPeContactRod::GetSeparatingSpeed() const
		{
			double dist = CPeParticleContact::DistanceBetweenParticle(*m_particleA, *m_particleB);

			if (abs(dist - m_length) > 0.01)
			{
				return -abs(m_separatingSpeed);
			}
			return 0.;
		}
		
		double CPeContactRod::ComputePenetration() const
		{
			double dist = CPeParticleContact::DistanceBetweenParticle(*m_particleA, *m_particleB);

			if ((dist - m_length) > 0.01)
			{
				return m_length- dist;
			}
			if ((dist - m_length) < -0.01)
			{
				return m_length - dist;
			}
			return 0.;
		}

		pemaths::CPeVector3 CPeContactRod::ComputeContactNormal() const
		{
			double dist = CPeParticleContact::DistanceBetweenParticle(*m_particleA, *m_particleB);
			
			if ((dist - m_length) > 0.01)
			{
				return this->CPeParticleContact::ComputeContactNormal() * (- 1.);
			}
			if ((dist - m_length) < -0.01)
			{
				return this->CPeParticleContact::ComputeContactNormal();
			}
			return pemaths::CPeVector3(0, 0, 0);
		}

		bool CPeContactRod::IsContactAtRest(double p_timeStep) const
		{
			return false;
		}
	}
}