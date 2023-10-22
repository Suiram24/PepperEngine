#include <list>
#include "CPeCollisionSystem.h"

namespace engine {
	namespace physics {
		
		void CPeCollisionSystem::ResolveCollisions(double p_timeStep)
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
		
		void CPeCollisionSystem::UpdateCollision(double p_timeStep, std::vector<CPeParticle*> p_particles)
		{
			DetectCollions(p_particles);
			ResolveCollisions(p_timeStep);
		}


		void CPeCollisionSystem::AddPermanentContact(CPeParticleContact* p_contact)
		{
			m_permanentContacts.push_back(p_contact);
		}

		void CPeCollisionSystem::CreateRodBetween(CPeParticle* p_particleA, CPeParticle* p_particleB, double p_restitution, double p_length)
		{
			CPeContactRod* rod = new CPeContactRod(p_particleA, p_particleB, p_restitution, p_length);
			AddPermanentContact(rod);
		}

		void CPeCollisionSystem::CreateCableBetween(CPeParticle* p_particleA, CPeParticle* p_particleB, double p_restitution, double p_maxLength)
		{
			CPeContactCable* cable = new CPeContactCable(p_particleA, p_particleB, p_restitution, p_maxLength);
			AddPermanentContact(cable);
		}

		void CPeCollisionSystem::DetectCollions(std::vector<CPeParticle*> p_particles)
		{
			int nbParticles = p_particles.size();
			
			for (int i = 0; i < nbParticles; i++)
			{
				for (int j = i+1; j < nbParticles; j++)
				{
					double dist = CPeParticleContact::DistanceBetweenParticle(*p_particles[i], *p_particles[j]);
					if (dist < 0)
					{
						CPeParticleContact* newContact = new CPeParticleContact(p_particles[i], p_particles[j]);
						m_oneTimeContacts.push_back(newContact);
					}
				}
			}
		}

	}
}