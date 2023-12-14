#ifndef CPECOLLISIONSYSTEM_CPECOLLISIONSYSTEM_H
#define CPECOLLISIONSYSTEM_CPECOLLISIONSYSTEM_H

#include <vector>
#include "CPeColliderComponent.h"

namespace engine 
{
	class CPeGameManager;

	namespace physics {
		struct SPeContactInfos{
			pemaths::CPeVector3 contactPoint;
			pemaths::CPeVector3 normal;
			double interpenetration;
			CPeColliderComponent* collider1;
			CPeColliderComponent* collider2;
		};

		namespace consts
		{
			constexpr int nbIterationCollider = 1;
		}

		/**
		 * @brief The class that detect contacts and resolve collisions. Provides an interface to add permanent contacts.
		*/
		class CPeCollisionSystem {
		private:

			// number of iteration for the solver
			int m_solverIteration;

			pecore::CPeObjectPool<CPeColliderComponent, 4 * pecore::consts::maxEntityNumber>* m_collidersPool;

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
			void UpdateCollision(double p_timeStep, std::vector<CPeParticle*>* p_particles);

			CPeColliderComponent* CreateColliderComponent(pecore::CPeEntity* p_owner, double p_radius = 1);
		private:

			CPeCollisionSystem()
				: m_solverIteration(consts::nbIterationCollider)
				, m_collidersPool(nullptr)
			{
			}

			void AllocateObjectsPool();
			void FreeObjectsPool();
		};
	}
}

#endif /* CPECOLLISIONSYSTEM_CPECOLLISIONSYSTEM_H */