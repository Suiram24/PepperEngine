#include "CPeForceSystem.h"

namespace engine {
	namespace physics {

		CPeParticle* CPeForceSystem::CreateParticleComponent(pecore::CPeEntity* p_owner, double p_massInverse /*= 1*/, double p_damping /*= 0.999*/, pemaths::CPeVector3 p_gravity/* = pemaths::CPeVector3(0, -10, 0)*/)
		{
			return &m_particlePool->Create(p_owner, p_massInverse, p_damping, p_gravity);
		}

		CPeRigidBody* CPeForceSystem::CreateRigidBodyComponent(
			pecore::CPeEntity* p_owner,
			double p_massInverse,
			double p_damping,
			pemaths::CPeVector3 p_gravity,
			double angular_dampling
		)
		{
			return &m_rigidbodyPool->Create(p_owner, p_massInverse, p_damping, p_gravity, angular_dampling);
		}


		CPeForceDrag* CPeForceSystem::CreateForceDrag(float p_k1, float p_k2, pemaths::CPeVector3 p_appPoint)
		{
			return &m_dragPool->Create(p_k1, p_k2, p_appPoint);
		}

		CPeForceAnchoredSpring* CPeForceSystem::CreateForceAnchoredSpring(const pemaths::CPeVector3& p_anchor, float p_k, float p_restLength, pemaths::CPeVector3 p_bodyAnchor)
		{
			return &m_anchoredSpringPool->Create(p_anchor, p_k, p_restLength, p_bodyAnchor);
		}

		CPeForceSpring* CPeForceSystem::CreateForceSpring(CPeParticle* p_other, float p_k, float p_restLength, pemaths::CPeVector3 p_bodyAnchor, pemaths::CPeVector3 p_otherLocalAnchor)
		{
			return &m_springPool->Create(p_other, p_k, p_restLength, p_bodyAnchor, p_otherLocalAnchor);
		}

		CPeForceBuoyancy* CPeForceSystem::CreateForceBuoyancy(float p_immersionDepth, float p_volume, float p_liquidLevel, float p_liquidDensity /*= 1*/, pemaths::CPeVector3 p_appPoint)
		{
			return &m_buoyancyPool->Create(p_immersionDepth, p_volume, p_liquidLevel, p_liquidDensity, p_appPoint);
		}

		CPeForceFree* CPeForceSystem::CreateForceFree(pemaths::CPeVector3 p_forceValue, pemaths::CPeVector3 p_appPoint)
		{
			return &m_freePool->Create(p_forceValue, p_appPoint);
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

		bool CPeForceSystem::AddForceAtPoint(CPeForce* p_force, CPeRigidBody* p_rigidBody, pemaths::CPeVector3 localPoint, double p_lifespan)
		{
			if (p_force != nullptr && p_rigidBody != nullptr)
			{
				m_registry->Create(p_force, p_rigidBody, p_lifespan);
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
			
			CPeRigidBody* rigIt = m_rigidbodyPool->First();
			for (size_t  i = 0; i < m_rigidbodyPool->Size(); i++)
			{
				if (rigIt->IsActive())
				{
					rigIt->UpdatePrecisely(p_timeStep);
				}
				rigIt++;
			}

		}


		void CPeForceSystem::AllocateObjectsPool()
		{

			m_registry = new pecore::CPeObjectPool<SPeParticleForceEntry, 4 * pecore::consts::maxEntityNumber>();

			m_dragPool = new pecore::CPeObjectPool<CPeForceDrag, pecore::consts::maxEntityNumber>();
			m_anchoredSpringPool = new pecore::CPeObjectPool<CPeForceAnchoredSpring, pecore::consts::maxEntityNumber>();
			m_springPool = new pecore::CPeObjectPool<CPeForceSpring, pecore::consts::maxEntityNumber>();
			m_buoyancyPool = new pecore::CPeObjectPool<CPeForceBuoyancy, pecore::consts::maxEntityNumber>();
			m_freePool = new pecore::CPeObjectPool<CPeForceFree, pecore::consts::maxEntityNumber>();

			m_particlePool = new pecore::CPeObjectPool<CPeParticle, pecore::consts::maxEntityNumber>();
			m_rigidbodyPool = new pecore::CPeObjectPool <CPeRigidBody, pecore::consts::maxEntityNumber>();
		}

		void CPeForceSystem::FreeObjectsPool()
		{
			delete m_registry;

			delete m_dragPool;
			delete m_anchoredSpringPool;
			delete m_springPool;
			delete m_buoyancyPool;
			delete m_freePool;

			delete m_particlePool;
			delete m_rigidbodyPool;
		}
	}
}