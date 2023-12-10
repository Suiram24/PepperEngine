#ifndef CPECOLLISIONSYSTEM_CPESHAPE_H
#define CPECOLLISIONSYSTEM_CPESHAPE_H

#include "../../PeMaths/PeMaths.h"

namespace pemaths = engine::maths;

namespace engine {
	namespace physics {

		/**
		 * @brief A parent class for shapes that describes a primitive collider.
		*/
		class CPeShape {
		private:
			pemaths::CPeVector3 m_offset; //Offset of the shape in local coordinate

		public:
			/**
			 * @brief default constructor.
			*/
			CPeShape(pemaths::CPeVector3 p_offset)
				: m_offset(p_offset)
			{
			}

			pemaths::CPeVector3 GetOffset() const;

		}
	}
}

#endif /* CPECOLLISIONSYSTEM_CPESHAPE_H */