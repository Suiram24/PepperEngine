#include "CPeForceBuoyancy.h"

namespace engine {
	namespace physics {

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