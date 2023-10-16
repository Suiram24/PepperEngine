#include "CPeForceSpring.h"

namespace engine {
	namespace physics {

		void CPeForceSpring::Compute(CPeParticle& p_particule, double p_timeStep) const
		{
			pemaths::CPeVector3 d = m_other.GetTransform().GetPosition() - p_particule.GetTransform().GetPosition();
			p_particule.AddForce(d.NormalizeVector() * (-m_k * (d.GetNorm() - m_restLength)));
		}
	}
}