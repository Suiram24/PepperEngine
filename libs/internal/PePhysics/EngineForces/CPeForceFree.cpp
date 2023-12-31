#include "CPeForceFree.h"

namespace engine {
	namespace physics {
		void CPeForceFree::Initialise(pemaths::CPeVector3 p_forceValue, pemaths::CPeVector3 p_appPoint)
		{
			m_isActive = true;
			m_forceValue = p_forceValue;
			m_appPoint = p_appPoint;
		}
		void CPeForceFree::Initialise(pemaths::CPeVector3 p_direction, float p_magnitude, pemaths::CPeVector3 p_appPoint)
		{
			m_isActive = true;
			m_forceValue = p_direction.NormalizeVector()*p_magnitude;
			m_appPoint = p_appPoint;
		}

		void CPeForceFree::Compute(CPeParticle& p_particle, double p_timeStep) const
		{
			p_particle.AddForceAtBodyPoint(m_forceValue * p_timeStep, m_appPoint);
		}

		void CPeForceFree::ChangeValue(pemaths::CPeVector3 p_forceValue)
		{
			m_forceValue = p_forceValue;
		}
	}
}