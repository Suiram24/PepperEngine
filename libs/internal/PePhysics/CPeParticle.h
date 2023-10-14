#ifndef CPEPARTICLE_CPEPARTICLE_H
#define CPEPARTICLE_CPEPARTICLE_H

#include <vector>

#include "../PeMaths/PeMaths.h"
#include "CPeMovable.h"
#include "CPeForce.h"

namespace pemaths = engine::maths;

namespace engine {
	namespace physics {
		/**
		 * @brief A simple implementation of a particle in standard Newton's Physics applied to video games. All units use SI.
		*/
		class CPeParticle : public CPeMovable {
			//Fields
		private:
			pemaths::CPeVector3 m_velocity;// in m/s
			
			pemaths::CPeVector3 m_acceleration;// in m/s²

			double m_massInverse;// in kg

			double m_damping;// no unit

			pemaths::CPeVector3 m_sumForces;

			//Methods
		public:
			CPeParticle(const CPeTransform& p_transform, double p_massInverse, double p_damping) :
				CPeMovable(p_transform),
				m_velocity(pemaths::CPeVector3(0., 0., 0.)),
				m_acceleration(pemaths::CPeVector3(0., 0., 0.)),
				m_massInverse(p_massInverse),
				m_damping(p_damping),
				m_sumForces(pemaths::CPeVector3(0.,0.,0.))
			{
			}

			CPeParticle(const CPeTransform& p_transform, double p_massInverse) :
				CPeMovable(p_transform),
				m_velocity(pemaths::CPeVector3(0., 0., 0.)),
				m_acceleration(pemaths::CPeVector3(0., 0., 0.)),
				m_massInverse(p_massInverse),
				m_damping(0.999),
				m_sumForces(pemaths::CPeVector3(0., 0., 0.))
			{
			}

			/**
			 * @brief Accessor for m_massInverse.
			 * @return m_massInverse (m/s).
			*/
			const double GetMassInverse() const;

			/**
			 * @brief Accessor for m_velocity.
			 * @return m_velocity (m/s).
			*/
			const pemaths::CPeVector3& GetVelocity() const;

			/**
			 * @brief Accessor for m_acceleration.
			 * @return m_acceleration (m/s²).
			*/
			const pemaths::CPeVector3& GetAcceleration() const;

			/**
			 * @brief Setter for m_massInverse.
			 * @param A new mass inverse value. Should be positive or zero (for infinite mass) in kg-1.
			*/
			void SetMassInverse(double p_massInverse);

			/**
			 * @brief Setter for m_massInverse compute from the mass value.
			 * @param A new mass value. Should be strictly positive in kg.
			*/
			void SetMass(double p_mass);

			/**
			 * @brief Setter for m_velocity.
			 * @param A new velocity value for the particle in m/s.
			*/
			void SetVelocity(const pemaths::CPeVector3& p_velocity);

			/**
			 * @brief Setter for m_acceleration.
			 * @param A new acceleration value for the particle in m/s².
			*/
			void SetAcceleration(const pemaths::CPeVector3& p_acceleration);

			/**
			 * @brief Setter for m_position.
			 * @param A new position value for the particle.
			*/
			void SetPosition(const pemaths::CPeVector3& p_position);

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
			 * @brief Update the sum of all forces applied on the particule.
			 * @param p_sumForces The new sum of all forces applied on the particule.
			*/
			void SetSumForces(pemaths::CPeVector3 p_sumForces);

		private:
			
			/**
			 * @brief Compute the new acceleration based on all forces.
			*/
			void UpdateAcceleration();

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