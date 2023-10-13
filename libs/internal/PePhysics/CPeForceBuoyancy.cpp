#include "CPeForceBuoyancy.h"

namespace engine {
	namespace physics {

		const pemaths::CPeVector3& CPeForceBuoyancy::Compute(const CPeParticle& p_particule, double p_timeStep) const
		{
			float d = (p_particule.GetTransform().GetPosition().GetY() - m_liquidLevel - m_immersionDepth) / (2 * m_immersionDepth);

			pemaths::CPeVector3 yNorm = pemaths::CPeVector3(0., 1., 0.);
			
			if (d < 0) { return yNorm * 0.; }

			if (d > 1) { return yNorm * (m_volume * m_liquidDensity); }

			return yNorm * ( d * m_volume * m_liquidDensity);
		}
	}
}