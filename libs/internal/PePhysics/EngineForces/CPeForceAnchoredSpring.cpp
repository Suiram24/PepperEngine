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
			double n = d.GetNorm();
			if (n > m_restLength)
			{
				d = d *  ((n - m_restLength) / n) * m_k * p_timeStep;
			}
			p_particule.AddForce(d);
			return;
		}


	}
}