#ifndef CPEPARTICLE_CPEPARTICLE_H
#define CPEPARTICLE_CPEPARTICLE_H

#include <vector>

#include "../PeMaths/PeMaths.h"
#include "CPeMovable.h"
#include "CPeForces.h"

namespace pemaths = engine::maths;

namespace engine {
	namespace physics {
		/**
		 * @brief A simple implementation of a particle in standard Newton's Physics applied to video games.
		*/
		class CPeParticle : public CPeMovable {
			//Fields
		private:
			pemaths::CPeVector3 m_velocity;
			
			pemaths::CPeVector3 m_acceleration;

			double m_massInverse;

			double m_damping;

			double m_gravity;

			//std::vector<CPeForces*> m_forces;

			//Methods
		public:
			CPeParticle(const CPeTransform& p_transform, double p_massInverse, double p_damping) :
				CPeMovable(p_transform),
				m_velocity(pemaths::CPeVector3(0., 0., 0.)),
				m_acceleration(pemaths::CPeVector3(0., 0., 0.)),
				m_massInverse(p_massInverse),
				m_damping(p_damping),
				m_gravity(10.)
			{
			}

			CPeParticle(const CPeTransform& p_transform, double p_massInverse) :
				CPeMovable(p_transform),
				m_velocity(pemaths::CPeVector3(0., 0., 0.)),
				m_acceleration(pemaths::CPeVector3(0., 0., 0.)),
				m_massInverse(p_massInverse),
				m_damping(0.999),
				m_gravity(10.)
			{
			}

			/**
			 * @brief Accessor for m_velocity.
			 * @return m_velocity.
			*/
			const pemaths::CPeVector3& GetVelocity() const;

			/**
			 * @brief Accessor for m_acceleration.
			 * @return m_acceleration.
			*/
			const pemaths::CPeVector3& GetAcceleration() const;

			/**
			 * @brief Setter for m_massInverse.
			 * @param A new mass inverse value. Should be positive or zero (for infinite mass).
			*/
			void SetMassInverse(double p_massInverse);

			/**
			 * @brief Setter for m_massInverse compute from the mass value.
			 * @param A new mass value. Should be strictly positive.
			*/
			void SetMass(double p_mass);

			/**
			 * @brief Setter for m_gravity.
			 * @param A new gravity value for the particle.
			*/
			void SetGravity(double p_gravity);

			/**
			 * @brief Setter for m_velocity.
			 * @param A new velocity value for the particle.
			*/
			void SetVelocity(const pemaths::CPeVector3& p_velocity);

			/**
			 * @brief Setter for m_acceleration.
			 * @param A new acceleration value for the particle.
			*/
			void SetAcceleration(const pemaths::CPeVector3& p_acceleration);

			/**
			 * @brief Compute the sum of all forces, the new acceleration, velocity and position.
			 * @param p_timeStep The time step to integrate.
			*/
			void Update(double p_timeStep);

			/**
			 * @brief Compute the sum of all forces, the new acceleration, velocity and position with precision.
			 * @param p_timeStep The time step to integrate.
			*/
			void UpdatePrecisely(double p_timeStep);

		private:
			/**
			 * @brief Compute the sum of all forces in m_forces.
			 * @return The sum of m_forces.
			*/
			pemaths::CPeVector3 sumForces() const;

			/**
			 * @brief Compute the new acceleration based on all forces and gravity.
			*/
			void UpdateAcceleration(pemaths::CPeVector3& p_sumForces);

			/**
			 * @brief Compute the new velocity.
			 * @param p_timeStep The time step to integrate.
			*/
			void UpdateVelocity(double p_timeStep);

			/**
			 * @brief Compute the new position with minimum precision.
			 * @param p_timeStep The time step to integrate.
			*/
			void UpdatePosition(double p_timeStep);

			/**
			 * @brief Compute the new position with maximum precision.
			 * @param p_timeStep The time step to integrate.
			*/
			void UpdatePositionPrecisely(double p_timeStep);


		};
	}
}

#endif /* CPEPARTICLE_CPEPARTICLE_H */