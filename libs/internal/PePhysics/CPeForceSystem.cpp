#include "CPeForceSystem.h"

namespace engine {
	namespace physics {

		CPeParticle& CPeForceSystem::CreateParticleComponent(pecore::CPeEntity* p_owner, double p_massInverse /*= 1*/, double p_damping /*= 0.999*/, pemaths::CPeVector3 p_gravity/* = pemaths::CPeVector3(0, -10, 0)*/)
		{
			return m_particlePool->Create(p_owner, p_massInverse, p_damping, p_gravity);
		}

		CPeForceDrag& CPeForceSystem::CreateForceDrag(float p_k1, float p_k2)
		{
			return m_dragPool->Create(p_k1, p_k2);
		}

		CPeForceAnchoredSpring& CPeForceSystem::CreateForceAnchoredSpring(const pemaths::CPeVector3& p_anchor, float p_k, float p_restLength)
		{
			return m_anchoredSpringPool->Create(p_anchor, p_k, p_restLength);
		}

		CPeForceSpring& CPeForceSystem::CreateForceSpring(CPeParticle& p_other, float p_k, float p_restLength)
		{
			return m_springPool->Create(p_other, p_k, p_restLength);
		}

		CPeForceBuoyancy& CPeForceSystem::CreateForceBuoyancy(float p_immersionDepth, float p_volume, float p_liquidLevel, float p_liquidDensity /*= 1*/)
		{
			return m_buoyancyPool->Create(p_immersionDepth, p_volume, p_liquidLevel, p_liquidDensity);
		}

		bool CPeForceSystem::AddForceToParticle(CPeForce* p_force, CPeParticle* p_particle, double p_lifespan /*= -1*/)
		{
			if (p_force != nullptr && p_particle != nullptr)
			{
				m_registry->Create(p_force, p_particle, p_lifespan);
			}
			else
			{
				return false;
			}
		}



		void CPeForceSystem::Update(double p_timeStep)
		{
			//
			// Add all forces to particles sumforces vector
			SPeParticleForceEntry* regIt = m_registry->First();
			for (size_t i = 0; i < m_registry->Size(); i++)
			{
				if (regIt->IsActive())
				{
					double lifeSpan = regIt->m_lifeSpan;

					if (lifeSpan == -1) // Infinite lifespan
					{
						regIt->m_force->Compute(*regIt->m_particle, p_timeStep);
					}
					else if (lifeSpan > p_timeStep) // More lifespan left than the timestep
					{
						regIt->m_force->Compute(*regIt->m_particle, p_timeStep);
						regIt->m_lifeSpan -= p_timeStep;
					}
					else //Less lifespan left than the timestep
					{
						regIt->m_force->Compute(*regIt->m_particle, lifeSpan);
						regIt->m_lifeSpan = 0;

						//TODO: Release force
					}
				}
					
				regIt++;
			}

			//
			// Integrate particles
			CPeParticle* partIt = m_particlePool->First();
			for (size_t  i = 0; i < m_particlePool->Size(); i++)
			{
				if (partIt->IsActive())
				{
					partIt->UpdatePrecisely(p_timeStep);
				}
				partIt++;
			}

		}


		void CPeForceSystem::AllocateObjectsPool()
		{

			m_registry = new pecore::CPeObjectPool<SPeParticleForceEntry, 4 * pecore::consts::maxEntityNumber>();

			m_dragPool = new pecore::CPeObjectPool<CPeForceDrag, pecore::consts::maxEntityNumber>();
			m_anchoredSpringPool = new pecore::CPeObjectPool<CPeForceAnchoredSpring, pecore::consts::maxEntityNumber>();
			m_springPool = new pecore::CPeObjectPool<CPeForceSpring, pecore::consts::maxEntityNumber>();
			m_buoyancyPool = new pecore::CPeObjectPool<CPeForceBuoyancy, pecore::consts::maxEntityNumber>();

			m_particlePool = new pecore::CPeObjectPool<CPeParticle, pecore::consts::maxEntityNumber>();
		}

		void CPeForceSystem::FreeObjectsPool()
		{
			delete m_registry;

			delete m_dragPool;
			delete m_anchoredSpringPool;
			delete m_springPool;
			delete m_buoyancyPool;

			delete m_particlePool;
		}
	}
}