#ifndef CPEPARTICLECONTACT_CPEPARTICLECONTACT_H
#define CPEPARTICLECONTACT_CPEPARTICLECONTACT_H

#include "../CPeParticle.h"
#include "../../PeMaths/CPeVector3.h"

namespace pemaths = engine::maths;

namespace engine {
	namespace physics {

		/**
		 * @brief A class for handling the contact between two particles.
		*/
		class CPeParticleContact {
			//Fields
		protected:
			CPeParticle* m_particleA;
			CPeParticle* m_particleB;
			
			double m_restitution;// define the elacticness of the collision

			double m_penetration;// the penetration distance

			pemaths::CPeVector3 m_contactNormal; 
			pemaths::CPeVector3 m_separatingVelocity;
			double m_separatingSpeed;


			//Methods
		public:
			CPeParticleContact(CPeParticle* p_particleA, CPeParticle* p_particleB, double p_restitution)
				: m_particleA(p_particleA)
				, m_particleB(p_particleB)
				, m_restitution(p_restitution)
				, m_penetration(ComputePenetration())
				, m_contactNormal(ComputeContactNormal())
				, m_separatingVelocity(ComputeSeparatingVelocity())
				, m_separatingSpeed(ComputeSeparatingSpeed())
			{
			}

			CPeParticleContact(CPeParticle* p_particleA, CPeParticle* p_particleB)
				: m_particleA(p_particleA)
				, m_particleB(p_particleB)
				, m_restitution(0.9f)
				, m_penetration(ComputePenetration())
				, m_contactNormal(ComputeContactNormal())
				, m_separatingVelocity(ComputeSeparatingVelocity())
				, m_separatingSpeed(ComputeSeparatingSpeed())
			{
			}

			/**
			 * @brief Resolve the contact.
			 * @param p_timeStep The time of simulation in second.
			*/
			void Resolve(double p_timeStep);

			/**
			 * @brief A comparator between two CPeParticleContact.
			 * @param p_contact1 A CPeParticleContact.
			 * @param p_contact2 A second CPeParticleContact.
			 * @return True if the separating speed of the first is lesser than the separating speed of the second and false if not.
			*/
			static bool CompareContactSeparationSpeed(CPeParticleContact* p_contact1, CPeParticleContact* p_contact2);

			/**
			 * @brief Getter for the separating speed.
			 * @return the separating speed.
			*/
			virtual double GetSeparatingSpeed() const;

			/**
			* @brief Returns the distance between the two particles taking their radius into account.
			* @param p_particleA
			* @param p_particleB
			* @return the distance between the two particles surfaces.
			*/
			static double DistanceBetweenParticle(CPeParticle& p_particleA, CPeParticle& p_particleB);

		protected:

			/**
			* @brief Compute the penetration between the two particles radius.
			* @return the penetration between the two particles radius.
			*/
			virtual double ComputePenetration() const;

			/**
			* @brief Compute the contact normal between the two particles.
			* @return the contact normal between the two particles.
			*/
			virtual pemaths::CPeVector3 ComputeContactNormal() const;

			/**
			* @brief Compute the separating velocity of two particles.
			* @return the separating velocity of two particles.
			*/
			pemaths::CPeVector3 ComputeSeparatingVelocity() const;

			/**
			* @brief Compute the separating speed of two particles.
			* @return the separating speed of two particles.
			*/
			double ComputeSeparatingSpeed() const;

			/**
			* @brief Change the velocity of the particles to resolve collision.
			*/
			void ResolveVelocity();

			/**
			* @brief Change the position of the particles to resolve collision.
			*/
			void ResolvePenetration();

			/**
			* @brief Verifies if the contact is at rest.
			* @param p_timeStep The time of simulation in second.
			* @return is the contact at rest.
			*/
			bool IsContactAtRest(double p_timeStep) const;

			/**
			* @brief Compute the contact normal, penetration, separating speed and separating velocity.
			*/
			void ResetValues();
		};
	}
}

#endif /* CPEPARTICLECONTACT_CPEPARTICLECONTACT_H */