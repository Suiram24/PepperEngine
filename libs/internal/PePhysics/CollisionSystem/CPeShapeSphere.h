#ifndef CPECOLLISIONSYSTEM_CPESHAPESPHERE_H
#define CPECOLLISIONSYSTEM_CPESHAPESPHERE_H

#include "CPeShape.h"

namespace pemaths = engine::maths;

namespace engine {
	namespace physics {

		/**
		 * @brief A parent class for shapes that describes a primitive collider.
		*/
		class CPeShapeSphere: public CPeShape {
		private:
			double m_radius; //Offset of the shape in local coordinate

		public:
			/**
			 * @brief default constructor.
			*/
			CPeShapeSphere(double p_radius, pemaths::CPeVector3 p_offset = pemaths::CPeVector3())
				: CPeShape(p_offset)
				, m_radius(p_radius)
			{
			}

			double GetRadius() const;
		}
	}
}

#endif /* CPECOLLISIONSYSTEM_CPESHAPESPHERE_H */