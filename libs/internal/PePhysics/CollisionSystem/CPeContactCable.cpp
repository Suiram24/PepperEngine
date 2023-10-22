#include "CPeContactCable.h"

namespace engine {
	namespace physics {

		double CPeContactCable::ComputePenetration() const
		{
			double dist = CPeParticleContact::DistanceBetweenParticle(*m_particleA, *m_particleB);

			if (dist > m_maxLength)
			{
				return m_maxLength - dist;
			}
			return 0.;
		}

		double CPeContactCable::GetSeparatingSpeed() const
		{
			double dist = CPeParticleContact::DistanceBetweenParticle(*m_particleA, *m_particleB);

			if (dist > m_maxLength)
			{
				return -m_separatingSpeed;
			}
		}



	}
}