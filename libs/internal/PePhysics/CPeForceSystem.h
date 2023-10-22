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

			

			CPeParticle& CreateParticleComponent(pecore::CPeEntity* p_owner, double p_massInverse = 1, double p_damping = 0.999);
			
			CPeForceDrag& CreateForceDrag(float p_k1, float p_k2);
			CPeForceAnchoredSpring& CreateForceAnchoredSpring(const pemaths::CPeVector3& p_anchor, float p_k, float p_restLength);
			CPeForceSpring& CreateForceSpring(CPeParticle& p_other, float p_k, float p_restLength);
			CPeForceBuoyancy& CreateForceBuoyancy(float p_immersionDepth, float p_volume, float p_liquidLevel, float p_liquidDensity = 1);

			bool AddForceToParticle(CPeForce* p_force, CPeParticle* p_particle, double p_lifespan = -1);

			void Update(double p_timeStep);

		protected:
		private:
			CPeForceSystem()
				: m_dragPool()
				, m_anchoredSpringPool()
				, m_springPool()
				, m_buoyancyPool()
				, m_particlePool()
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

			pecore::CPeObjectPool<CPeParticle, pecore::consts::maxEntityNumber>* m_particlePool;

		};
	}
}

#endif /* PEPHYSICS_CPEFORCESYSTEM_H */