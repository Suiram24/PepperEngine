#ifndef CPE_PHYSICAL_OBJECT_H
#define CPE_PHYSICAL_OBJECT_H

#include <vector>

#include "../PeMaths/PeMaths.h"
#include "../PeEngineCore/PeEngineCore.h"



namespace pemaths = engine::maths;
namespace pecore = engine::core;

namespace engine {
	namespace physics {

		/**
		 * @brief A simple implementation of a particle in standard Newton's Physics applied to video games. All units use SI.
		*/
		class CPePhysicalObject : public pecore::CPeComponent {
			//Fields
		protected:
			pemaths::CPeVector3 m_velocity;// in m/s
			
			pemaths::CPeVector3 m_acceleration;// in m/s�

			double m_massInverse;// in kg

			double m_damping;// no unit

			pemaths::CPeVector3 m_gravity;

			pemaths::CPeVector3 m_sumForces;

			//Methods
		public:
			
			//TODO: Remove deprecated functions and constructors

			CPePhysicalObject();

			virtual void Initialise(pecore::CPeEntity* p_owner, double p_massInverse, double p_damping, pemaths::CPeVector3 p_gravity) = 0;

			/**
			 * @brief Accessor for m_massInverse.
			 * @return m_massInverse (m/s).
			*/
			virtual double GetMassInverse() const = 0;

			virtual double GetMass() const = 0;

			virtual const pemaths::CPeVector3& GetGravity() const = 0;

			/**
			 * @brief Accessor for m_owner's transform.
			 * @return m_owner->m_transform.
			*/
			virtual pemaths::CPeTransform& GetTransform() = 0;

			/**
			 * @brief Accessor for m_velocity.
			 * @return m_velocity (m/s).
			*/
			virtual const pemaths::CPeVector3& GetVelocity() const = 0;

			/**
			 * @brief Accessor for m_acceleration.
			 * @return m_acceleration (m/s�).
			*/
			virtual const pemaths::CPeVector3& GetAcceleration() const = 0;

			/**
			 * @brief Setter for m_massInverse.
			 * @param p_massInverse A new mass inverse value. Should be positive or zero (for infinite mass) in kg-1.
			*/
			virtual void SetMassInverse(double p_massInverse) = 0;

			/**
			 * @brief Setter for m_massInverse compute from the mass value.
			 * @param p_mass A new mass value. Should be strictly positive in kg.
			*/
			virtual void SetMass(double p_mass) = 0;

			/**
			 * @brief Setter for m_gravity.
			 * @param p_gravity A new gravity value for the particle.
			*/
			virtual void SetGravity(const pemaths::CPeVector3& p_gravity) = 0;

			/**
			 * @brief Setter for m_velocity.
			 * @param p_velocity A new velocity value for the particle in m/s.
			*/
			virtual void SetVelocity(const pemaths::CPeVector3& p_velocity) = 0;

			/**
			 * @brief Setter for m_acceleration.
			 * @param p_acceleration A new acceleration value for the particle in m/s�.
			*/
			virtual void SetAcceleration(const pemaths::CPeVector3& p_acceleration) = 0;

			/**
			 * @brief Setter for m_position.
			 * @param p_position A new position value for the particle.
			*/
			virtual void SetPosition(const pemaths::CPeVector3& p_position) const = 0;

			/**
			 * @brief Compute the new acceleration, velocity and position.
			 * @param p_timeStep The time step to integrate in second.
			*/
			virtual void Update(double p_timeStep) = 0;

			/**
			 * @brief Compute the new acceleration, velocity and position with precision.
			 * @param p_timeStep The time step to integrate in second.
			*/
			virtual void UpdatePrecisely(double p_timeStep) = 0;

			/**
			 * @brief Update the sum of all forces applied on the particule. Deprecated, forces should use AddForce instead.
			 * @param p_sumForces The new sum of all forces applied on the particule.
			 * @deprecated
			*/
			virtual void SetSumForces(const pemaths::CPeVector3& p_sumForces) = 0;

			/**
			 * @brief Add a force to this particle sumforce vector
			 * @param p_forceValue The value of the force to be applied on the particule.
			*/
			virtual void AddForce(const pemaths::CPeVector3& p_forceValue) = 0;
		};
	}
}

#endif /* CPEPARTICLE_CPEPARTICLE_H */