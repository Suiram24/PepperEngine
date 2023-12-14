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

				if (obj[2] == nullptr) //Second object has an infinite mass
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