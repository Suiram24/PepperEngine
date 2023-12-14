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

            pemaths::CPeMatrix3 m_inertiaInverse;

            void UpdateOrientation(double p_timeStep);

            void UpdateInertia();//TODO: Delete

            void UpdateAngularAcceleration(double p_timeStep);

            void UpdateAngularVelocity(double p_timeStep);
            
            void ClearAccumulators();

            
           
        public:
            CPeRigidBody() :
                CPeParticle()
                , m_angularDamping(0)
                , m_angularVelocity(pemaths::CPeVector3(0, 0, 0))
                , m_sumTorques(pemaths::CPeVector3(0, 0, 0))
                , m_inertiaInverse(pemaths::CPeMatrix3())
            {
            }

            void Initialise(pecore::CPeEntity* p_owner, double p_massInverse, double p_damping, pemaths::CPeVector3 p_gravity, double p_angularDamping);

            void SetSphereInertia(double p_radius);

            void SetCubeInertia(double p_dx, double p_dy, double p_dz);

            void SetCylinderInertia(double p_height, double p_radius);

            void UpdatePrecisely(double p_timeStep) override;

            void AddForceAtPoint(const pemaths::CPeVector3& p_forceValue, const pemaths::CPeVector3& worldPoint) override;

            void AddForceAtBodyPoint(const pemaths::CPeVector3& p_forceValue, const pemaths::CPeVector3& localPoint) override;

            pemaths::CPeMatrix3& GetInverseInertia();


        };
    }
}

#endif