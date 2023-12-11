#include "CPeNarrowPhaseSystem.h"

namespace engine
{
	namespace physics {
		void CPeCollisionResolutionSystem::ResolveCollisions(std::vector<SPeContactInfos*> p_contacts, double p_timeStep)
		{
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
		}

	}
}