#ifndef CPEPARTICLE_CPEPARTICLE_H
#define CPEPARTICLE_CPEPARTICLE_H

#include <vector>

#include "../PeMaths/PeMaths.h"
#include "../PeEngineCore/PeEngineCore.h"
#include "CPePhysicalObject.h"



namespace pemaths = engine::maths;
namespace pecore = engine::core;

namespace engine {
	namespace physics {

		/**
		 * @brief A simple implementation of a particle in standard Newton's Physics applied to video games. All units use SI.
		*/
		class CPeParticle : public CPePhysicalObject {
			//Fields
		private:
			pemaths::CPeVector3 m_velocity;// in m/s
			
			pemaths::CPeVector3 m_acceleration;// in m/s�

			double m_massInverse;// in kg

			double m_damping;// no unit

			pemaths::CPeVector3 m_gravity;

			pemaths::CPeVector3 m_sumForces;

			//Methods
		public:
			
			//TODO: Remove deprecated functions and constructors

			CPeParticle() :
				m_velocity(pemaths::CPeVector3(0., 0., 0.))
				, m_acceleration(pemaths::CPeVector3(0., 0., 0.))
				, m_massInverse(0)
				, m_damping(0)
				, m_sumForces(pemaths::CPeVector3(0., 0., 0.))
			{
			}

			void Initialise(pecore::CPeEntity* p_owner, double p_massInverse, double p_damping, pemaths::CPeVector3 p_gravity);

			void Initialise(pecore::CPeEntity& p_owner, double p_massInverse);//Deprecated

			/**
			 * @brief Accessor for m_massInverse.
			 * @return m_massInverse (m/s).
			*/
			double GetMassInverse() const;

			double GetMass() const;

			const pemaths::CPeVector3& GetGravity() const;

			/**
			 * @brief Accessor for m_owner's transform.
			 * @return m_owner->m_transform.
			*/
			pemaths::CPeTransform& GetTransform();

			/**
			 * @brief Accessor for m_velocity.
			 * @return m_velocity (m/s).
			*/
			const pemaths::CPeVector3& GetVelocity() const;

			/**
			 * @brief Accessor for m_acceleration.
			 * @return m_acceleration (m/s�).
			*/
			const pemaths::CPeVector3& GetAcceleration() const;

			/**
			 * @brief Setter for m_massInverse.
			 * @param p_massInverse A new mass inverse value. Should be positive or zero (for infinite mass) in kg-1.
			*/
			void SetMassInverse(double p_massInverse);

			/**
			 * @brief Setter for m_massInverse compute from the mass value.
			 * @param p_mass A new mass value. Should be strictly positive in kg.
			*/
			void SetMass(double p_mass);

			/**
			 * @brief Setter for m_gravity.
			 * @param p_gravity A new gravity value for the particle.
			*/
			void SetGravity(const pemaths::CPeVector3& p_gravity);

			/**
			 * @brief Setter for m_velocity.
			 * @param p_velocity A new velocity value for the particle in m/s.
			*/
			void SetVelocity(const pemaths::CPeVector3& p_velocity);

			/**
			 * @brief Setter for m_acceleration.
			 * @param p_acceleration A new acceleration value for the particle in m/s�.
			*/
			void SetAcceleration(const pemaths::CPeVector3& p_acceleration);

			/**
			 * @brief Setter for m_position.
			 * @param p_position A new position value for the particle.
			*/
			void SetPosition(const pemaths::CPeVector3& p_position) const;

			/**
			 * @brief Compute the new acceleration, velocity and position.
			 * @param p_timeStep The time step to integrate in second.
			*/
			void Update(double p_timeStep);

			/**
			 * @brief Compute the new acceleration, velocity and position with precision.
			 * @param p_timeStep The time step to integrate in second.
			*/
			void UpdatePrecisely(double p_timeStep);

			/**
			 * @brief Update the sum of all forces applied on the particule. Deprecated, forces should use AddForce instead.
			 * @param p_sumForces The new sum of all forces applied on the particule.
			 * @deprecated
			*/
			void SetSumForces(const pemaths::CPeVector3& p_sumForces);

			/**
			 * @brief Add a force to this particle sumforce vector
			 * @param p_forceValue The value of the force to be applied on the particule.
			*/
			void AddForce(const pemaths::CPeVector3& p_forceValue);

			void AddForceAtPoint(const pemaths::CPeVector3& p_forceValue, const pemaths::CPeVector3& worldPoint);

			void AddForceAtBodyPoint(const pemaths::CPeVector3& p_forceValue, const pemaths::CPeVector3& localPoint);

		private:
			
			/**
			 * @brief Compute the new acceleration based on all forces.
			*/
			void UpdateAcceleration(double p_timeStep);

			/**
			 * @brief Compute the new velocity.
			 * @param p_timeStep The time step to integrate in second.
			*/
			void UpdateVelocity(double p_timeStep);

			/**
			 * @brief Compute the new position with minimum precision.
			 * @param p_timeStep The time step to integrate in second.
			*/
			void UpdatePosition(double p_timeStep);

			/**
			 * @brief Compute the new position with maximum precision.
			 * @param p_timeStep The time step to integrate in second.
			*/
			void UpdatePositionPrecisely(double p_timeStep);


		};
	}
}

#endif /* CPEPARTICLE_CPEPARTICLE_H */