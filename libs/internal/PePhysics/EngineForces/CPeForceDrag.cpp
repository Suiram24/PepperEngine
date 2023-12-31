#include "CPeForceDrag.h"

namespace engine {
	namespace physics {

		void CPeForceDrag::Initialise(float p_k1, float p_k2, pemaths::CPeVector3 p_appPoint)
		{
			m_isActive = true;
			m_k1 = p_k1;
			m_k2 = p_k2;
			m_appPoint = p_appPoint;
		}

		void CPeForceDrag::Compute(CPeParticle& p_particule, double p_timeStep) const
		{
			pemaths::CPeVector3 v = p_particule.GetVelocity();
			double norm = v.GetNorm();
			p_particule.AddForceAtBodyPoint(v.NormalizeVector() * -(m_k1 * norm + m_k2 * norm * norm) * p_timeStep, m_appPoint);
		}
	}
}