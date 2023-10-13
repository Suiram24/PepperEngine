#ifndef SPEPARTICLEFORCEENTRY_SPEPARTICLEFORCEENTRY_H
#define SPEPARTICLEFORCEENTRY_SPEPARTICLEFORCEENTRY_H


#include "CPeParticle.h"
#include "CPeForces.h"


namespace engine {
	namespace physics {

		struct SPeParticleForceEntry
		{
			CPeForces* m_force;
			CPeParticle* m_particle;
		};
	}
}
#endif /* SPEPARTICLEFORCEENTRY_SPEPARTICLEFORCEENTRY_H */