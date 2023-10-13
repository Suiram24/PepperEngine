#include "CPeForceDrag.h"

namespace engine {
	namespace physics {

		const pemaths::CPeVector3& CPeForceDrag::Compute(const CPeParticle& p_particule, double p_timeStep) const
		{
			pemaths::CPeVector3 v = p_particule.GetVelocity();
			double norm = v.GetNorm();

			return v.NormalizeVector() * -(m_k1 * norm + m_k2 * norm * norm);
		}
	}
}