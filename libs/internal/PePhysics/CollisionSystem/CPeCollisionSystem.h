#ifndef CPECOLLISIONSYSTEM_CPECOLLISIONSYSTEM_H
#define CPECOLLISIONSYSTEM_CPECOLLISIONSYSTEM_H

#include <vector>
#include "CPeParticleContact.h"
#include "CPeColliderComponent.h"

namespace engine {
	namespace physics {

		/**
		 * @brief The class that detect contacts and resolve collisions. Provides an interface to add permanent contacts.
		*/
		class CPeCollisionSystem {
		private:
			// vector of detected contacts
			std::vector<CPeParticleContact*> m_oneTimeContacts;

			// vector of permanent contacts
			std::vector<CPeParticleContact*> m_permanentContacts;

			// number of iteration for the solver
			int m_solverIteration;

		public:
			CPeCollisionSystem()
				: m_oneTimeContacts(std::vector<CPeParticleContact*>())
				, m_permanentContacts(std::vector<CPeParticleContact*>())
				, m_solverIteration(2)
			{
			}

			/**
			 * @brief Detect the contacts and resolve te collisions.
			 * @param p_timeStep The time of simulation in second.
			 * @param p_particles A vector of the particles with a CPeColliderComponent.
			*/
			void UpdateCollision(double p_timeStep, std::vector<CPeParticle*> p_particles);

			/**
			 * @brief Register a permanent contact.
			 * @param p_contact The contact to register.
			*/
			void AddPermanentContact(CPeParticleContact* p_contact);

		private:

			/**
			 * @brief Detect the new collisions.
			 * @param p_particles A vector of the particles with a CPeColliderComponent.
			*/
			void DetectCollions(std::vector<CPeParticle*> p_particles);

			/**
			 * @brief Resolve both type of collisions.
			 * @param p_timeStep The time of simulation in second.
			*/
			void ResolveCollisions(double p_timeStep);
		};
	}
}

#endif /* CPECOLLISIONSYSTEM_CPECOLLISIONSYSTEM_H */