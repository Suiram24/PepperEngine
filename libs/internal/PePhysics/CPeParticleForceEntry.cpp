#include "CPeParticleForceEntry.h"

namespace engine {
	namespace physics {
		const CPeForces& CPeParticleForceEntry::GetForce() const
		{
			return m_force;
		}

		const CPeParticle& CPeParticleForceEntry::GetParticule() const
		{
			return m_particle;
		}

	}
}