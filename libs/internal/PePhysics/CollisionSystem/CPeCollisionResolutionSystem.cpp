#include "CPeCollisionResolutionSystem.h"
#include "../PePhysicsComponents.h"

namespace engine
{
	namespace physics {


		void CPeCollisionResolutionSystem::ResolveInterpenetrations(std::vector<SPeContactInfos*> p_contacts, double p_timeStep)
		{
			for (SPeContactInfos* cInfo : p_contacts)
			{
				flecs::entity obj[2] = { cInfo->obj1 , cInfo->obj2 };
				pemaths::CPeVector3 cPoint = cInfo->contactPoint;

				size_t nbRigidbody = 2;

				if (obj[1].get<Mass>()->m_massInverse == 0) //Second object has an infinite mass
				{
					nbRigidbody = 1;
				}
				else
				{
					nbRigidbody = 2;
				}

				double angularInertia[2] = { .0 ,.0 };
				double linearInertia[2] = { .0,.0 };
				double totalInertia = 0;
				pemaths::CPeVector3 localContactPoint;
				pemaths::CPeMatrix4 inverseTransform[2];
				pemaths::CPeMatrix3 inertiaInverse[2];
				pemaths::CPeVector3 position[2];

 				for (size_t i = 0; i < nbRigidbody; i++)
				{
					//Retrieve data
					inertiaInverse[i] = obj[i].get<RigidBody>()->m_inertiaInverse;
					position[i] = obj[i].get<Position>()->m_position;
					pemaths::CPeTransform::ComputeMatrixFromTransform(inverseTransform[i], position[i], obj[i].get<Rotation>()->m_rotation);
					inverseTransform[i] = inverseTransform[i].Inverse();

					//compute inertia
					localContactPoint = cInfo->contactPoint - position[i];
					pemaths::CPeVector3 angularInertiaWorld = pemaths::CPeVector3::CrossProduct(localContactPoint, cInfo->normal);
					angularInertiaWorld = inertiaInverse[i] * angularInertiaWorld;
					angularInertiaWorld = pemaths::CPeVector3::CrossProduct(localContactPoint, angularInertiaWorld);
					angularInertia[i] = pemaths::CPeVector3::ScalarProduct(angularInertiaWorld, cInfo->normal);

					linearInertia[i] = obj[i].get<Mass>()->m_massInverse;

					totalInertia += linearInertia[i] + angularInertia[i];
					
					
					
					
				}

				double inverseIntertia = 1 / totalInertia;

				for (size_t i = 0; i < nbRigidbody; i++)
				{
					double linearMove = cInfo->interpenetration * linearInertia[i] * inverseIntertia;
					double angularMove = cInfo->interpenetration * angularInertia[i] * inverseIntertia;

					localContactPoint = inverseTransform[i] * cInfo->contactPoint; 
					pemaths::CPeVector3 impulsePerMove = inertiaInverse[i] * pemaths::CPeVector3::CrossProduct(localContactPoint, cInfo->normal);

					pemaths::CPeQuaternion rot = obj[i].get<Rotation>()->m_rotation;
					double invAngIntertia = (angularInertia[i] == 0) ? 0 : (1/angularInertia[i]); //avoid dividing by 0
					pemaths::CPeVector3 rotationVect = angularMove * (impulsePerMove * invAngIntertia);
					rot.RotateByVector(rotationVect);

					obj[i].set<Rotation>({ rot });
					obj[i].set<Position>({ position[i] + (cInfo->normal * -linearMove) });

					inverseIntertia *= -1;
				}

			}
		}


		void CPeCollisionResolutionSystem::ResolveImpulsions(std::vector<SPeContactInfos*> p_contacts, double p_timeStep)
		{
			for (SPeContactInfos* cInfo : p_contacts)
			{
				flecs::entity obj[2] = { cInfo->obj1 , cInfo->obj2 };
				pemaths::CPeVector3 cPoint = cInfo->contactPoint;
				pemaths::CPeVector3 n = cInfo->normal;
				

				size_t nbRigidbody = 2;

				double SumMassInverse;

				double massInverse[2];
				pemaths::CPeVector3 objPosition[2];
				pemaths::CPeVector3 objVelocity[2];
				pemaths::CPeVector3 objAngVelocity[2];
				pemaths::CPeMatrix3 inertiaInverse[2];

				//retrieve data
				for (size_t i = 0; i < nbRigidbody; i++)
				{
					massInverse[i] = obj[i].get<Mass>()->m_massInverse;
					objPosition[i] = obj[i].get<Position>()->m_position;
					objVelocity[i] = obj[i].get<Velocity>()->m_velocity;
					objAngVelocity[i] = obj[i].get<AngularVelocity>()->m_angularVelocity;
					inertiaInverse[i] = obj[i].get<RigidBody>()->m_inertiaInverse;
				}

				SumMassInverse = massInverse[0] + massInverse[1];

				pemaths::CPeVector3 contactPointVector, pointVelocity, angVelocitybyImpulse, velocity, contactVelocity;
				double e = cInfo->contactElasticity;
				//double linearVelDelta[2] = { .0 ,.0 };
				//double angularVelDelta[2] = { .0 ,.0 };
				double deltaVelocity = 0;

				


				
				int sign = 1;
				for (size_t i = 0; i < nbRigidbody; i++)
				{

					contactPointVector = cInfo->contactPoint - objPosition[i];
					pointVelocity = objVelocity[i] + objAngVelocity[i] * contactPointVector.GetNorm();

					//
					// Velocity change by unit impulse
					//deltaVelocity += obj[i]->GetMassInverse(); //Linear velocity change by unit impulse
					angVelocitybyImpulse = pemaths::CPeVector3::CrossProduct(contactPointVector, n);
					angVelocitybyImpulse = inertiaInverse[i] * angVelocitybyImpulse;
					angVelocitybyImpulse = pemaths::CPeVector3::CrossProduct(angVelocitybyImpulse, contactPointVector);

					deltaVelocity += pemaths::CPeVector3::ScalarProduct(angVelocitybyImpulse, n);

					//
					// Closing velocity (TODO: inverse for second body ?)
					velocity += sign * pemaths::CPeVector3::CrossProduct(objAngVelocity[i], contactPointVector);
					velocity += sign * objVelocity[i];

					sign = -1;
				}

				double norm = velocity.GetNorm();

				if (pemaths::CPeVector3::ScalarProduct(n, velocity) <= 0)
				{
					return;
				}

				



				//
				//Alternative computation
				deltaVelocity += pemaths::CPeVector3::ScalarProduct((SumMassInverse * n), n);
				double numerator = (e + 1) * pemaths::CPeVector3::ScalarProduct(velocity, n);
				double k = numerator / deltaVelocity;
				for (size_t i = 0; i < nbRigidbody; i++)
				{
					pemaths::CPeVector3 r = cInfo->contactPoint - objPosition[i];

					obj[i].set<Velocity>({ objVelocity[i] - (k * n * massInverse[i]) });
					obj[i].set<AngularVelocity>({ objAngVelocity[i] - (inertiaInverse[i] * pemaths::CPeVector3::CrossProduct(r, k * n)) });
					k *= -1;
				}
				
				return;



			}

		}



	}
}






/*

for (int k = 0; k < m_solverIteration; k++)
{
	std::list<CPeParticleContact*> contacts;

	for (int it = 0; it < m_oneTimeContacts.size(); it++)
	{
		contacts.push_front(m_oneTimeContacts[it]);
	}

	for (int it = 0; it < m_permanentContacts.size(); it++)
	{
		contacts.push_front(m_permanentContacts[it]);
	}

	contacts.sort(CPeParticleContact::CompareContactSeparationSpeed);
	while (!contacts.empty())
	{
		CPeParticleContact* cont = contacts.front();
		contacts.pop_front();

		if (cont->GetSeparatingSpeed() > 0)
		{
			break;
		}

		cont->Resolve(p_timeStep);
	}
}

for (int it = 0; it < m_oneTimeContacts.size(); it++)
{
	delete m_oneTimeContacts[it];
}
m_oneTimeContacts.clear();
*/