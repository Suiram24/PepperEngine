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
			m_meshComponentPool.reserve(100 * sizeof(CPeMeshComponent*));
			m_modelWatcherPool.reserve(100 * sizeof(vk::ModelWatcher*));
			//TODO: implement CPeObjectPool for MeshCOmponent
		}

		void CPeMeshRenderSystem::FreeObjectsPool()
		{
			//Temp work 
			for (CPeMeshComponent* c : m_meshComponentPool)
			{
				delete c;
			}
			for (vk::ModelWatcher* c : m_modelWatcherPool)
			{
				delete c;
			}
			m_meshComponentPool.clear();
			m_modelWatcherPool.clear();
		}

		void CPeMeshRenderSystem::Update()
		{
			for (CPeMeshComponent* c : m_meshComponentPool)
			{
				c->UpdateTransformMatrix();
			}

			updater.ForEach(updaterFunction);

		}

		void CPeMeshRenderSystem::InitSystems(pecore::CPeWorld& world, vk::GenericRenderer& _renderer)
		{
			renderer = &_renderer;

			std::vector<std::pair<pecore::PeEntity, int>> ModelwatcherAddList;
			engine::core::ComponentDataMap dataMap = world.m_ComponentArchetypeMap.at(MeshPlaceholder::CompId());
			
			for (auto entityArchetype : world.m_EntitiesArchetypeMap)
			{
				if (dataMap.count(entityArchetype.second.archetypeID) != 0)
				{
					MeshPlaceholder* mp = world.Get<MeshPlaceholder>(entityArchetype.first);
					std::string modelPath = std::string(mp->m_modelPath);
					std::string texturePath = std::string(mp->m_texturePath);
					int id = InitializeModelWatcher(modelPath, texturePath);
					ModelwatcherAddList.push_back(std::make_pair(entityArchetype.first, id));
				}
			}

			for (auto pair : ModelwatcherAddList)
			{
				world.Set<MeshRenderer>(pair.first, { pair.second });
				world.Remove<MeshPlaceholder>(pair.first);
			}

			updater = world.Build<MeshRenderer, pecore::Position>();
			updaterFunction =[this](MeshRenderer& mr, pecore::Position& p)
					{

						pemaths::CPeMatrix4 peTMatrix;

						pemaths::CPeTransform::ComputeMatrixFromTransform(peTMatrix, p.m_position);


						glm::mat4 glmTMatrix = glm::mat4(
							peTMatrix.Get(0, 0), peTMatrix.Get(1, 0), peTMatrix.Get(2, 0), 0,
							peTMatrix.Get(0, 1), peTMatrix.Get(1, 1), peTMatrix.Get(2, 1), 0,
							peTMatrix.Get(0, 2), peTMatrix.Get(1, 2), peTMatrix.Get(2, 2), 0,
							peTMatrix.Get(0, 3), peTMatrix.Get(1, 3), peTMatrix.Get(2, 3), 1
						);

						UpdateModelWatcher(mr.ModelWatcherID, glmTMatrix);
					};
		}


		int CPeMeshRenderSystem::InitializeModelWatcher(std::string& modelPath, std::string& texture)
		{
			vk::ModelWatcher* newModel = new vk::ModelWatcher(*renderer, modelPath, texture);
			m_modelWatcherPool.push_back(newModel);
			return m_modelWatcherPool.size() - 1;
		}

		void CPeMeshRenderSystem::UpdateModelWatcher(int id, const glm::mat4& transform)
		{
			m_modelWatcherPool[id]->SetTransformMatrix(transform);
		}

	}
}