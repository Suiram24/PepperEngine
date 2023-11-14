#include "CPeMeshRenderSystem.h"

namespace engine {
	namespace render {

		CPeMeshComponent* CPeMeshRenderSystem::CreateMeshComponent(pecore::CPeEntity* p_owner, vk::GenericRenderer& renderer, std::string model, std::string texture)
		{
			CPeMeshComponent* c = new CPeMeshComponent(p_owner, renderer, model, texture);
			m_meshComponentPool.push_back(c);
			return c;
		}

		void CPeMeshRenderSystem::AllocateObjectsPool()
		{
			m_meshComponentPool.reserve(100 * sizeof(CPeMeshComponent));
			//TODO: implement CPeObjectPool for MeshCOmponent
		}

		void CPeMeshRenderSystem::FreeObjectsPool()
		{
			//Temp work 
			for (CPeMeshComponent* c : m_meshComponentPool)
			{
				delete c;
			}
			m_meshComponentPool.clear();
		}

		void CPeMeshRenderSystem::Update()
		{
			for (CPeMeshComponent* c : m_meshComponentPool)
			{
				c->UpdateTransformMatrix();
			}

		}

	}
}