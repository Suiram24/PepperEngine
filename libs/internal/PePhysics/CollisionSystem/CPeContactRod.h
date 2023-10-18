#ifndef CPECONTACTROD_CPECONTACTROD_H
#define CPECONTACTROD_CPECONTACTROD_H

#include "CPeParticleContact.h"


namespace engine {
	namespace physics {

		class CPeContactRod : public CPeParticleContact {
			//Fields
		private:
			float m_length;

			//Methods
		public:
			CPeContactRod(CPeParticle* p_particleA, CPeParticle* p_particleB, float p_restitution, float p_length)
				: CPeParticleContact(p_particleA, p_particleB, p_restitution)
				, m_length(p_length)
			{
			}

			CPeContactRod(CPeParticle* p_particleA, CPeParticle* p_particleB, float p_length)
				: CPeParticleContact(p_particleA, p_particleB)
				, m_length(p_length)
			{
			}

			float GetSeparatingSpeed() const;

		protected:
			pemaths::CPeVector3 ComputeContactNormal() const;
		};
	}
}

#endif /* CPECONTACTROD_CPECONTACTROD_H */