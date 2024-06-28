#ifndef PERENDER_PEMESHRENDERSYSTEM_H
#define PERENDER_PEMESHRENDERSYSTEM_H

#include "../PeMaths/PeMaths.h"
#include "../PeEngineCore/PeEngineCore.h"
#include <vector>
#include "CPeMeshComponent.h"
#include "PeRenderComponents.h"


namespace pemaths = engine::maths;
namespace pecore = engine::core;

namespace engine {

	class CPeGameManager;
	namespace render {
		
		 
		/**
		 * @brief The singleton that manage the MeshComponents (create and update them)
		*/
		class CPeMeshRenderSystem {
	public:

			friend class engine::CPeGameManager;
			//
			// Singleton setup
			static CPeMeshRenderSystem& GetInstance()
			{
				static CPeMeshRenderSystem instance;
				return instance;
			}

			
			/**
			 * @brief Create a mesh component and attach it to it's owner
			 * @param p_owner: entity that will own this component
			 * @param renderer: the renderer that will render the model
			 * @param model: the local path of the model file
			 * @param texture: the local path of the texture file
			*/
			CPeMeshComponent* CreateMeshComponent(pecore::CPeEntity* p_owner, vk::GenericRenderer& renderer, std::string model, std::string texture);

			/**
			 * @brief Update the transform matrix of the model watchers for all the mesh components
			*/
			void Update();

			void InitSystems(pecore::CPeWorld& world, vk::GenericRenderer& _renderer);

			int InitializeModelWatcher(std::string& modelPath, std::string& texture);

			void UpdateModelWatcher(int id, const glm::mat4& transform);

		protected:
		private:
			CPeMeshRenderSystem()
				: m_meshComponentPool()
				, m_modelWatcherPool()
				, initializer()
				, updater()
				, renderer(nullptr)
			{
			}

			void AllocateObjectsPool();
			void FreeObjectsPool();

		public:
		protected:
		private:
			
			//TODO: make this an object pool (may need to work on vk modelwatcher)
			std::vector<CPeMeshComponent*> m_meshComponentPool; 

			std::vector<vk::ModelWatcher*> m_modelWatcherPool;
			pecore::CPeQuery<MeshPlaceholder> initializer;
			pecore::CPeQuery<MeshRenderer, pecore::Position> updater;
			vk::GenericRenderer* renderer;
			std::function<void(MeshPlaceholder&)> initializeFunction;
			std::function<void(MeshRenderer&, pecore::Position&)> updaterFunction;


		};
	}
}

#endif /* PERENDER_PEMESHRENDERSYSTEM_H */