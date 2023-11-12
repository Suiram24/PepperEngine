#ifndef CPERIGIDBODY_CPERIGIDBODY_H
#define CPERIGIDBODY_CPERIGIDBODY_H

#include "../PeMaths/PeMaths.h"
#include "CPeParticle.h"

namespace pemaths = engine::maths;

namespace engine {
	namespace physics {
        class CPeRigidBody : public CPeParticle {
        private:
            double m_angularDamping;

            pemaths::CPeVector3 m_angularVelocity;

            pemaths::CPeVector3 m_sumTorques;

            /**
             * @brief Compute the new angular velocity and orientation.
             * @param p_timeStep The time step to integrate in second.
            */
            void UpdateAngle(double p_timeStep);

            /**
             * @brief Call each frame to compute transformMatrix & normalize the orientation.
             */
            void ComputeDerivedData();
        };
    }
}

#endif