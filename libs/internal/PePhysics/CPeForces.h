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
			//Methods
		public:
			virtual const pemaths::CPeVector3& Compute(const CPeParticle& p_particule) const;
		};
	}
}

#endif /* CPEFORCES_CPEFORCES_H */