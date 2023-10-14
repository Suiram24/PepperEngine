#include "CPeForce.h"

namespace pemaths = engine::maths;

namespace engine {
	namespace physics {
		class CPeForceDrag : public CPeForce {
		private:
			float m_k1;
			float m_k2;

		public:
			CPeForceDrag(float p_k1, float p_k2) :m_k1(p_k1), m_k2(p_k2)
			{

			}

			const pemaths::CPeVector3& Compute(const CPeParticle& p_particule, double p_timeStep) const;
		};
	}
}