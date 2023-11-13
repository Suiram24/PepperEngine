#include "CPeForceAnchoredSpring.h"

namespace engine {
	namespace physics {

		void CPeForceAnchoredSpring::Initialise(const pemaths::CPeVector3& p_anchor, float p_k, float p_restLength)
		{
			m_isActive = true;
			m_anchor = p_anchor;
			m_localAnchor = pemaths::CPeVector3(0,0,0);
			m_k = p_k;
			m_restLength = p_restLength;
		}

		void CPeForceAnchoredSpring::Initialise(
			const pemaths::CPeVector3& p_anchor,
			const pemaths::CPeVector3& p_localAnchor,
			float p_k,
			float p_restLength
		)
		{
			m_isActive = true;
			m_anchor = p_anchor;
			m_localAnchor = p_localAnchor;
			m_k = p_k;
			m_restLength = p_restLength;
		}

		void CPeForceAnchoredSpring::Compute(CPeParticle* p_particule, double p_timeStep) const
		{
			pemaths::CPeVector3 d = m_anchor - p_particule->GetTransform().GetPosition();
			p_particule->AddForce(d.NormalizeVector() * (m_k * (d.GetNorm() - m_restLength)) * p_timeStep);
			return;
		}

		void CPeForceAnchoredSpring::Compute(CPeRigidBody* p_rigidBody, double p_timeStep) const
		{
			pemaths::CPeVector3 v_globalRigidBodyAnchor = p_rigidBody->GetTransform().GetPositionPoint(m_anchor);

			pemaths::CPeVector3 d = m_anchor - v_globalRigidBodyAnchor;
			p_rigidBody->AddForceAtBodyPoint(d.NormalizeVector() * (m_k * (d.GetNorm() - m_restLength)) * p_timeStep, m_localAnchor);
			return;
		}


	}
}