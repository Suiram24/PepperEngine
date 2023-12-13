#ifndef CPECOLLIDERCOMPONENT_CPECOLLIDERCOMPONENT_H
#define CPECOLLIDERCOMPONENT_CPECOLLIDERCOMPONENT_H

#include "../../PeEngineCore/PeEngineCore.h"
#include "CPePrimitiveShape.h"
#include "CPeSpherePrimitiveShape.h"

namespace pecore = engine::core;

namespace engine {
	namespace physics {

		/**
		 * @brief A class for objects that perform collisions.
		*/
		class CPeColliderComponent : public pecore::CPeComponent {
		private:
			CPeSpherePrimitiveShape* m_enclosingShape;
			std::vector<CPePrimitiveShape*> m_narrowShapes;

			

		public:

			/**
			 * @brief default constructor, shouldn't be used outside of CPeObjectPool. 
			*/
			CPeColliderComponent()
				: CPeComponent()
			{
			}
			/**
			 * @brief Get the global enveloping volume.
			 * @returns CPeSpherePrimitiveShape& - The global enveloping volume (a sphere).
			 */
			CPeSpherePrimitiveShape& GetGlobalVolume();
			
			/**
			 * @brief Initialise the component. Used by object pool
			*/
			void Initialise(pecore::CPeEntity* p_owner, double p_radius);

			/**
			 * @brief Used to set inactive the component in an object pool
			 * @param value Should be false
			*/
			void SetActive(bool value);


			/**
			 * @brief Used in object pooling to determine if the object is used or not
			 * @return true if object is used, false otherwise
			*/
			bool isActive() const;

			std::vector<CPePrimitiveShape*>& GetPrimitives();
		};
	}
}

#endif /* CPECOLLIDERCOMPONENT_CPECOLLIDERCOMPONENT_H */