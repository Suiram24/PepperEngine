#ifndef CPECOLLISIONSYSTEM_CPECOLLISIONSYSTEM_H
#define CPECOLLISIONSYSTEM_CPECOLLISIONSYSTEM_H

#include <vector>
#include "CPeColliderComponent.h"
#include "../CPeParticle.h"
#include "SPeContactInfos.h"

#include "CPeBoxPrimitiveShape.h"
#include "CPePlanePrimitiveShape.h"

namespace engine 
{
	class CPeGameManager;

	namespace physics {
		

		namespace consts
		{
			constexpr int nbIterationCollider = 5;

		}

		/**
		 * @brief The class that detect contacts and resolve collisions. Provides an interface to add permanent contacts.
		*/
		class CPeCollisionSystem {
		private:

			// number of iteration for the solver
			int m_solverIteration;

			//pecore::CPeObjectPool<CPeColliderComponent, pecore::consts::maxEntityNumber>* m_collidersPool;

			std::vector<CPeSpherePrimitiveShape*> m_sphereShapesPool;
			std::vector<CPeBoxPrimitiveShape*> m_boxShapesPool;
			std::vector<CPePlanePrimitiveShape*> m_planeShapesPool;
			std::vector<CPeColliderComponent*> m_collidersPool;

		public:

			friend class engine::CPeGameManager;

			static CPeCollisionSystem& GetInstance()
			{
				static CPeCollisionSystem instance;
				return instance;
			}	

			/**
			 * @brief Detect the contacts and resolve te collisions.
			 * @param p_timeStep The time of simulation in second.
			 * @param p_particles A vector of the particles with a CPeColliderComponent.
			*/
			void UpdateCollision(double p_timeStep);

			CPeColliderComponent* CreateColliderComponent(pecore::CPeEntity& p_owner, double p_radius = 1);

			CPeSpherePrimitiveShape* CreateSphereShape(const pecore::CPeEntity& p_owner, double p_radius, double p_elasticity = 0.6);
			CPeBoxPrimitiveShape* CreateBoxShape(const pecore::CPeEntity& p_owner, const pemaths::CPeVector3& p_size);
			CPePlanePrimitiveShape* CreatePlaneShape(const pecore::CPeEntity& p_owner, pemaths::CPeVector3 p_normal, double p_offset);

		private:

			void SortContactInfos(std::vector<SPeContactInfos*>& contactInfos, int iteration);

			CPeCollisionSystem()
				: m_solverIteration(consts::nbIterationCollider)
				, m_sphereShapesPool()
				, m_collidersPool()
			{
			}

			void AllocateObjectsPool();
			void FreeObjectsPool();
		};
	}
}

#endif /* CPECOLLISIONSYSTEM_CPECOLLISIONSYSTEM_H */