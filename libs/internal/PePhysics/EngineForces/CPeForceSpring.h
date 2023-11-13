#ifndef PEPHYSICS_CPEFORCESPRING_H
#define PEPHYSICS_CPEFORCESPRING_H

#include "../CPeForce.h"
#include "../CPeRigidBody.h"

namespace pemaths = engine::maths;

namespace engine {
	namespace physics {

		class CPeForceSpring : public CPeForce {
		private:
			pemaths::CPeVector3 m_bodyAnchor;

			CPeParticle* m_other;
			pemaths::CPeVector3 m_otherBodyAnchor;

			float m_k;
			float m_restLength;
		public:
			CPeForceSpring()
				: CPeForce()
				, m_other(nullptr)
				, m_bodyAnchor(0,0,0)
				, m_otherBodyAnchor(0,0,0)
				, m_k(0)
				, m_restLength(0)
			{

			}

			void Initialise(CPeParticle* p_other, float p_k, float p_restLength);
			void Initialise(CPeRigidBody* p_other, pemaths::CPeVector3 p_otherLocalAnchor, float p_k, float p_restLength);

			void Compute(CPeParticle& p_particle, double p_timeStep) const;
			void Compute(CPeRigidBody& p_rigidBody, double p_timeStep) const;
		};
	}
}

#endif /* PEPHYSICS_CPEFORCESPRING_H */