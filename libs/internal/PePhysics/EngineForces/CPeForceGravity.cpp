#include "CPeForceGravity.h"

namespace engine {
	namespace physics {

		void CPeForceGravity::Compute(CPeParticle& p_particule, double p_timeStep) const
		{
			p_particule.AddForce(m_value * (1 / p_particule.GetMassInverse()));
		}
	}
}