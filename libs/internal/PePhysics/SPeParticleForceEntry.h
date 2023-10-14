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
			float lifeSpan;
		};
	}
}
#endif /* SPEPARTICLEFORCEENTRY_SPEPARTICLEFORCEENTRY_H */