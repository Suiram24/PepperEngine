#ifndef SPECONTACTINFOS_SPECONTACTINFOS_H
#define SPECONTACTINFOS_SPECONTACTINFOS_H

#include "../../PeMaths/CPeVector3.h"
#include "../CPeRigidBody.h"	
namespace engine {
	namespace physics {


		struct SPeContactInfos {
			pemaths::CPeVector3 contactPoint;
			pemaths::CPeVector3 normal;
			double interpenetration;
			double contactElasticity;
			CPeRigidBody* obj1;
			CPeRigidBody* obj2;
		};
	}
}
#endif /* SPECONTACTINFOS_SPECONTACTINFOS_H */