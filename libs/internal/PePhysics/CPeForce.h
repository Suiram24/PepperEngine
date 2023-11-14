#ifndef CPeForce_CPeForce_H
#define CPeForce_CPeForce_H

#include "../PeMaths/PeMaths.h"
#include "CPeParticle.h"
#include "CPeRigidBody.h"

namespace pemaths = engine::maths;

namespace engine {
	namespace physics {

		//class CPeParticle;//forward declaration to avoid circular dependency.
		
		/**
		 * @brief A class for Newton's Physics forces.
		*/
		class CPeForce {


			//Methods
		public:
			CPeForce()
				: m_isActive(false)
			{

			}

			void Release();
			bool IsActive() const;

			virtual void Compute(CPeParticle& p_particule, double p_timeStep) const = 0;
		protected:
		private:



		public:
		protected:
			bool m_isActive;
		private:

			

		};
	}
}

#endif /* CPeForce_CPeForce_H */