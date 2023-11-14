#ifndef CPERENDER_CPEMESHCOMPONENT_H
#define CPERENDER_CPEMESHCOMPONENT_H

#include <vector>

#include "../PeMaths/PeMaths.h"
#include "../PeEngineCore/PeEngineCore.h"
#include "CPeGraphicalObjects.h"



namespace pemaths = engine::maths;
namespace pecore = engine::core;

namespace engine {
	namespace render {

		/**
		 * @brief A simple implementation of a particle in standard Newton's Physics applied to video games. All units use SI.
		*/
		class CPeMeshComponent : public pecore::CPeComponent {
			//Fields
		private:
			vk::ModelWatcher m_modelWatcher;

			//Methods
		public:
			
			CPeMeshComponent(pecore::CPeEntity* p_owner, vk::GenericRenderer& renderer, std::string texture)
				: CPeComponent(*p_owner)
				, m_modelWatcher(renderer, texture)
			{
				p_owner->AddComponent(this);
			}

			void UpdateTransformMatrix();
			//void Initialise(pecore::CPeEntity& p_owner, vk::GenericRenderer& renderer, std::string texture);



		private:
			


		};
	}
}

#endif /* CPERENDER_CPEMESHCOMPONENT_H */