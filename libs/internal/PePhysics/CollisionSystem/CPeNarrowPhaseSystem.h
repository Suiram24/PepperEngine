#ifndef CPENARROWPHASESYSTEM_CPENARROWPHASESYSTEM_H
#define CPENARROWPHASESYSTEM_CPENARROWPHASESYSTEM_H

#include <vector>
#include "CPeColliderComponent.h"
#include "CPePrimitiveShape.h"
#include "CPeCollisionSystem.h"

namespace engine
{
	namespace physics {
		/**
		 * @brief The class that detect contacts between primitive shapes. Provides contacts infos.
		*/
		class CPeNarrowPhaseSystem {
		private:

		public:

			static CPeNarrowPhaseSystem& GetInstance()
			{
				static CPeNarrowPhaseSystem instance;
				return instance;
			}


			/**
			 * @brief Generate contact between the two primitives.
			 * @param CPePrimitiveShape the first primitive.
			 * @param CPePrimitiveShape the second primitive.
			 * @param SPeContactInfos the contact info to fill.
			 * @return true if a contact was generated, false if not.
			*/
			bool GenerateContacts(const CPeSpherePrimitiveShape& p_sphere1, const CPeSpherePrimitiveShape& p_sphere2, SPeContactInfos* data);
			bool GenerateContacts(const CPeSpherePrimitiveShape& p_sphere, const CPePlanePrimitiveShape& p_plane, SPeContactInfos* data);
			bool GenerateContacts(const CPeBoxPrimitiveShape& p_box, const CPePlanePrimitiveShape& p_plane, SPeContactInfos* data);
			bool GenerateContacts(const CPeBoxPrimitiveShape& p_box, const CPeSpherePrimitiveShape& p_sphere, SPeContactInfos* data);
			bool GenerateContacts(const CPeBoxPrimitiveShape& p_box1, const CPeBoxPrimitiveShape& p_box2, SPeContactInfos* data);
			
		private:

			CPeNarrowPhaseSystem()
			{
			}


		};
	}
}

#endif /* CPENARROWPHASESYSTEM_CPENARROWPHASESYSTEM_H */