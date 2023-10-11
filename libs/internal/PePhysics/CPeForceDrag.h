#include "CPeForces.h"

namespace pemaths = engine::maths;

namespace engine {
	namespace physics {
		class CPeForceDrag : public CPeForces {

			const pemaths::CPeVector3& Compute(const CPeParticle& p_particule, double p_timeStep) const;
		};
	}
}