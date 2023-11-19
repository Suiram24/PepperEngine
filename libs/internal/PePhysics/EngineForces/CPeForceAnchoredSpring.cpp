#include "CPeForceAnchoredSpring.h"

namespace engine {
	namespace physics {
		void CPeForceAnchoredSpring::Initialise(
			const pemaths::CPeVector3& p_anchor,
			float p_k,
			float p_restLength,
			pemaths::CPeVector3 p_bodyAnchor
		)
		{
			m_isActive = true;
			m_anchor = p_anchor;
			m_bodyAnchor = p_bodyAnchor;
			m_k = p_k;
			m_restLength = p_restLength;
		}

		void CPeForceAnchoredSpring::Compute(CPeParticle& p_particule, double p_timeStep) const
		{
			pemaths::CPeVector3 globalBodyAnchor = p_particule.GetTransform().GetPositionPoint(m_bodyAnchor);
			pemaths::CPeVector3 d = m_anchor - globalBodyAnchor;
			p_particule.AddForceAtBodyPoint(d.NormalizeVector() * (m_k * (d.GetNorm() - m_restLength)) * p_timeStep, m_bodyAnchor);
		}
	}
}