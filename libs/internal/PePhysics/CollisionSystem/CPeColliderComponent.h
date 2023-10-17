#ifndef CPECOLLIDERCOMPONENT_CPECOLLIDERCOMPONENT_H
#define CPECOLLIDERCOMPONENT_CPECOLLIDERCOMPONENT_H

#include "../../PeEngineCore/PeEngineCore.h"

namespace pecore = engine::core;

namespace engine {
	namespace physics {

		class CPeColliderComponent : public pecore::CPeComponent {
		private:
			float m_radius;

		public:
			CPeColliderComponent(pecore::CPeEntity& p_owner, float p_radius) 
				: CPeComponent(p_owner)
				, m_radius(p_radius)
			{
			}

			float GetRadius() const;

			void SetRadius(float p_radius);
		};
	}
}

#endif /* CPECOLLIDERCOMPONENT_CPECOLLIDERCOMPONENT_H */