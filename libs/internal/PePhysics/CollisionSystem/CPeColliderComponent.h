#ifndef CPECOLLIDERCOMPONENT_CPECOLLIDERCOMPONENT_H
#define CPECOLLIDERCOMPONENT_CPECOLLIDERCOMPONENT_H

#include "../../PeEngineCore/PeEngineCore.h"

namespace pecore = engine::core;

namespace engine {
	namespace physics {

		/**
		 * @brief A class for objects that perform collisions.
		*/
		class CPeColliderComponent : public pecore::CPeComponent {
		private:
			double m_radius;// radius of the spheric particle in meter

		public:
			/**
			 * @brief constructor, shouldn't be used
			 * @deprecated
			*/
			CPeColliderComponent(pecore::CPeEntity& p_owner, double p_radius) 
				: CPeComponent(p_owner)
				, m_radius(p_radius)
			{
			}

			/**
			 * @brief default constructor, shouldn't be used outside of CPeObjectPool. 
			*/
			CPeColliderComponent()
				: CPeComponent()
				, m_radius(-1)
			{
			}
			
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

			/**
			 * @brief Get for radius.
			 * @return The particle radius in meter.
			*/
			double GetRadius() const;

			/**
			 * @brief Setter for the radius.
			 * @param p_radius A new radius in meter.
			*/
			void SetRadius(double p_radius);
		};
	}
}

#endif /* CPECOLLIDERCOMPONENT_CPECOLLIDERCOMPONENT_H */