#ifndef PEPHYSICS_CPEFORCEDRAG_H
#define PEPHYSICS_CPEFORCEDRAG_H

#include "..\CPeForce.h"

namespace pemaths = engine::maths;

namespace engine {
	namespace physics {
		class CPeForceDrag : public CPeForce {
		private:
			float m_k1;
			float m_k2;

		public:
			CPeForceDrag()
				: CPeForce()
				, m_k1(0)
				, m_k2(0)
			{

			}

			void Initialise(float p_k1, float p_k2);

			void Compute(CPeParticle& p_particule, double p_timeStep) const;
		};
	}
}

#endif /* PEPHYSICS_CPEFORCEDRAG_H */
