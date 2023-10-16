#include "CPeForceAnchoredSpring.h"

namespace engine {
	namespace physics {

		void CPeForceAnchoredSpring::Compute(CPeParticle& p_particule, double p_timeStep) const
		{
			pemaths::CPeVector3 d = m_anchor - p_particule.GetTransform().GetPosition();
			p_particule.AddForce(d);
			return;
		}
	}
}