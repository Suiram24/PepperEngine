#ifndef CPECONTACTROD_CPECONTACTROD_H
#define CPECONTACTROD_CPECONTACTROD_H

#include "CPeParticleContact.h"


namespace engine {
	namespace physics {

		/**
		 * @brief Represent a rod between two particle.
		*/
		class CPeContactRod : public CPeParticleContact {
			//Fields
		private:
			double m_length;// the length of the rod in meter

			//Methods
		public:
			CPeContactRod(CPeParticle* p_particleA, CPeParticle* p_particleB, double p_restitution, double p_length)
				: CPeParticleContact(p_particleA, p_particleB, p_restitution)
				, m_length(p_length)
			{
			}

			CPeContactRod(CPeParticle* p_particleA, CPeParticle* p_particleB, double p_length)
				: CPeParticleContact(p_particleA, p_particleB)
				, m_length(p_length)
			{
			}

			double GetSeparatingSpeed() const;

		protected:
			pemaths::CPeVector3 ComputeContactNormal() const;
		};
	}
}

#endif /* CPECONTACTROD_CPECONTACTROD_H */