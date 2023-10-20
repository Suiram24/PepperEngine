#include "CPeForceBuoyancy.h"

namespace engine {
	namespace physics {

		void CPeForceBuoyancy::Initialise(float p_immersionDepth, float p_volume, float p_liquidLevel, float p_liquidDensity)
		{
			m_isActive = true;
			m_immersionDepth = p_immersionDepth;
			m_volume = p_volume;
			m_liquidLevel = p_liquidLevel;
			m_liquidDensity = p_liquidDensity;
		}

		void CPeForceBuoyancy::Compute(CPeParticle& p_particule, double p_timeStep) const
		{
			float d = (p_particule.GetTransform().GetPosition().GetY() - m_liquidLevel - m_immersionDepth) / (2 * m_immersionDepth);

			pemaths::CPeVector3 yNorm = pemaths::CPeVector3(0., 1., 0.);
			
			if (d < 0)
			{ 
				p_particule.AddForce(yNorm * 0.);
			}
			else if (d > 1) 
			{ 
				p_particule.AddForce(yNorm * (m_volume * m_liquidDensity));
			}
			else 
			{
				p_particule.AddForce(yNorm * (d * m_volume * m_liquidDensity));
			}

			
		}
	}
}