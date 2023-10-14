#include "CPeForceGravity.h"

namespace engine {
	namespace physics {

		const pemaths::CPeVector3& CPeForceGravity::Compute(const CPeParticle& p_particule, double p_timeStep) const
		{
			return m_value * (1 / p_particule.GetMassInverse());
		}
	}
}