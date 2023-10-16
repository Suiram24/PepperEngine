#include "..\CPeForce.h"

namespace pemaths = engine::maths;

namespace engine {
	namespace physics {
		class CPeForceAnchoredSpring : public CPeForce {
		private:
			pemaths::CPeVector3 m_anchor;
			float m_k;
			float m_restLength;

		public:
			CPeForceAnchoredSpring(const pemaths::CPeVector3& p_anchor, float p_k, float p_restLength)
				: m_anchor(p_anchor)
				, m_k(p_k)
				, m_restLength(p_restLength)
			{

			}

			void Compute(CPeParticle& p_particule, double p_timeStep) const;
		};
	}
}