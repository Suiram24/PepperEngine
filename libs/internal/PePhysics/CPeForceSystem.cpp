#include "CPeForceSystem.h"

namespace engine {
	namespace physics {

		void CPeForceSystem::Update(double p_timeStep)
		{
			AnchoredSpringSystem.run(p_timeStep);

			AccelerationIntegrator.run(p_timeStep);
			VelocityIntegrator.run(p_timeStep);
			PositionIntegrator.run(p_timeStep);

			AngAccelerationIntegrator.run(p_timeStep);
			AngVelocityIntegrator.run(p_timeStep);
			RotationIntegrator.run(p_timeStep);
			
		}

		void CPeForceSystem::InitSystems(flecs::world& world)
		{
			//
			// Particle update
			AccelerationIntegrator = world.system<Acceleration, ForceReceiver, const Mass, const ParticleCustomValues*>("Acceleration_Integrator")
				.each([](flecs::iter& it, size_t, Acceleration& a, ForceReceiver& f, const Mass& m, const ParticleCustomValues *cv)
				{
					if (cv)
					{
						a.m_acceleration = (f.m_sumForces *(1 / it.delta_time()) * m.m_massInverse + cv->m_gravity);
					}
					else
					{
						a.m_acceleration = (f.m_sumForces * (1 / it.delta_time())) * m.m_massInverse + pemaths::CPeVector3(0,-9.81,0);//TODO: use the world const singleton component
					}

					f.m_sumForces = pemaths::CPeVector3();//Reset accumulator

					//m_acceleration = (m_sumForces * (1 / p_timeStep)) * m_massInverse + m_gravity;
				});

			VelocityIntegrator = world.system<Velocity, const Acceleration, const ParticleCustomValues*>("Velocity_Integrator")
				.each([](flecs::iter& it, size_t, Velocity& v, const Acceleration& a, const ParticleCustomValues* cv)
				{
					if (cv)
					{
						v.m_velocity = (v.m_velocity * cv->m_damping) +  (a.m_acceleration * it.delta_time());
					}
					else
					{
						v.m_velocity = (v.m_velocity * 0.999) + (a.m_acceleration * it.delta_time());;//TODO: use the world const singleton component
					}

					//m_velocity = (m_velocity * m_damping) + (m_acceleration * p_timeStep);
				});

			PositionIntegrator = world.system<Position, const Velocity>("Position_Integrator")
				.each([](flecs::iter& it, size_t, Position& p, const Velocity& v)
				{

					p.m_position = p.m_position + v.m_velocity * it.delta_time();//TODO: use the world const singleton component

					//m_owner->m_transform.SetPosition(m_owner->m_transform.GetPosition() + (m_velocity * p_timeStep));
				});

			//Rigidbody update

			AngAccelerationIntegrator = world.system<AngularAcceleration, RigidBody, const Rotation, const Scale*>("Angular_Rotation_Integrator")
				.each([](flecs::iter& it, size_t, AngularAcceleration& aa, RigidBody& rb, const Rotation& ro, const Scale* s)
				{
					if (s)
					{
						pemaths::CPeMatrix3 worldMatrix = ro.m_rotation.Normalize().ToMatrix3() * pemaths::CPeMatrix3(
							s->m_scale.GetX(), .0, .0,
							.0, s->m_scale.GetY(), .0,
							.0, .0, s->m_scale.GetZ()
						);
						pemaths::CPeMatrix3 intertiaInverseWorld = worldMatrix * rb.m_inertiaInverse * worldMatrix.Inverse();
						aa.m_angularAcceleration = intertiaInverseWorld * (rb.m_sumTorques * (1 / it.delta_time()));
					}
					else
					{
						pemaths::CPeMatrix3 worldMatrix = ro.m_rotation.Normalize().ToMatrix3();
						pemaths::CPeMatrix3 intertiaInverseWorld = worldMatrix * rb.m_inertiaInverse * worldMatrix.Inverse();
						aa.m_angularAcceleration = intertiaInverseWorld * (rb.m_sumTorques * (1 / it.delta_time()));
					}

					rb.m_sumTorques = pemaths::CPeVector3();//Reset accumulator

					// pemaths::CPeMatrix3 worldMatrix = GetTransform().GetTransformMatrix().ToMatrix3();
					//pemaths::CPeMatrix3 intertiaInverseWorld = worldMatrix * m_inertiaInverse * worldMatrix.Inverse();

					//m_angularAcceleration = intertiaInverseWorld * (m_sumTorques * (1 / p_timeStep));
				});

			AngVelocityIntegrator = world.system<AngularVelocity, const AngularAcceleration, const RigidBody>("Angular_Velocity_Integrator")
				.each([](flecs::iter& it, size_t, AngularVelocity& av, const AngularAcceleration& aa, const RigidBody& rb)
				{

					av.m_angularVelocity = av.m_angularVelocity * rb.m_angularDamping + aa.m_angularAcceleration * it.delta_time();

					// m_angularVelocity = m_angularVelocity * m_angularDamping + m_angularAcceleration * p_timeStep;
				});

			RotationIntegrator = world.system<Rotation, const AngularVelocity>("Rotation_Integrator")
				.each([](flecs::iter& it, size_t, Rotation& ro, const AngularVelocity& av)
				{
					pemaths::CPeQuaternion w(0, av.m_angularVelocity.GetX(), av.m_angularVelocity.GetY(), av.m_angularVelocity.GetZ());
					ro.m_rotation = ro.m_rotation + ((it.delta_time() / 2.0f) * w * ro.m_rotation);

					//pemaths::CPeTransform& transform = GetTransform();
					//pemaths::CPeQuaternion w(0, m_angularVelocity.GetX(), m_angularVelocity.GetY(), m_angularVelocity.GetZ());

					//transform.SetOrientation(transform.GetOrientation() + ((p_timeStep / 2.0f) * w * transform.GetOrientation()));
				});


			//Forces

			AnchoredSpringSystem = world.system<ForceReceiver, const AnchoredSpring, const Position, const Rotation*, RigidBody*, const Scale*>("AnchoredSpring")
				.each([](flecs::iter& it, size_t, ForceReceiver& fr, const AnchoredSpring& as, const Position& p, const Rotation* ro, RigidBody* rb, const Scale* s)
					{
						pemaths::CPeMatrix4 transformMatrix;
						if (ro)
						{
							if (s)
							{
								pemaths::CPeTransform::ComputeMatrixFromTransform(transformMatrix, p.m_position, ro->m_rotation, s->m_scale);
							}
							else
							{
								pemaths::CPeTransform::ComputeMatrixFromTransform(transformMatrix, p.m_position, ro->m_rotation);
							}
						}
						else
						{
							pemaths::CPeTransform::ComputeMatrixFromTransform(transformMatrix, p.m_position);
						}

						pemaths::CPeVector3 d = as.m_anchorPoint - (transformMatrix * as.m_bodyAnchor);
						pemaths::CPeVector3 forceValue = d.NormalizeVector() * (as.m_k * (d.GetNorm() - as.m_restLength)) * it.delta_time();

						if (rb)
						{
							rb->m_sumTorques += pemaths::CPeVector3::CrossProduct((transformMatrix * as.m_bodyAnchor) - p.m_position, forceValue);
						}

						fr.m_sumForces += forceValue;

						//pemaths::CPeVector3 globalBodyAnchor = p_particule.GetTransform().GetPositionPoint(m_bodyAnchor);
						//pemaths::CPeVector3 d = m_anchor - globalBodyAnchor;
						//p_particule.AddForceAtBodyPoint(d.NormalizeVector()* (m_k* (d.GetNorm() - m_restLength))* p_timeStep, m_bodyAnchor);
					});
		}





		//Old Update
		/*void CPeForceSystem::Update(double p_timeStep)
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

		}*/

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

		CPeForceCustomLocal* CPeForceSystem::CreateForceCustomLocal(pemaths::CPeVector3 p_forceValue, pemaths::CPeVector3 p_appPoint)
		{
			return &m_customLocalPool->Create(p_forceValue, p_appPoint);
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

		void CPeForceSystem::AllocateObjectsPool()
		{

			m_registry = new pecore::CPeObjectPool<SPeParticleForceEntry, 4 * pecore::consts::maxEntityNumber>();

			m_dragPool = new pecore::CPeObjectPool<CPeForceDrag, pecore::consts::maxEntityNumber>();
			m_anchoredSpringPool = new pecore::CPeObjectPool<CPeForceAnchoredSpring, pecore::consts::maxEntityNumber>();
			m_springPool = new pecore::CPeObjectPool<CPeForceSpring, pecore::consts::maxEntityNumber>();
			m_buoyancyPool = new pecore::CPeObjectPool<CPeForceBuoyancy, pecore::consts::maxEntityNumber>();
			m_freePool = new pecore::CPeObjectPool<CPeForceFree, pecore::consts::maxEntityNumber>();
			m_customLocalPool = new pecore::CPeObjectPool<CPeForceCustomLocal, pecore::consts::maxEntityNumber>();

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
			delete m_customLocalPool;

			delete m_particlePool;
			delete m_rigidbodyPool;
		}	
	}
}