#include "CPeRigidBody.h"
#include <iostream>

namespace engine {
	namespace physics {
        void CPeRigidBody::UpdateOrientation(double p_timeStep)
        {
            pemaths::CPeTransform& transform = GetTransform();
            pemaths::CPeQuaternion w(0, m_angularVelocity.GetX(), m_angularVelocity.GetY(), m_angularVelocity.GetZ());

            transform.SetOrientation(transform.GetOrientation() + ((p_timeStep / 2.0f) * w * transform.GetOrientation()));
        }

        void CPeRigidBody::UpdateInertia() //TODO: Delete
        {
            return;
            pemaths::CPeMatrix3 worldMatrix = GetTransform().GetTransformMatrix().ToMatrix3();
            if (worldMatrix.IsInversible()) {
                m_inertiaInverse = worldMatrix * m_inertiaInverse * worldMatrix.Inverse();
                //if (isinf(m_inertiaInverse.Get(0,0))) 

            }
            else {
                std::cout << "Inertia has not been updated!" << std::endl;
            }
        }

        void CPeRigidBody::UpdateAngularAcceleration(double p_timeStep)
        {
            //
            //Change Inertia from local to world
            pemaths::CPeMatrix3 worldMatrix = GetTransform().GetTransformMatrix().ToMatrix3();
            pemaths::CPeMatrix3 intertiaInverseWorld = worldMatrix * m_inertiaInverse * worldMatrix.Inverse();

            m_angularAcceleration = intertiaInverseWorld * (m_sumTorques * (1/ p_timeStep));
        } 

        void CPeRigidBody::UpdateAngularVelocity(double p_timeStep)
        {
            m_angularVelocity = m_angularVelocity * m_angularDamping + m_angularAcceleration * p_timeStep;
        }

        void CPeRigidBody::ClearAccumulators()
        {
            SetSumForces(pemaths::CPeVector3(0, 0, 0));
            m_sumTorques = pemaths::CPeVector3(0, 0, 0);
        }

        const pemaths::CPeMatrix3& CPeRigidBody::GetInverseInertia() const
        {
            return m_inertiaInverse;
        }

        pemaths::CPeMatrix3 CPeRigidBody::GetInverseInertiaWorld()
        {
            pemaths::CPeMatrix3 worldMatrix = GetTransform().GetTransformMatrix().ToMatrix3();
            pemaths::CPeMatrix3 intertiaInverseWorld = worldMatrix * m_inertiaInverse * worldMatrix.Inverse();
            return intertiaInverseWorld;
        }


        const pemaths::CPeVector3& CPeRigidBody::GetAngularVelocity() const
        {
            return m_angularVelocity;
        }

        void CPeRigidBody::SetAngularVelocity(pemaths::CPeVector3& p_newAngularVelocity)
        {
            m_angularVelocity = p_newAngularVelocity;
        }


        void CPeRigidBody::SetSphereInertia(double p_radius)
        {
            double value = 2.0f / 5.0f * GetMass() * p_radius * p_radius;
            m_inertiaInverse = pemaths::CPeMatrix3(
                value,0,0,
                0,value,0,
                0,0,value).Inverse();
        }

        void CPeRigidBody::SetCubeInertia(double p_dx, double p_dy, double p_dz)
        {
            double value1 = 1.0f/12.0f * GetMass() * (p_dy * p_dy + p_dz * p_dz);
            double value2 = 1.0f/12.0f * GetMass() * (p_dx * p_dx + p_dz * p_dz);
            double value3 = 1.0f/12.0f * GetMass() * (p_dx * p_dx + p_dy * p_dy);
            m_inertiaInverse = pemaths::CPeMatrix3(
                value1, 0, 0,
                0, value2, 0,
                0, 0, value3).Inverse();
        }

        void CPeRigidBody::SetCylinderInertia(double p_height, double p_radius)
        {
            double value1 = 1.0f / 12.0f * GetMass() * p_height * p_height + 1.0f / 4.0f * GetMass() * p_radius * p_radius;
            double value2 = 1.0f/2.0f * GetMass() * p_radius * p_radius;
            m_inertiaInverse = pemaths::CPeMatrix3(
                value1, 0, 0,
                0, value2, 0,
                0, 0, value1).Inverse();
        }

        void CPeRigidBody::Initialise(pecore::CPeEntity* p_owner, double p_massInverse, double p_damping, pemaths::CPeVector3 p_gravity, double p_angularDamping)
        {
            __super::Initialise(p_owner, p_massInverse, p_damping, p_gravity);
            m_angularDamping = p_angularDamping;
            SetSphereInertia(1);
        }

        void CPeRigidBody::UpdatePrecisely(double p_timeStep)
        {
           

            //UpdateInertia();

            UpdateAcceleration(p_timeStep);
            UpdateAngularAcceleration(p_timeStep);

            UpdateVelocity(p_timeStep);
            UpdateAngularVelocity(p_timeStep);

            UpdatePositionPrecisely(p_timeStep);
            UpdateOrientation(p_timeStep);

            ClearAccumulators();
        }

        void CPeRigidBody::AddForceAtPoint(const pemaths::CPeVector3& p_forceValue, const pemaths::CPeVector3& worldPoint)
        {
            pemaths::CPeVector3 lp = GetTransform().GetPositionPointInLocal(worldPoint);
            AddForceAtBodyPoint(p_forceValue, lp);
        }

        void CPeRigidBody::AddForceAtBodyPoint(const pemaths::CPeVector3& p_forceValue, const pemaths::CPeVector3& localPoint)
        {
            AddForce(p_forceValue);
            m_sumTorques += pemaths::CPeVector3::CrossProduct(GetTransform().GetPositionPoint(localPoint)-GetTransform().GetPosition(), p_forceValue);
            return;
        }
	}
}