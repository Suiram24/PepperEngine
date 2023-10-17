#ifndef CPECONTACTGENERATOR_CPECONTACTGENERATOR_H
#define CPECONTACTGENERATOR_CPECONTACTGENERATOR_H

#include <vector>
#include "CPeParticleContact.h"

namespace engine {
	namespace physics {

		class CPeContactGenerator {
		public:
			virtual void AddContact(std::vector<CPeParticleContact>& p_contactVector) const = 0;
		};
	}
}

#endif /* CPECONTACTGENERATOR_CPECONTACTGENERATOR_H */