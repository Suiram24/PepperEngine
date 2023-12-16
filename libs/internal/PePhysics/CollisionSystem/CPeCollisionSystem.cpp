#include <list>
#include "CPeCollisionSystem.h"
#include "CPeKDTree.h"
#include "CPeNarrowPhaseSystem.h"
#include "CPeCollisionResolutionSystem.h"

namespace engine {
	namespace physics {
		
		
		void CPeCollisionSystem::UpdateCollision(double p_timeStep)
		{

			printf("Updating collision\n");
			//Get all colliders
			std::vector<CPeColliderComponent*> collidersList = m_collidersPool;


			// Broad phase
			printf("Broad Phase\n");
			CPeKDTree tree = CPeKDTree(X, collidersList);

			std::vector<std::pair<CPeColliderComponent*, CPeColliderComponent*>> possibleCollisions = tree.GetPossibleCollisions();
			
			// Narrow phase
			printf("Narrow phase\n");
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
			printf("Resolution phase\n");
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

		CPeColliderComponent* CPeCollisionSystem::CreateColliderComponent(pecore::CPeEntity& p_owner, double p_radius /*= 1*/)
		{
			//return &m_collidersPool->Create(p_owner, p_radius);
			CPeColliderComponent* col = new CPeColliderComponent(p_owner, CreateSphereShape(dynamic_cast<const pecore::CPeEntity&>(p_owner), p_radius));
			m_collidersPool.push_back(col);
			return col;
		}

		CPeSpherePrimitiveShape* CPeCollisionSystem::CreateSphereShape(const pecore::CPeEntity& p_owner, double p_radius)
		{
			CPeSpherePrimitiveShape* sphereShape = new CPeSpherePrimitiveShape(p_owner, p_radius);
			m_sphereShapesPool.push_back(sphereShape);
			return sphereShape;
		}



		void CPeCollisionSystem::AllocateObjectsPool()
		{
			//m_collidersPool = new pecore::CPeObjectPool<CPeColliderComponent, pecore::consts::maxEntityNumber>();
			m_sphereShapesPool.reserve(4 * pecore::consts::maxEntityNumber);
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
		}
	}
}