#include "CPeForceSpring.h"

namespace engine {
	namespace physics {
        void CPeForceSpring::Initialise(
			CPeParticle*p_other,
			float p_k,
			float p_restLength,
			pemaths::CPeVector3 p_bodyAnchor,
			pemaths::CPeVector3 p_otherLocalAnchor
		)
        {
			m_isActive = true;
			m_other = p_other;
			m_bodyAnchor = p_bodyAnchor;
			m_otherBodyAnchor = p_otherLocalAnchor;
			m_k = p_k;
			m_restLength = p_restLength;
        }

        void CPeForceSpring::Compute(CPeParticle& p_particle, double p_timeStep) const
		{
			pemaths::CPeVector3 globalOtherAnchor = m_other->GetTransform().GetPositionPoint(m_otherBodyAnchor);
			pemaths::CPeVector3 globalBodyAnchor = p_particle.GetTransform().GetPositionPoint(m_bodyAnchor);
			
			pemaths::CPeVector3 d = globalOtherAnchor - globalBodyAnchor;
			if (d.GetNorm() > 0.00001)
			{
				p_particle.AddForceAtBodyPoint(d.NormalizeVector() * (m_k * (d.GetNorm() - m_restLength)) * p_timeStep, m_bodyAnchor);
				m_other->AddForceAtBodyPoint(d.NormalizeVector() * (-m_k * (d.GetNorm() - m_restLength)) * p_timeStep, m_otherBodyAnchor);
			}
			
		}

		
	}
}