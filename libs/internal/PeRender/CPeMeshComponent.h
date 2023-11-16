#ifndef CPERENDER_CPEMESHCOMPONENT_H
#define CPERENDER_CPEMESHCOMPONENT_H

#include "../PeMaths/PeMaths.h"
#include "../PeEngineCore/PeEngineCore.h"
#include "CPeGraphicalObjects.h"

namespace pemaths = engine::maths;
namespace pecore = engine::core;

namespace engine {
	namespace render {

		/**
		 * @brief A component that allow to render an entity using a model and a texture. Updated by the CPeMeshRenderSystem.
		*/
		class CPeMeshComponent : public pecore::CPeComponent 
		{

		public:

			/**
			 * @brief Default CPeMeshComponent constructor
			 * @param p_owner: entity that will own this component
			 * @param renderer: the renderer that will render the model
			 * @param model: the local path of the model file
			 * @param texture: the local path of the texture file 
			*/
			CPeMeshComponent(pecore::CPeEntity* p_owner, vk::GenericRenderer& renderer, std::string model, std::string texture)
				: CPeComponent(*p_owner)
				, m_modelWatcher(renderer, model, texture)
			{
				p_owner->AddComponent(this);
			}

			/**
			 * @brief Update the ModelWatcher transform matrix using owner transform
			*/
			void UpdateTransformMatrix();

			//
			// TODO: implement Initialise(), SetActive() and CPeMeshComponent() to make the component work with object pools
			//void Initialise(pecore::CPeEntity& p_owner, vk::GenericRenderer& renderer, std::string texture);

		protected:
		private:
			

		public:
		protected:
		private:
			vk::ModelWatcher m_modelWatcher; //Model Watcher that hold the model, texture and transform matrix, and is rendered by the VulkanRenderer.

		};
	}
}

#endif /* CPERENDER_CPEMESHCOMPONENT_H */