#include "CPeForceAnchoredSpring.h"

namespace engine {
	namespace physics {

		const pemaths::CPeVector3& CPeForceAnchoredSpring::Compute(const CPeParticle& p_particule, double p_timeStep) const
		{
			pemaths::CPeVector3 d = m_anchor - p_particule.GetTransform().GetPosition();
			return d.NormalizeVector() * (-m_k * (d.GetNorm() - m_restLength));
		}
	}
}