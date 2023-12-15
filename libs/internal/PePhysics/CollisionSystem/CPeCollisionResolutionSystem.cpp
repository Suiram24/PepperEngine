#include "CPeCollisionResolutionSystem.h"

namespace engine
{
	namespace physics {
		void CPeCollisionResolutionSystem::ResolveCollisions(std::vector<SPeContactInfos*> p_contacts, double p_timeStep)
		{
			
		}


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
					double linearMove = (1-2*i) * cInfo->interpenetration * linearInertia[0] * inverseIntertia;
					double angularMove = (1-2*i) * cInfo->interpenetration * linearInertia[0] * inverseIntertia;

					localContactPoint = obj[i]->GetTransform().GetPositionPointInLocal(cInfo->contactPoint);
					pemaths::CPeVector3 impulsePerMove = obj[i]->GetInverseInertia() * pemaths::CPeVector3::CrossProduct(localContactPoint, cInfo->normal);

					pemaths::CPeQuaternion rot = obj[i]->GetTransform().GetOrientation();
					rot.RotateByVector(angularMove * (impulsePerMove * (1 / angularInertia[i])));

					obj[i]->GetTransform().SetOrientation(rot);
					obj[i]->GetTransform().SetPosition(obj[i]->GetTransform().GetPosition() + (cInfo->normal * linearMove));
				}

			}
		}


		void CPeCollisionResolutionSystem::ResolveImpulsions(std::vector<SPeContactInfos*> p_contacts, double p_timeStep)
		{
			for (SPeContactInfos* cInfo : p_contacts)
			{
				CPeRigidBody* obj[2] = { cInfo->obj1 , cInfo->obj2 };
				pemaths::CPeVector3 cPoint = cInfo->contactPoint;

				size_t nbRigidbody = 2;

				double SumMassInverse;

				if (obj[1] == nullptr) //Second object has an infinite mass
				{
					nbRigidbody = 1;
					SumMassInverse = obj[0]->GetMassInverse();
				}
				else
				{
					SumMassInverse = obj[0]->GetMassInverse() + obj[1]->GetMassInverse();
				}

				pemaths::CPeVector3 contactPointVector, pointVelocity, deltaWorld, velocity, contactVelocity;
				double k, e;
				//double linearVelDelta[2] = { .0 ,.0 };
				//double angularVelDelta[2] = { .0 ,.0 };
				double deltaVelocity = 0;

				
				e = 1;
				for (size_t i = 0; i < nbRigidbody; i++)
				{
					e *= 0.99; //TODO: replace with elasticity
					contactPointVector = cInfo->contactPoint - obj[i]->GetTransform().GetPosition() ;
					pointVelocity = obj[i]->GetVelocity() + obj[i]->GetAngularVelocity() * contactPointVector.GetNorm();

					//
					// Velocity change by unit impulse
					deltaVelocity += obj[i]->GetMassInverse();
					deltaWorld = pemaths::CPeVector3::CrossProduct(contactPointVector, cInfo->normal);
					deltaWorld = obj[i]->GetInverseInertiaWorld() * deltaWorld; 
					deltaWorld = pemaths::CPeVector3::CrossProduct(deltaWorld, contactPointVector);

					deltaVelocity += pemaths::CPeVector3::ScalarProduct(deltaWorld, cInfo->normal);

					//
					// Closing velocity (TODO: inverse for second body ?)
					velocity += pemaths::CPeVector3::CrossProduct(obj[i]->GetAngularVelocity(), contactPointVector);
					velocity += obj[i]->GetVelocity();

					
				}

				//
				// retrieve the velocity that is in the direction of the normal
				contactVelocity = pemaths::CPeVector3::OrthographicProjection(velocity, cInfo->normal);

				double desiredDeltaVelocity = -contactVelocity.GetNorm() * (1 + e);

				//
				//Calculating the impulse
				pemaths::CPeVector3 impulse = cInfo->normal.NormalizeVector();
				impulse = impulse * (desiredDeltaVelocity / deltaVelocity);

				//
				//Applying the impulse
				pemaths::CPeVector3 velocityChange, rotationChange;

				for (size_t i = 0; i < nbRigidbody; i++)
				{
					contactPointVector = cInfo->contactPoint - obj[i]->GetTransform().GetPosition();

					velocityChange = impulse * obj[i]->GetMassInverse();
					rotationChange = obj[i]->GetInverseInertiaWorld() * pemaths::CPeVector3::CrossProduct(impulse, contactPointVector);
				
					obj[i]->SetVelocity(obj[i]->GetVelocity() + velocityChange);
					obj[i]->SetAngularVelocity(obj[i]->GetAngularVelocity() + rotationChange);

					impulse = impulse * (-1); // inverse vector direction for second rigidbody if there is one
				}


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