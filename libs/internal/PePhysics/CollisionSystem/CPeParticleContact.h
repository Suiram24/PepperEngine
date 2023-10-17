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
		private:
			static const float DEFAULT_PENETRATION = 0.9f;

			CPeParticle& m_particleA;
			CPeParticle& m_particleB;
			
			float m_restitution;// define the elacticness of the collision

			float m_penatration;// the penetration distance

			pemaths::CPeVector3 m_contactNormal;

			//Methods
		public:
			CPeParticleContact(CPeParticle& p_particleA, CPeParticle& p_particleB, float p_restitution)
				: m_particleA(p_particleA)
				, m_particleB(p_particleB)
				, m_restitution(p_restitution)
				, m_penatration(ComputePenetration())
				, m_contactNormal(ComputeContactNormal())
			{
			}

			CPeParticleContact(CPeParticle& p_particleA, CPeParticle& p_particleB)
				: m_particleA(p_particleA)
				, m_particleB(p_particleB)
				, m_restitution(DEFAULT_PENETRATION)
				, m_penatration(ComputePenetration())
				, m_contactNormal(ComputeContactNormal())
			{
			}

			void Resolve(float p_duration);

		private:
			float ComputePenetration() const;

			pemaths::CPeVector3 ComputeContactNormal() const;

			float ComputeSeperatingVelocity();

			void ResolveVelocity();

			void ResolvePenetration();
		};
	}
}

#endif /* CPEPARTICLECONTACT_CPEPARTICLECONTACT_H */