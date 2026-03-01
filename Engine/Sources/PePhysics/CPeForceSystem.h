#ifndef PEPHYSICS_CPEFORCESYSTEM_H
#define PEPHYSICS_CPEFORCESYSTEM_H

#include "../PeMaths/PeMaths.h"
#include "../PeEngineCore/PeEngineCore.h"
#include "CPeParticle.h"
#include "SPeParticleForceEntry.h"

#include "EngineForces/CPeForceAnchoredSpring.h"
#include "EngineForces/CPeForceBuoyancy.h"
#include "EngineForces/CPeForceDrag.h"
#include "EngineForces/CPeForceSpring.h"
#include "EngineForces/CPeForceFree.h"
#include "EngineForces/CPeForceCustomLocal.h"

namespace pemaths = engine::maths;
namespace pecore = engine::core;

namespace engine {

	class CPeGameManager;
	namespace physics {
		
		 
		/**
		 * @brief A class for Newton's Physics forces.
		*/
		class CPeForceSystem {
	public:

			friend class engine::CPeGameManager;
			//
			// Singleton setup
			static CPeForceSystem& GetInstance()
			{
				static CPeForceSystem instance;
				return instance;
			}

			

			CPeParticle* CreateParticleComponent(pecore::CPeEntity* p_owner, double p_massInverse = 1, double p_damping = 0.999, pemaths::CPeVector3 p_gravity = pemaths::CPeVector3(0, -10, 0));
			CPeRigidBody* CreateRigidBodyComponent(pecore::CPeEntity* p_owner, double p_massInverse = 1, double p_damping = 0.999, pemaths::CPeVector3 p_gravity = pemaths::CPeVector3(0, -10, 0), double angular_dampling = 0.999);
			
			CPeForceDrag* CreateForceDrag(float p_k1, float p_k2, pemaths::CPeVector3 p_appPoint = pemaths::CPeVector3());
			CPeForceAnchoredSpring* CreateForceAnchoredSpring(const pemaths::CPeVector3& p_anchor, float p_k, float p_restLength, pemaths::CPeVector3 p_bodyAnchor = pemaths::CPeVector3());
			CPeForceSpring* CreateForceSpring(CPeParticle* p_other, float p_k, float p_restLength, pemaths::CPeVector3 p_bodyAnchor = pemaths::CPeVector3(), pemaths::CPeVector3 p_otherLocalAnchor = pemaths::CPeVector3());
			CPeForceBuoyancy* CreateForceBuoyancy(float p_immersionDepth, float p_volume, float p_liquidLevel, float p_liquidDensity = 1, pemaths::CPeVector3 p_appPoint = pemaths::CPeVector3());
			CPeForceFree* CreateForceFree(pemaths::CPeVector3 p_forceValue, pemaths::CPeVector3 p_appPoint = pemaths::CPeVector3());
			CPeForceCustomLocal* CreateForceCustomLocal(pemaths::CPeVector3 p_forceValue, pemaths::CPeVector3 p_appPoint = pemaths::CPeVector3());

			bool AddForceToParticle(CPeForce* p_force, CPeParticle* p_particle, double p_lifespan = -1);
			bool AddForceAtPoint(CPeForce* p_force, CPeRigidBody* p_rigidBody, pemaths::CPeVector3 localPoint, double p_lifespan = -1);

			void Update(double p_timeStep);

		protected:
		private:
			CPeForceSystem()
				: m_registry(nullptr)
				, m_dragPool(nullptr)
				, m_anchoredSpringPool(nullptr)
				, m_springPool(nullptr)
				, m_buoyancyPool(nullptr)
				, m_freePool(nullptr)
				, m_customLocalPool(nullptr)
				, m_particlePool(nullptr)
				, m_rigidbodyPool(nullptr)
			{

			}

			void AllocateObjectsPool();
			void FreeObjectsPool();

		public:
		protected:
		private:
			

			pecore::CPeObjectPool<SPeParticleForceEntry, 4 * pecore::consts::maxEntityNumber>* m_registry;

			pecore::CPeObjectPool<CPeForceDrag, pecore::consts::maxEntityNumber>* m_dragPool;
			pecore::CPeObjectPool<CPeForceAnchoredSpring, pecore::consts::maxEntityNumber>* m_anchoredSpringPool;
			pecore::CPeObjectPool<CPeForceSpring, pecore::consts::maxEntityNumber>* m_springPool;
			pecore::CPeObjectPool<CPeForceBuoyancy, pecore::consts::maxEntityNumber>* m_buoyancyPool;
			pecore::CPeObjectPool<CPeForceFree, pecore::consts::maxEntityNumber>* m_freePool;
			pecore::CPeObjectPool<CPeForceCustomLocal, pecore::consts::maxEntityNumber>* m_customLocalPool;

			pecore::CPeObjectPool<CPeParticle, pecore::consts::maxEntityNumber>* m_particlePool;
			pecore::CPeObjectPool<CPeRigidBody, pecore::consts::maxEntityNumber>* m_rigidbodyPool;

		};
	}
}

#endif /* PEPHYSICS_CPEFORCESYSTEM_H */