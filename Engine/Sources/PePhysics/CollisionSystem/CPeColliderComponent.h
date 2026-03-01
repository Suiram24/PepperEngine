#ifndef CPECOLLIDERCOMPONENT_CPECOLLIDERCOMPONENT_H
#define CPECOLLIDERCOMPONENT_CPECOLLIDERCOMPONENT_H

#include "../../PeEngineCore/PeEngineCore.h"
#include "CPePrimitiveShape.h"
#include "CPeSpherePrimitiveShape.h"

namespace pecore = engine::core;

namespace engine {
	namespace physics {
		class CPePrimitiveShape;

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
			CPeColliderComponent(pecore::CPeEntity& p_owner, CPeSpherePrimitiveShape* p_enclosingSphere)
				: CPeComponent(p_owner)
				, m_enclosingShape(p_enclosingSphere)
			{
			}
			/**
			 * @brief Get the global enveloping volume.
			 * @returns CPeSpherePrimitiveShape& - The global enveloping volume (a sphere).
			 */
			CPeSpherePrimitiveShape& GetGlobalVolume();
			
			const std::vector<CPePrimitiveShape*>& GetPrimitives() const;

			void AddPrimitive(CPePrimitiveShape* p_primitive);
		};
	}
}

#endif /* CPECOLLIDERCOMPONENT_CPECOLLIDERCOMPONENT_H */