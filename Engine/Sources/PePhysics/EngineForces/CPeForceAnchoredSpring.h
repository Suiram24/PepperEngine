#ifndef PEPHYSICS_CPEFORCESANCHOREDPRING_H
#define PEPHYSICS_CPEFORCESANCHOREDPRING_H

#include "../CPeForce.h"
#include "../CPeRigidBody.h"

namespace pemaths = engine::maths;

namespace engine {
	namespace physics {
		class CPeForceAnchoredSpring : public CPeForce {
		private:
			pemaths::CPeVector3 m_anchor;
			pemaths::CPeVector3 m_bodyAnchor;

			float m_k; 
			float m_restLength;

		public:
			CPeForceAnchoredSpring()
				: CPeForce()
				, m_anchor(pemaths::CPeVector3())
				, m_bodyAnchor(pemaths::CPeVector3())
				, m_k(0)
				, m_restLength(0)
			{

			}
 
			void Initialise(const pemaths::CPeVector3& p_anchor, float p_k, float p_restLength, pemaths::CPeVector3 p_bodyAnchor = pemaths::CPeVector3());

			void Compute(CPeParticle& p_particule, double p_timeStep) const;
		};
	}
}

#endif /* PEPHYSICS_CPEFORCESANCHOREDPRING_H */
