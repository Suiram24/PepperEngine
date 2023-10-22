#ifndef CPECOLLISIONSYSTEM_CPECOLLISIONSYSTEM_H
#define CPECOLLISIONSYSTEM_CPECOLLISIONSYSTEM_H

#include <vector>
#include "CPeParticleContact.h"
#include "CPeColliderComponent.h"
#include "CPeContactRod.h"
#include "CPeContactCable.h"

namespace engine {
	namespace physics {

		namespace consts
		{
			constexpr int nbIterationCollider = 1;
		}

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

			static CPeCollisionSystem& GetInstance()
			{
				static CPeCollisionSystem instance;
				return instance;
			}	

			/**
			 * @brief Detect the contacts and resolve te collisions.
			 * @param p_timeStep The time of simulation in second.
			 * @param p_particles A vector of the particles with a CPeColliderComponent.
			*/
			void UpdateCollision(double p_timeStep, std::vector<CPeParticle*>* p_particles);

		

			/**
			 * @brief Add a permanent rod contact between two particles.
			 * @param p_particleA the first particle.
			 * @param p_particleB the second particle.
			 * @param p_restitution the restitution of the particles.
			 * @param p_length the length of the rod.
			*/
			void CreateRodBetween(CPeParticle* p_particleA, CPeParticle* p_particleB, double p_restitution, double p_length);

			/**
			 * @brief Add a permanent rod contact between two particles.
			 * @param p_particleA the first particle.
			 * @param p_particleB the second particle.
			 * @param p_restitution the restitution of the particles.
			 * @param p_maxLength the maximum length of the cable.
			*/
			void CreateCableBetween(CPeParticle* p_particleA, CPeParticle* p_particleB, double p_restitution, double p_maxLength);

		private:

			CPeCollisionSystem()
				: m_oneTimeContacts(std::vector<CPeParticleContact*>())
				, m_permanentContacts(std::vector<CPeParticleContact*>())
				, m_solverIteration(consts::nbIterationCollider)
			{
			}


			/**
			* @brief Register a permanent contact.
			* @param p_contact The contact to register.
			*/
			void AddPermanentContact(CPeParticleContact* p_contact);

			/**
			 * @brief Detect the new collisions.
			 * @param p_particles A vector of the particles with a CPeColliderComponent.
			*/
			void DetectCollions(std::vector<CPeParticle*>* p_particles);

			/**
			 * @brief Resolve both type of collisions.
			 * @param p_timeStep The time of simulation in second.
			*/
			void ResolveCollisions(double p_timeStep);
		};
	}
}

#endif /* CPECOLLISIONSYSTEM_CPECOLLISIONSYSTEM_H */