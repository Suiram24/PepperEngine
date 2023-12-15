#include <list>
#include "CPeCollisionSystem.h"
#include "CPeKDTree.h"
#include "CPeNarrowPhaseSystem.h"
#include "CPeCollisionResolutionSystem.h"

namespace engine {
	namespace physics {
		
		
		void CPeCollisionSystem::UpdateCollision(double p_timeStep, std::vector<CPeParticle*>* p_particles)
		{
			//Get all colliders
			std::vector<CPeColliderComponent*> collidersList = std::vector<CPeColliderComponent*>();
			for (int i = 0; i < p_particles->size(); i++)
			{
				CPeColliderComponent* collider = (*p_particles)[i]->GetOwner().GetComponent<CPeColliderComponent>();
				if (collider != nullptr)
				{
					collidersList.push_back(collider);
				}
			}

			// Broad phase
			CPeKDTree tree = CPeKDTree(X, collidersList);

			std::vector<std::pair<CPeColliderComponent*, CPeColliderComponent*>> possibleCollisions = tree.GetPossibleCollisions();

			// Narrow phase
			CPeNarrowPhaseSystem narrowPhase = CPeNarrowPhaseSystem::GetInstance();

			std::vector<SPeContactInfos*> contactInfosList = std::vector<SPeContactInfos*>();

			for (int k = 0; k < possibleCollisions.size(); k++)
			{
				const std::vector<CPePrimitiveShape*>& shapeList1 = possibleCollisions[k].first->GetPrimitives();
				const std::vector<CPePrimitiveShape*>& shapeList2 = possibleCollisions[k].second->GetPrimitives();

				for (int i = 0; i < shapeList1.size(); i++)
				{
					for (int j = 0; j < shapeList2.size(); j++)
					{
						narrowPhase.GenerateContacts(shapeList1[i], shapeList2[j], &contactInfosList);
					}
				}
			}

			// Resolution

			CPeCollisionResolutionSystem::ResolveInterpenetrations(contactInfosList, p_timeStep);
			CPeCollisionResolutionSystem::ResolveImpulsions(contactInfosList, p_timeStep);

			//TODO call resolution system on contactInfoList

			//FREE
			for (int k = 0; k < contactInfosList.size(); k++)
			{
				delete(contactInfosList[k]);
			}
			contactInfosList.clear();
		}

		CPeColliderComponent* CPeCollisionSystem::CreateColliderComponent(pecore::CPeEntity* p_owner, double p_radius /*= 1*/)
		{
			return &m_collidersPool->Create(p_owner, p_radius);
		}


		void CPeCollisionSystem::AllocateObjectsPool()
		{
			m_collidersPool = new pecore::CPeObjectPool<CPeColliderComponent, 4 * pecore::consts::maxEntityNumber>();
		}

		void CPeCollisionSystem::FreeObjectsPool()
		{
			delete m_collidersPool;
		}
	}
}