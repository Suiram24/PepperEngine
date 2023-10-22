#ifndef PEPHYSICS_CPEFORCESPRING_H
#define PEPHYSICS_CPEFORCESPRING_H

#include "..\CPeForce.h"

namespace pemaths = engine::maths;

namespace engine {
	namespace physics {
		class CPeForceSpring : public CPeForce {
		private:
			CPeParticle* m_other;
			float m_k;
			float m_restLength;

		public:
			CPeForceSpring()
				: CPeForce()
				, m_other(nullptr)
				, m_k(0)
				, m_restLength(0)
			{

			}

			void Initialise(CPeParticle& p_other, float p_k, float p_restLength);

			void Compute(CPeParticle& p_particule, double p_timeStep) const;
		};
	}
}

#endif /* PEPHYSICS_CPEFORCESPRING_H */