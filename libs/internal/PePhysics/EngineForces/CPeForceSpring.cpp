#include "CPeForceSpring.h"

namespace engine {
	namespace physics {

		void CPeForceSpring::Initialise(CPeParticle* p_other, float p_k, float p_restLength)
		{
			m_isActive = true;
			m_other = p_other;
			m_k = p_k;
			m_restLength = p_restLength;
		}

		void CPeForceSpring::Compute(CPeParticle& p_particule, double p_timeStep) const
		{
			pemaths::CPeVector3 d = m_other->GetTransform().GetPosition() - p_particule.GetTransform().GetPosition();
			p_particule.AddForce(d.NormalizeVector() * (m_k * (d.GetNorm() - m_restLength)) * p_timeStep);
			m_other->AddForce(d.NormalizeVector() * (-m_k * (d.GetNorm() - m_restLength)) * p_timeStep);
		}
	}
}