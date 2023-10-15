#include "CPeForceDrag.h"

namespace engine {
	namespace physics {

		void CPeForceDrag::Compute(CPeParticle& p_particule, double p_timeStep) const
		{
			pemaths::CPeVector3 v = p_particule.GetVelocity();
			double norm = v.GetNorm();

			p_particule.AddForce(v.NormalizeVector() * -(m_k1 * norm + m_k2 * norm * norm));
		}
	}
}