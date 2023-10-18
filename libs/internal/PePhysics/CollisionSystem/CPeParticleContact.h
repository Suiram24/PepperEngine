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
			
			float m_restitution;// define the elacticness of the collision

			float m_penetration;// the penetration distance

			pemaths::CPeVector3 m_contactNormal; 
			pemaths::CPeVector3 m_separatingVelocity;
			float m_separatingSpeed;


			//Methods
		public:
			CPeParticleContact(CPeParticle* p_particleA, CPeParticle* p_particleB, float p_restitution)
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

			void Resolve(float p_duration);

			static bool CompareContactSeparationSpeed(CPeParticleContact* p_contact1, CPeParticleContact* p_contact2);

			virtual float GetSeparatingSpeed() const;

			/**
			* @brief Returns the distance between the two particles taking their radius into account.
			*/
			static float DistanceBetweenParticle(CPeParticle& p_particleA, CPeParticle& p_particleB);

		protected:
			virtual float ComputePenetration() const;

			virtual pemaths::CPeVector3 ComputeContactNormal() const;

			pemaths::CPeVector3 ComputeSeparatingVelocity() const;

			float ComputeSeparatingSpeed() const;

			void ResolveVelocity();

			void ResolvePenetration();

			bool IsContactAtRest(float p_duration) const;

			void ResetValues();
		};
	}
}

#endif /* CPEPARTICLECONTACT_CPEPARTICLECONTACT_H */