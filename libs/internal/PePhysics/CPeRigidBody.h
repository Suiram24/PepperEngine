#ifndef CPERIGIDBODY_CPERIGIDBODY_H
#define CPERIGIDBODY_CPERIGIDBODY_H

#include "../PeMaths/PeMaths.h"
#include "../PeEngineCore/PeEngineCore.h"

namespace pemaths = engine::maths;
namespace pecore = engine::core;

namespace engine {
	namespace physics {
        class CPeRigidBody : public pecore::CPeComponent {
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