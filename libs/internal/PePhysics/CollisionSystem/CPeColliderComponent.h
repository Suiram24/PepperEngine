#ifndef CPECOLLIDERCOMPONENT_CPECOLLIDERCOMPONENT_H
#define CPECOLLIDERCOMPONENT_CPECOLLIDERCOMPONENT_H

#include "../../PeEngineCore/PeEngineCore.h"
#include "CPeShapeSphere.h"

namespace pecore = engine::core;

namespace engine {
	namespace physics {

		/**
		 * @brief A class for objects that perform collisions.
		*/
		class CPeColliderComponent : public pecore::CPeComponent {
		private:
			CPeShapeSphere m_boundingSphere;// radius of the spheric particle in meter
			std::vector<CPeShape*> m_shapesList;

		public:
			/**
			 * @brief constructor, shouldn't be used
			 * @deprecated
			*/
			CPeColliderComponent(pecore::CPeEntity& p_owner, double p_boundingSphereRadius, pemaths::CPeVector3 p_offset = pemaths::CPeVector3())
				: CPeComponent(p_owner)
				, m_boundingSphere(p_boundingSphereRadius, p_offset)
			{
			}

			/**
			 * @brief default constructor, shouldn't be used outside of CPeObjectPool. 
			*/
			//CPeColliderComponent()
			//	: CPeComponent()
			//	, m_radius(-1)
			//{
			//}
			
			///**
			// * @brief Initialise the component. Used by object pool
			//*/
			//void Initialise(pecore::CPeEntity* p_owner, double p_radius);

			///**
			// * @brief Used to set inactive the component in an object pool
			// * @param value Should be false
			//*/
			//void SetActive(bool value);


			///**
			// * @brief Used in object pooling to determine if the object is used or not
			// * @return true if object is used, false otherwise
			//*/
			//bool isActive() const;

			/**
			 * @brief Get the bounding sphere position in world coordinate
			 * @return the position vector in world coordinate
			*/
			pemaths::CPeVector3 GetBoundingSphereCenter() const;

			/**
			 * @brief Get the bounding sphere radius.
			 * @return the radius
			*/
			double GetBoundingSphereRadius() const;
		};
	}
}

#endif /* CPECOLLIDERCOMPONENT_CPECOLLIDERCOMPONENT_H */