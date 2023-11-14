#ifndef PERENDER_PEMESHRENDERSYSTEM_H
#define PERENDER_PEMESHRENDERSYSTEM_H

#include "../PeMaths/PeMaths.h"
#include "../PeEngineCore/PeEngineCore.h"
#include <vector>
#include "CPeMeshComponent.h"


namespace pemaths = engine::maths;
namespace pecore = engine::core;

namespace engine {

	class CPeGameManager;
	namespace render {
		
		 
		/**
		 * @brief A class for Newton's Physics forces.
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

			

			CPeMeshComponent* CreateMeshComponent(pecore::CPeEntity* p_owner, vk::GenericRenderer& renderer, std::string model, std::string texture);


			void Update();

		protected:
		private:
			CPeMeshRenderSystem()
				: m_meshComponentPool()
			{
			}

			void AllocateObjectsPool();
			void FreeObjectsPool();

		public:
		protected:
		private:
			
			//TODO: make this an object pool (may need to work on vk modelwatcher)
			std::vector<CPeMeshComponent*> m_meshComponentPool; 


		};
	}
}

#endif /* PERENDER_PEMESHRENDERSYSTEM_H */