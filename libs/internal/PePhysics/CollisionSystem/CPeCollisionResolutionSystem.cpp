#include "CPeCollisionResolutionSystem.h"

namespace engine
{
	namespace physics {


		void CPeCollisionResolutionSystem::ResolveInterpenetrations(std::vector<SPeContactInfos*> p_contacts, double p_timeStep)
		{
			for (SPeContactInfos* cInfo : p_contacts)
			{
				CPeRigidBody* obj[2] = { cInfo->obj1 , cInfo->obj2 };
				pemaths::CPeVector3 cPoint = cInfo->contactPoint;

				size_t nbRigidbody = 2;

				if (obj[1] == nullptr) //Second object has an infinite mass
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


				for (size_t i = 0; i < nbRigidbody; i++)
				{
					localContactPoint = obj[i]->GetTransform().GetPositionPointInLocal(cInfo->contactPoint);
					pemaths::CPeVector3 angularInertiaWorld = pemaths::CPeVector3::CrossProduct(localContactPoint, cInfo->normal);
					angularInertiaWorld = obj[i]->GetInverseInertia() * angularInertiaWorld;
					angularInertiaWorld = pemaths::CPeVector3::CrossProduct(localContactPoint, angularInertiaWorld);
					angularInertia[i] = pemaths::CPeVector3::ScalarProduct(angularInertiaWorld, cInfo->normal);

					linearInertia[i] = obj[i]->GetMassInverse();

					totalInertia += linearInertia[i] + angularInertia[i];
				}

				double inverseIntertia = 1 / totalInertia;

				for (size_t i = 0; i < nbRigidbody; i++)
				{
					double linearMove = cInfo->interpenetration * linearInertia[i] * inverseIntertia;
					double angularMove = cInfo->interpenetration * angularInertia[i] * inverseIntertia;

					localContactPoint = obj[i]->GetTransform().GetPositionPointInLocal(cInfo->contactPoint);
					pemaths::CPeVector3 impulsePerMove = obj[i]->GetInverseInertia() * pemaths::CPeVector3::CrossProduct(localContactPoint, cInfo->normal);

					pemaths::CPeQuaternion rot = obj[i]->GetTransform().GetOrientation();
					double invAngIntertia = (angularInertia[i] == 0) ? 0 : (1/angularInertia[i]); //avoid dividing by 0
					pemaths::CPeVector3 rotationVect = angularMove * (impulsePerMove * invAngIntertia);
					rot.RotateByVector(rotationVect);

					obj[i]->GetTransform().SetOrientation(rot);
					obj[i]->GetTransform().SetPosition(obj[i]->GetTransform().GetPosition() + (cInfo->normal * -linearMove));

					inverseIntertia *= -1;
				}

			}
		}


		void CPeCollisionResolutionSystem::ResolveImpulsions(std::vector<SPeContactInfos*> p_contacts, double p_timeStep)
		{
			for (SPeContactInfos* cInfo : p_contacts)
			{
				CPeRigidBody* obj[2] = { cInfo->obj1 , cInfo->obj2 };
				pemaths::CPeVector3 cPoint = cInfo->contactPoint;
				pemaths::CPeVector3 n = cInfo->normal;
				

				size_t nbRigidbody = 2;

				double SumMassInverse;

				if (obj[1] == nullptr) //Second object has an infinite mass
				{
					nbRigidbody = 1;
					SumMassInverse = obj[0]->GetMassInverse();
					if (pemaths::CPeVector3::ScalarProduct(n, obj[0]->GetVelocity()) <= 0)
					{
						continue;
					}
				}
				else
				{
					SumMassInverse = obj[0]->GetMassInverse() + obj[1]->GetMassInverse();
					double scalar =  pemaths::CPeVector3::ScalarProduct(n, obj[0]->GetVelocity()) - pemaths::CPeVector3::ScalarProduct(n, obj[1]->GetVelocity());
					if (scalar <= 0)
					{
						continue;
					}
				}

				pemaths::CPeVector3 contactPointVector, pointVelocity, angVelocitybyImpulse, velocity, contactVelocity;
				double e;
				//double linearVelDelta[2] = { .0 ,.0 };
				//double angularVelDelta[2] = { .0 ,.0 };
				double deltaVelocity = 0;

				
				e = 1;
				int sign = 1;
				for (size_t i = 0; i < nbRigidbody; i++)
				{
					e *= 0.6; //TODO: replace with elasticity
					contactPointVector = cInfo->contactPoint - obj[i]->GetTransform().GetPosition() ;
					pointVelocity = obj[i]->GetVelocity() + obj[i]->GetAngularVelocity() * contactPointVector.GetNorm();

					//
					// Velocity change by unit impulse
					//deltaVelocity += obj[i]->GetMassInverse(); //Linear velocity change by unit impulse
					angVelocitybyImpulse = pemaths::CPeVector3::CrossProduct(contactPointVector, n);
					angVelocitybyImpulse = obj[i]->GetInverseInertiaWorld() * angVelocitybyImpulse; 
					angVelocitybyImpulse = pemaths::CPeVector3::CrossProduct(angVelocitybyImpulse, contactPointVector);

					deltaVelocity += pemaths::CPeVector3::ScalarProduct(angVelocitybyImpulse, n);

					//
					// Closing velocity (TODO: inverse for second body ?)
					velocity += sign * pemaths::CPeVector3::CrossProduct(obj[i]->GetAngularVelocity(), contactPointVector);
					velocity += sign *obj[i]->GetVelocity();

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
					pemaths::CPeVector3 r = cInfo->contactPoint - obj[i]->GetTransform().GetPosition();

					obj[i]->SetVelocity(obj[i]->GetVelocity() - (k * n *  obj[i]->GetMassInverse()));
					obj[i]->SetAngularVelocity(obj[i]->GetAngularVelocity() - (obj[i]->GetInverseInertiaWorld() * pemaths::CPeVector3::CrossProduct(r, k * n)));
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