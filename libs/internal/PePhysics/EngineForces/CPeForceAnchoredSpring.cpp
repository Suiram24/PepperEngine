#include "CPeForceAnchoredSpring.h"

namespace engine {
	namespace physics {

		void CPeForceAnchoredSpring::Initialise(const pemaths::CPeVector3& p_anchor, float p_k, float p_restLength)
		{
			m_isActive = true;
			m_anchor = p_anchor;
			m_k = p_k;
			m_restLength = p_restLength;
		}

		void CPeForceAnchoredSpring::Compute(CPeParticle& p_particule, double p_timeStep) const
		{
			pemaths::CPeVector3 d = m_anchor - p_particule.GetTransform().GetPosition();
			p_particule.AddForce(d.NormalizeVector() * (m_k * (d.GetNorm() - m_restLength)) * p_timeStep);
			return;
		}


	}
}