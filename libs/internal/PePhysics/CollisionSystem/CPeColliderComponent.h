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
			CPeColliderComponent(pecore::CPeEntity& p_owner, double p_radius) 
				: CPeComponent(p_owner)
				, m_radius(p_radius)
			{
			}

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