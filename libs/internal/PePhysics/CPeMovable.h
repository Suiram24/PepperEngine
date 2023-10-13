#ifndef CPEMOVABLE_PEPHYSICS_H
#define PEPHYSICS_PEPHYSICS_H

#include "CPeTransform.h"

namespace engine {
	namespace physics {
		/**
		 * @brief Interface for movable objects
		*/
		class CPeMovable {
			//Fields
		protected:
			CPeTransform m_transform;

			//Methods
		public:
			CPeMovable(const CPeTransform& p_transform) : m_transform(p_transform)
			{
			}

			/**
			 * @brief Accessor for m_transform.
			 * @return m_transform.
			*/
			const CPeTransform& GetTransform() const;
		};
	}
}
#endif /* PEPHYSICS_PEPHYSICS_H */