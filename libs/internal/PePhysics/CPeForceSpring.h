#include "CPeForce.h"

namespace pemaths = engine::maths;

namespace engine {
	namespace physics {
		class CPeForceSpring : public CPeForce {
		private:
			CPeParticle& m_other;
			float m_k;
			float m_restLength;

		public:
			CPeForceSpring(CPeParticle& p_other, float p_k, float p_restLength)
				: m_other(p_other)
				, m_k(p_k)
				, m_restLength(p_restLength)
			{

			}

			void Compute(CPeParticle& p_particule, double p_timeStep) const;
		};
	}
}