#ifndef PEPHYSICS_CPECOLLISIONRESOLUTION_SYSTEM_H
#define PEPHYSICS_CPECOLLISIONRESOLUTION_SYSTEM_H

#include <vector>
#include "CPeColliderComponent.h"
#include "CPePrimitiveShape.h"
#include "CPeSpherePrimitiveShape.h"
#include "CPePlanePrimitiveShape.h"
#include "CPeBoxPrimitiveShape.h"
#include "CPeCollisionSystem.h"

namespace engine
{
	namespace physics {
		/**
		 * @brief The class that detect contacts between primitive shapes. Provides contacts infos.
		*/
		class CPeCollisionResolutionSystem {
		private:
			const double DOUBLE_MAX = 1000000;

		public:

			static CPeCollisionResolutionSystem& GetInstance()
			{
				static CPeCollisionResolutionSystem instance;
				return instance;
			}

			
		private:

			CPeCollisionResolutionSystem() {};

			void ResolveCollisions(std::vector<SPeContactInfos*> p_contacts, double p_timeStep);

			
		};
	}
}

#endif /* PEPHYSICS_CPECOLLISIONRESOLUTION_SYSTEM_H */