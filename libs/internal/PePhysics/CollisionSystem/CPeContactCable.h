#ifndef CPECONTACTCABLE_CPECONTACTCABLE_H
#define CPECONTACTCABLE_CPECONTACTCABLE_H

#include "CPeParticleContact.h"


namespace engine {
	namespace physics {

		/**
		 * @brief Represent a cable between two particle.
		*/
		class CPeContactCable : public CPeParticleContact {
			//Fields
		private:
			double m_maxLength;// The cable maximum length in meter
			
			//Methods
		public:
			CPeContactCable(CPeParticle* p_particleA, CPeParticle* p_particleB, double p_restitution, double p_maxLength)
				: CPeParticleContact(p_particleA, p_particleB, p_restitution)
				, m_maxLength(p_maxLength)
			{
			}

			double GetSeparatingSpeed() const;

		protected:
			double ComputePenetration() const;
			bool IsContactAtRest(double p_timeStep) const;

		};
	}
}

#endif /* CPECONTACTCABLE_CPECONTACTCABLE_H */