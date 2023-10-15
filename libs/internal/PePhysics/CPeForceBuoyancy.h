#include "CPeForce.h"

namespace pemaths = engine::maths;

namespace engine {
	namespace physics {
		class CPeForceBuoyancy : public CPeForce {
		private:
			float m_immersionDepth;// depth for a total immersion of the particle in m
			float m_volume;//particle volume in m**3
			float m_liquidLevel;// in m
			float m_liquidDensity;// in kg/m**3

		public:
			CPeForceBuoyancy(float p_immersionDepth, float p_volume, float p_liquidLevel, float p_liquidDensity)
				: m_immersionDepth(p_immersionDepth)
				, m_volume(p_volume)
				, m_liquidLevel(p_liquidLevel)
				, m_liquidDensity(p_liquidDensity)
			{

			}

			void Compute(CPeParticle& p_particule, double p_timeStep) const;
		};
	}
}