#ifndef PEPHYSICS_CPEPRIMITIVESHAPE_H
#define PEPHYSICS_CPEPRIMITIVESHAPE_H

#include "../../PeEngineCore/PeEngineCore.h"

namespace pecore = engine::core;
namespace pemaths = engine::maths;

namespace engine {
	namespace physics {

		/**
		 * @brief A class for objects that perform collisions.
		*/
		class CPePrimitiveShape {
		private:
			pemaths::CPeTransform m_shapeTransform;

			pecore::CPeEntity& m_owner;

		public:

			/**
			 * @brief default constructor, shouldn't be used outside of CPeObjectPool. 
			*/
			CPePrimitiveShape()
			{
			}

			pemaths::CPeMatrix4 GetWorldTransform();

			pemaths::CPeVector3 GetWorldPosition();

		protected:
			virtual void GotAbstracted() = 0;
		};
	}
}

#endif /* PEPHYSICS_CPEPRIMITIVESHAPE_H */