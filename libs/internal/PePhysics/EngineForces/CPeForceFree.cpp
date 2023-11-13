#include "CPeForceFree.h"

namespace engine {
	namespace physics {
		void CPeForceFree::Initialise(pemaths::CPeVector3 p_forceValue, pemaths::CPeVector3 p_appPoint)
		{
			m_isActive = true;
			m_forceValue = p_forceValue;
			m_globalPosition = p_appPoint;
		}
		void CPeForceFree::Initialise(pemaths::CPeVector3 p_direction, float p_magnitude, pemaths::CPeVector3 p_appPoint)
		{
			m_isActive = true;
			m_forceValue = p_direction.NormalizeVector()*p_magnitude;
			m_globalPosition = p_appPoint;
		}
		void CPeForceFree::Compute(CPeParticle* p_particle, double p_timeStep) const
		{
			p_particle->AddForceAtPoint(m_forceValue, m_globalPosition);
		}
	}
}