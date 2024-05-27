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

			initializer.run();
			updater.run();

		}

		void CPeMeshRenderSystem::InitSystems(flecs::world& world, vk::GenericRenderer& _renderer)
		{
			renderer = &_renderer;

			//
			// Particle update
			initializer = world.system<MeshPlaceholder>("Mesh initializer")
				.each([this](flecs::entity e, MeshPlaceholder& mp)
				{
						int id = InitializeModelWatcher(mp.m_modelPath, mp.m_texturePath);
						e.set<MeshRenderer>({ id });
						e.remove<MeshPlaceholder>();
				});

			updater = world.system<const MeshRenderer, const Position, const Rotation*, const Scale*>("ModelWatcher Updater")
				.each([this](const MeshRenderer& mr, const Position& p, const Rotation* r, const Scale* s)
					{

						pemaths::CPeMatrix4 peTMatrix;

						if (r)
						{
							if (s)
							{
								pemaths::CPeTransform::ComputeMatrixFromTransform(peTMatrix, p.m_position, r->m_rotation, s->m_scale);
							}
							else
							{
								pemaths::CPeTransform::ComputeMatrixFromTransform(peTMatrix, p.m_position, r->m_rotation);
							}
						}
						else
						{
							pemaths::CPeTransform::ComputeMatrixFromTransform(peTMatrix, p.m_position);
						}
						

						glm::mat4 glmTMatrix = glm::mat4(
							peTMatrix.Get(0, 0), peTMatrix.Get(1, 0), peTMatrix.Get(2, 0), 0,
							peTMatrix.Get(0, 1), peTMatrix.Get(1, 1), peTMatrix.Get(2, 1), 0,
							peTMatrix.Get(0, 2), peTMatrix.Get(1, 2), peTMatrix.Get(2, 2), 0,
							peTMatrix.Get(0, 3), peTMatrix.Get(1, 3), peTMatrix.Get(2, 3), 1
						);

						UpdateModelWatcher(mr.ModelWatcherID, glmTMatrix);
					});
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