#include <list>
#include "CPeCollisionSystem.h"
#include "CPeKDTree.h"
#include "CPeNarrowPhaseSystem.h"
#include "CPeCollisionResolutionSystem.h"
#include "../PePhysicsComponents.h"

namespace engine {
	namespace physics {


		void CPeCollisionSystem::InitSystems(flecs::world& world)
		{
			collisionUpdater = world.system<const Position, const SphereCollider, const Rotation*>("Collision_Updater")
				.each([this](flecs::entity& e, const Position& p, const SphereCollider& sc, const Rotation* r)
				{
						if (r)
						{
							colInfoList.push_back({e,p.m_position, r->m_rotation, sc.radius });
						}
						else
						{
							colInfoList.push_back({ e,p.m_position, pemaths::CPeQuaternion(1,0,0,0), sc.radius});
						}
						
				});
		}


		void CPeCollisionSystem::UpdateCollision(double p_timeStep)
		{
			int it = 0;

			//printf("Updating collision\n");
				//Get all colliders
			//std::vector<CPeColliderComponent*> collidersList = m_collidersPool;

			colInfoList.clear();
			colInfoRefs.clear();
			collisionUpdater.run();

			for (auto& c : colInfoList)
			{
				colInfoRefs.push_back(&c);
			}

			if (colInfoRefs.size() == 0)
			{
				return;
			}

			// Broad phase
			//printf("Broad Phase\n");
			CPeKDTree tree = CPeKDTree(X, colInfoRefs);

			std::vector<std::pair<ColliderInfos*, ColliderInfos*>> possibleCollisions = tree.GetPossibleCollisions();
			
			

			// Narrow phase
			//printf("Narrow phase\n");
			CPeNarrowPhaseSystem narrowPhase = CPeNarrowPhaseSystem::GetInstance();

			std::vector<SPeContactInfos*> contactInfosList = std::vector<SPeContactInfos*>();

			for (int k = 0; k < possibleCollisions.size(); k++)
			{

				double r1 = possibleCollisions[k].first->radius;
				double r2 = possibleCollisions[k].second->radius;

				double d = possibleCollisions[k].first->position.DistanceTo(possibleCollisions[k].second->position);

				if (d > (r1 + r2))
				{
					continue;
				}

				SPeContactInfos* data = new SPeContactInfos();

				data->normal = (possibleCollisions[k].first->position - possibleCollisions[k].second->position).NormalizeVector();
				data->interpenetration = r1 + r2 - d;
				data->contactPoint = possibleCollisions[k].second->position + r2 * data->normal;
				data->contactElasticity = 1;

				data->obj1 = possibleCollisions[k].second->owner;
				data->obj2 = possibleCollisions[k].first->owner;

				contactInfosList.push_back(data);
				printf("Collision detected %i\n");
			
			}

			do
			{
				++it;


				// Resolution
				//printf("Resolution phase\n");
				CPeCollisionResolutionSystem::ResolveInterpenetrations(contactInfosList, p_timeStep);
				CPeCollisionResolutionSystem::ResolveImpulsions(contactInfosList, p_timeStep);


				//FREE
				for (int k = 0; k < contactInfosList.size(); k++)
				{
					delete(contactInfosList[k]);
				}
				contactInfosList.clear();

				colInfoList.clear();
				colInfoRefs.clear();
				collisionUpdater.run();

				if (colInfoRefs.size() == 0)
				{
					return;
				}

				// Broad phase
				//printf("Broad Phase\n");
				CPeKDTree tree2 = CPeKDTree(X, colInfoRefs);
				possibleCollisions = tree2.GetPossibleCollisions();

				// Narrow phase
				//printf("Narrow phase\n");
				for (int k = 0; k < possibleCollisions.size(); k++)
				{

					double r1 = possibleCollisions[k].first->radius;
					double r2 = possibleCollisions[k].second->radius;

					double d = possibleCollisions[k].first->position.DistanceTo(possibleCollisions[k].second->position);

					if (d > (r1 + r2))
					{
						continue;
					}

					SPeContactInfos* data = new SPeContactInfos();

					data->normal = (possibleCollisions[k].first->position - possibleCollisions[k].second->position).NormalizeVector();
					data->interpenetration = r1 + r2 - d;
					data->contactPoint = possibleCollisions[k].second->position + r2 * data->normal;
					data->contactElasticity = 1;

					data->obj1 = possibleCollisions[k].first->owner;
					data->obj2 = possibleCollisions[k].second->owner;

					contactInfosList.push_back(data);

				}

				//if (contactInfosList.size() > 0)
				//{
				//	pintf("Iteration %i, contacts : %i \n", it, (contactInfosList.size()));
				//}
				

			}  while (contactInfosList.size() > 0 && it < consts::nbIterationCollider);


			//if (contactInfosList.size() > 0)
			//{
			//	printf("Incomplete iteration");
			//}
			//FREE
			for (int k = 0; k < contactInfosList.size(); k++)
			{
				delete(contactInfosList[k]);
			}
			contactInfosList.clear();

		}

		CPeColliderComponent* CPeCollisionSystem::CreateColliderComponent(pecore::CPeEntity& p_owner, double p_radius /*= 1*/)
		{
			//return &m_collidersPool->Create(p_owner, p_radius);
			CPeColliderComponent* col = new CPeColliderComponent(p_owner, CreateSphereShape(dynamic_cast<const pecore::CPeEntity&>(p_owner), p_radius));
			p_owner.AddComponent(col);
			m_collidersPool.push_back(col);
			return col;
		}

		CPeSpherePrimitiveShape* CPeCollisionSystem::CreateSphereShape(const pecore::CPeEntity& p_owner, double p_radius, double p_elasticity /*= 0.6*/)
		{
			CPeSpherePrimitiveShape* sphereShape = new CPeSpherePrimitiveShape(p_owner, p_radius, p_elasticity);
			m_sphereShapesPool.push_back(sphereShape);
			return sphereShape;
		}

		CPeBoxPrimitiveShape* CPeCollisionSystem::CreateBoxShape(const pecore::CPeEntity& p_owner, const pemaths::CPeVector3& p_size)
		{
			CPeBoxPrimitiveShape* Shape = new CPeBoxPrimitiveShape(p_owner, (p_size *0.5));
			m_boxShapesPool.push_back(Shape);
			return Shape;
		}

		CPePlanePrimitiveShape* CPeCollisionSystem::CreatePlaneShape(const pecore::CPeEntity& p_owner, pemaths::CPeVector3 p_normal, double p_offset)
		{
			CPePlanePrimitiveShape* Shape = new CPePlanePrimitiveShape(p_owner, p_normal, p_offset);
			m_planeShapesPool.push_back(Shape);
			return Shape;
		}

		void CPeCollisionSystem::SortContactInfos(std::vector<SPeContactInfos*>& contactInfos, int iteration)
		{
			int nbContacts = contactInfos.size();
			SPeContactInfos* tmp;
			if (nbContacts < 2)
			{
				return;
			}

			

			for (size_t i = 0; i < contactInfos.size()-1; i++)
			{
				for (size_t j = i+1; j < contactInfos.size(); j++)
				{
					if (contactInfos[i]->contactPoint.GetY() > contactInfos[j]->contactPoint.GetY())
					{
						tmp = contactInfos[i];
						contactInfos[i] = contactInfos[j];
						contactInfos[j] = tmp;
					}

				}
			}
		}



		void CPeCollisionSystem::AllocateObjectsPool()
		{
			//m_collidersPool = new pecore::CPeObjectPool<CPeColliderComponent, pecore::consts::maxEntityNumber>();
			m_sphereShapesPool.reserve(4 * pecore::consts::maxEntityNumber);
			m_boxShapesPool.reserve(4 * pecore::consts::maxEntityNumber);
			m_planeShapesPool.reserve(4 * pecore::consts::maxEntityNumber);
			m_collidersPool.reserve(pecore::consts::maxEntityNumber);
		}

		void CPeCollisionSystem::FreeObjectsPool()
		{
			//delete m_collidersPool;
			for (CPeColliderComponent* s : m_collidersPool)
			{
				delete s;
			}

			for (CPeSpherePrimitiveShape* s : m_sphereShapesPool)
			{
				delete s;
			}
			for (CPeBoxPrimitiveShape* s : m_boxShapesPool)
			{
				delete s;
			}
			for (CPePlanePrimitiveShape* s : m_planeShapesPool)
			{
				delete s;
			}
		}
	}
}