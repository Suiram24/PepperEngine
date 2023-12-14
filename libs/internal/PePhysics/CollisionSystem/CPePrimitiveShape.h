#ifndef PEPHYSICS_CPEPRIMITIVESHAPE_H
#define PEPHYSICS_CPEPRIMITIVESHAPE_H

#include "../../PeEngineCore/PeEngineCore.h"
#include "../CPeRigidBody.h"

namespace pecore = engine::core;
namespace pemaths = engine::maths;

namespace engine {
	namespace physics {
		/**
		 * @brief A class for primitive shapes of objects that perform collisions.
		*/
		class CPePrimitiveShape {
		protected:
			pemaths::CPeTransform m_shapeTransform;

			pecore::CPeEntity& m_owner;

		public:

			CPePrimitiveShape(pecore::CPeEntity& p_owner):
				m_owner(p_owner)
			{
			}

			pemaths::CPeMatrix4 GetWorldTransform() const;

			pemaths::CPeVector3 GetWorldPosition() const;

			pecore::CPeEntity& GetOwningEntity() const;

			
		protected:
			virtual void GotAbstracted() = 0;

			CPeRigidBody* GetRigidbody() const; //deprecated
		};
	}
}
#endif /* PEPHYSICS_CPEPRIMITIVESHAPE_H */