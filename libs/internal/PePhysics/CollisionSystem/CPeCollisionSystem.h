#ifndef CPECOLLISIONSYSTEM_CPECOLLISIONSYSTEM_H
#define CPECOLLISIONSYSTEM_CPECOLLISIONSYSTEM_H

#include <vector>
#include "CPeParticleContact.h"

namespace engine {
	namespace physics {

		class CPeCollisionSystem {
		private:
			std::vector<CPeParticleContact> m_oneTimeContacts;

			std::vector<CPeParticleContact> m_permanentContacts;

		public:
			CPeCollisionSystem()
				: m_oneTimeContacts(std::vector<CPeParticleContact>())
				, m_permanentContacts(std::vector<CPeParticleContact>())
			{
			}

			void DetectCollions();

			void ResolveCollisions();

			void AddPermanentContact(CPeParticleContact p_contact);

		};
	}
}

#endif /* CPECOLLISIONSYSTEM_CPECOLLISIONSYSTEM_H */