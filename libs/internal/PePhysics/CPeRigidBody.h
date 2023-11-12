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

            pemaths::CPeVector3 m_angularAcceleration;

            pemaths::CPeVector3 m_angularVelocity;

            pemaths::CPeVector3 m_sumTorques;

            pemaths::CPeVector3 m_inertiaInverse;

            /**
             * @brief Compute the new angular velocity and orientation.
             * @param p_timeStep The time step to integrate in second.
            */
            void UpdateAngle(double p_timeStep);

            /**
             * @brief Call each frame to compute transformMatrix & normalize the orientation.
             */
            void ComputeDerivedData();

            void UpdateOrientation();

            void UpdateInertia();

            void UpdateAngularAcceleration();

            void UpdateAngularVelocity();
            
            void ClearAccumulators();

        public:
            CPeRigidBody() :
                CPeParticle()
                , m_angularDamping(0)
                , m_angularVelocity(pemaths::CPeVector3(0, 0, 0))
                , m_sumTorques(pemaths::CPeVector3(0, 0, 0))
            {
            }

            void Initialise(pecore::CPeEntity* p_owner, double p_massInverse, double p_damping, pemaths::CPeVector3 p_gravity, double p_angularDamping);

            void UpdatePrecisely(double p_timeStep) override;

            void AddForceAtPoint(const pemaths::CPeVector3& p_forceValue, const pemaths::CPeVector3& worldPoint) override;

            void AddForceAtBodyPoint(const pemaths::CPeVector3& p_forceValue, const pemaths::CPeVector3& localPoint) override;

        };
    }
}

#endif