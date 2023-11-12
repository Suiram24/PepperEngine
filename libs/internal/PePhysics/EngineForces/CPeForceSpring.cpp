#include "CPeForceSpring.h"

namespace engine {
	namespace physics {

		void CPeForceSpring::Initialise(CPeParticle* p_other, float p_k, float p_restLength)
		{
			m_isActive = true;
			m_other = p_other;
			m_otherBodyAnchor = pemaths::CPeVector3(0,0,0);
			m_k = p_k;
			m_restLength = p_restLength;
		}

        void CPeForceSpring::Initialise(
			CPeParticle *p_other,
			pemaths::CPeVector3 p_otherLocalAnchor,
			float p_k,
			float p_restLength
		)
        {
			m_isActive = true;
			m_other = p_other;
			m_otherBodyAnchor = p_otherLocalAnchor;
			m_k = p_k;
			m_restLength = p_restLength;
        }

        void CPeForceSpring::Compute(CPeParticle& p_particle, double p_timeStep) const
		{
			pemaths::CPeVector3 v_globalOtherAnchor = m_other->GetTransform().GetPositionPoint(m_otherBodyAnchor),
								v_globalParticleAnchor = p_particle.GetTransform().GetPosition();
			
			pemaths::CPeVector3 d = v_globalOtherAnchor - v_globalParticleAnchor;
			p_particle.AddForce(d.NormalizeVector() * (m_k * (d.GetNorm() - m_restLength)) * p_timeStep);
			m_other->AddForceAtBodyPoint(d.NormalizeVector() * (-m_k * (d.GetNorm() - m_restLength)) * p_timeStep, m_otherBodyAnchor);
		}

		void CPeForceSpring::Compute(CPeRigidBody& p_rigidBody, double p_timeStep) const
		{
			pemaths::CPeVector3 v_globalOtherAnchor = m_other->GetTransform().GetPositionPoint(m_otherBodyAnchor),
								v_globalRigidBodyAnchor = p_rigidBody.GetTransform().GetPositionPoint(m_bodyAnchor);
			
			pemaths::CPeVector3 d = v_globalOtherAnchor - v_globalRigidBodyAnchor;
			p_rigidBody.AddForceAtBodyPoint(d.NormalizeVector() * (m_k * (d.GetNorm() - m_restLength)) * p_timeStep, m_bodyAnchor);
			m_other->AddForceAtBodyPoint(d.NormalizeVector() * (-m_k * (d.GetNorm() - m_restLength)) * p_timeStep, m_otherBodyAnchor);
		}

		
	}
}