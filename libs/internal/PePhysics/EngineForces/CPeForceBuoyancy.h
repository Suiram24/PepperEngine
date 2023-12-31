#ifndef PEPHYSICS_CPEFORCEBUOYANCY_H
#define PEPHYSICS_CPEFORCEBUOYANCY_H

#include "..\CPeForce.h"

namespace pemaths = engine::maths;

namespace engine {
	namespace physics {
		class CPeForceBuoyancy : public CPeForce {
		private:
			float m_immersionDepth;// depth for half immersion of the particle in m (particle "radius")
			float m_volume;//particle volume in m**3
			float m_liquidLevel;// in m
			float m_liquidDensity;// in kg/m**3

		public:
			CPeForceBuoyancy()
				: CPeForce()
				, m_immersionDepth(0)
				, m_volume(0)
				, m_liquidLevel(0)
				, m_liquidDensity(0)
			{

			}

			void Initialise(float p_immersionDepth, float p_volume, float p_liquidLevel, float p_liquidDensity, pemaths::CPeVector3 p_appPoint = pemaths::CPeVector3());

			void Compute(CPeParticle& p_particule, double p_timeStep) const;
		};
	}
}

#endif /* PEPHYSICS_CPEFORCEBUOYANCY_H */
