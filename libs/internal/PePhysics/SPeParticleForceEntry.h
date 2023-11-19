#ifndef SPEPARTICLEFORCEENTRY_SPEPARTICLEFORCEENTRY_H
#define SPEPARTICLEFORCEENTRY_SPEPARTICLEFORCEENTRY_H


#include "CPeParticle.h"
#include "CPeForce.h"


namespace engine {
	namespace physics {

		struct SPeParticleForceEntry
		{
			CPeForce* m_force;
			CPeParticle* m_particle;
			double m_lifeSpan; //-1 for infinite, so must be set to 0 if lifeSpan-dt <0 to make lifespan = 0 inactive

			SPeParticleForceEntry()
				: m_force(nullptr)
				, m_particle(nullptr)
				, m_lifeSpan(0)
			{

			}

			void Initialise(CPeForce* p_force, CPeParticle* p_particle, double p_lifeSpan = -1)
			{
				m_force = p_force;
				m_particle = p_particle;
				m_lifeSpan = p_lifeSpan;
			}

			bool IsActive()
			{
				return m_lifeSpan != 0;
			}
		};
	}
}
#endif /* SPEPARTICLEFORCEENTRY_SPEPARTICLEFORCEENTRY_H */