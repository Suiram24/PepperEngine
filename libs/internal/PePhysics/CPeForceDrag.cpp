#include "CPeForceDrag.h"

namespace engine {
	namespace physics {

		const pemaths::CPeVector3& CPeForceDrag::Compute(const CPeParticle& p_particule, double p_timeStep) const
		{
			return GetValue();
		}
	}
}