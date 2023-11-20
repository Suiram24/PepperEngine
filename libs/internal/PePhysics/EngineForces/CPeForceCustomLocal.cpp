#include "CPeForceCustomLocal.h"

namespace engine {
	namespace physics {
		void CPeForceCustomLocal::Initialise(pemaths::CPeVector3 p_forceValue, pemaths::CPeVector3 p_appPoint)
		{
			m_isActive = true;
			m_forceValue = p_forceValue;
			m_appPoint = p_appPoint;
		}
		void CPeForceCustomLocal::Initialise(pemaths::CPeVector3 p_direction, float p_magnitude, pemaths::CPeVector3 p_appPoint)
		{
			m_isActive = true;
			m_forceValue = p_direction.NormalizeVector()*p_magnitude;
			m_appPoint = p_appPoint;
		}

		void CPeForceCustomLocal::Compute(CPeParticle& p_particle, double p_timeStep) const
		{
			p_particle.AddForceAtBodyPoint(p_particle.GetTransform().GetVectorInLocal(m_forceValue) * p_timeStep, m_appPoint);
		}

		void CPeForceCustomLocal::ChangeValue(pemaths::CPeVector3 p_forceValue)
		{
			m_forceValue = p_forceValue;
		}
	}
}