#include "CPeContactCable.h"

namespace engine {
	namespace physics {

		float CPeContactCable::ComputePenetration() const
		{
			float dist = CPeParticleContact::DistanceBetweenParticle(*m_particleA, *m_particleB);

			if (dist > m_maxLength)
			{
				return m_maxLength - dist;
			}
			return 0.;
		}

		float CPeContactCable::GetSeparatingSpeed() const
		{
			float dist = CPeParticleContact::DistanceBetweenParticle(*m_particleA, *m_particleB);

			if (dist > m_maxLength)
			{
				return -m_separatingSpeed;
			}
		}



	}
}