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

		namespace consts
		{
			constexpr double projectionAngularLimit = 0.2;
		}

		class CPeCollisionResolutionSystem {

		public:

			static void ResolveInterpenetrations(std::vector<SPeContactInfos*> p_contacts, double p_timeStep);
			static void ResolveImpulsions(std::vector<SPeContactInfos*> p_contacts, double p_timeStep);

		private:

			//CPeCollisionResolutionSystem() {};

			//void ResolveCollisions(std::vector<SPeContactInfos*> p_contacts, double p_timeStep);



			
		};
	}
}

#endif /* PEPHYSICS_CPECOLLISIONRESOLUTION_SYSTEM_H */