#ifndef CPERIGIDBODY_CPERIGIDBODY_H
#define CPERIGIDBODY_CPERIGIDBODY_H

#include "../PeMaths/PeMaths.h"
#include "CPePhysicalObject.h"

namespace pemaths = engine::maths;

namespace engine {
	namespace physics {
        class CPeRigidBody : public CPePhysicalObject {
        private:
            float inverseMass;
            float linearDampling;
            pemaths::CPeVector3 position;
            pemaths::CPeVector3 velocity;

            pemaths::CPeQuaternion orientation;

            pemaths::CPeVector3 angularVelocity;

            pemaths::CPeMatrix4 transformMatrix;
        public:
            /**
             * @brief .Modify position, orientation & velocities
             */
            void Integrate(float p_timeStep);
            /**
             * @brief Call each frame to compute transformMatrix & normalize the orientation.
             */
            void ComputeDerivedData();
        };
    }
}

#endif