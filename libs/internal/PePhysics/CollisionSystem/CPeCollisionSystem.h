#ifndef CPECOLLISIONSYSTEM_CPECOLLISIONSYSTEM_H
#define CPECOLLISIONSYSTEM_CPECOLLISIONSYSTEM_H

#include <vector>
#include "CPeParticleContact.h"
#include "CPeColliderComponent.h"

namespace engine {
	namespace physics {

		class CPeCollisionSystem {
		private:
			std::vector<CPeParticleContact*> m_oneTimeContacts;

			std::vector<CPeParticleContact*> m_permanentContacts;

			int m_solverIteration;

		public:
			CPeCollisionSystem()
				: m_oneTimeContacts(std::vector<CPeParticleContact*>())
				, m_permanentContacts(std::vector<CPeParticleContact*>())
				, m_solverIteration(2)
			{
			}

			void UpdateCollision(float p_duration, std::vector<CPeParticle*> p_particles);

			void AddPermanentContact(CPeParticleContact* p_contact);

		private:
			void DetectCollions(std::vector<CPeParticle*> p_particles);

			void ResolveCollisions(float p_duration);


		};
	}
}

#endif /* CPECOLLISIONSYSTEM_CPECOLLISIONSYSTEM_H */