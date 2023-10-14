#include "CPeForce.h"

namespace pemaths = engine::maths;

namespace engine {
	namespace physics {
		class CPeForceGravity : public CPeForce {
		private:
			const pemaths::CPeVector3 m_value;

		public:
			CPeForceGravity(double p_intensity):m_value(pemaths::CPeVector3(0.,-p_intensity,0.))
			{
			}

			CPeForceGravity():m_value(pemaths::CPeVector3(0., -10., 0.))
			{
			}

			const pemaths::CPeVector3& Compute(const CPeParticle& p_particule, double p_timeStep) const;
		};
	}
}