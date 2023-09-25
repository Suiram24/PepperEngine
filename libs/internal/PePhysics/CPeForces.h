#ifndef CPEFORCES_CPEFORCES_H
#define CPEFORCES_CPEFORCES_H

#include "../PeMaths/PeMaths.h"
#include "CPeParticle.h"

namespace pemaths = engine::maths;

namespace engine {
	namespace physics {
		
		/**
		 * @brief A class for Newton's Physics forces.
		*/
		class CPeForces {

			//Fields
		private:
			pemaths::CPeVector3 m_value;

			//Methods
		public:
			CPeForces(const pemaths::CPeVector3& p_value) :m_value(p_value)
			{
			}

			/**
			 * @brief Accessor for the force's value.
			 * @return m_value.
			*/
			const pemaths::CPeVector3& GetValue() const;

			//virtual const pemaths::CPeVector3& Compute(const CPeParticle& p_particule) const = 0;

		};
	}
}

#endif /* CPEFORCES_CPEFORCES_H */