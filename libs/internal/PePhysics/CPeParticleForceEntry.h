#ifndef CPEPARTICLEFORCEENTRY_CPEPARTICLEFORCEENTRY_H
#define CPEPARTICLEFORCEENTRY_CPEPARTICLEFORCEENTRY_H


#include "CPeParticle.h"
#include "CPeForces.h"


namespace engine {
	namespace physics {

		class CPeParticleForceEntry
		{
		private:
			const CPeForces& m_force;
			const CPeParticle& m_particle;

		public:
			CPeParticleForceEntry(const CPeForces& p_forces, const CPeParticle& p_particule) :m_force(p_forces), m_particle(p_particule)
			{
			}

			const CPeForces& GetForce() const;

			const CPeParticle& GetParticule() const;
			
		};
	}
}
#endif /* CPEPARTICLEFORCEENTRY_CPEPARTICLEFORCEENTRY_H */