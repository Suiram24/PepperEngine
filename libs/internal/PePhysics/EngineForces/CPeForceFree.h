#ifndef PEPHYSICS_CPEFORCEFREE_H
#define PEPHYSICS_CPEFORCEFREE_H

#include "..\CPeForce.h"

namespace pemaths = engine::maths;

namespace engine {
	namespace physics {
		class CPeForceFree : public CPeForce {
		private:
			pemaths::CPeVector3 m_forceValue;
			pemaths::CPeVector3 m_globalPosition;

		public:
			CPeForceFree()
				: CPeForce()
				, m_forceValue(pemaths::CPeVector3(0, 0, 0))
				, m_globalPosition(pemaths::CPeVector3(0, 0, 0))
			{

			}
			/**
			 * @brief Define force by its vectorial values and the point where it
			 * needs to be applied.
			 * 
			 * @param p_forceValue CPeVector3 - Values of the force
			 * @param p_appPoint CPeVector3 - Point where the force must apply
			 */
			void Initialise(pemaths::CPeVector3 p_forceValue, pemaths::CPeVector3 p_appPoint);

			/**
			 * @brief Define force by its direction vector, its magnitude and the point
			 * where it needs to be applied.
			 *
			 * @param p_direction CPeVector3 - Direction of the force. The vector does not need to be normalized.
			 * @param p_magnitude float - Magnitude of the force vector.
			 * @param p_appPoint CPeVector3 - Point where the force must apply.
			 */
			void Initialise(pemaths::CPeVector3 p_direction, float p_magnitude, pemaths::CPeVector3 p_appPoint);

			/**
			 * @brief Compute the force for the targeted particle object.
			 */
			void Compute(CPeParticle* p_particle, double p_timeStep) const;
		};
	}
}

#endif /* PEPHYSICS_CPEFORCEDRAG_H */
