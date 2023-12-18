#ifndef PEPHYSICS_CPEPRIMITIVESHAPE_H
#define PEPHYSICS_CPEPRIMITIVESHAPE_H

#include "../../PeEngineCore/PeEngineCore.h"
#include "../CPeRigidBody.h"

namespace pecore = engine::core;
namespace pemaths = engine::maths;

namespace engine {
	namespace physics {
		enum EShapeTypes
		{
			SPHERE, BOX, PLANE
		};

		/**
		 * @brief A class for primitive shapes of objects that perform collisions.
		*/
		class CPePrimitiveShape {
		protected:
			pemaths::CPeTransform m_shapeTransform;
			pemaths::CPeMatrix4 m_ownerTransformMat;
			pemaths::CPeVector3 m_worldPosition;

			const pecore::CPeEntity& m_owner;

		public:

			CPePrimitiveShape(const pecore::CPeEntity& p_owner):
				m_owner(p_owner)
			{
			}

			pemaths::CPeMatrix4 GetWorldTransform() const;

			const pemaths::CPeVector3& GetWorldPosition();

			pemaths::CPeVector3 ConvertWorldToLocal(const pemaths::CPeVector3& p_worldCoordinates) const;

			pemaths::CPeVector3 ConvertLocalToWorld(const pemaths::CPeVector3& p_localCoordinates) const;

			const pecore::CPeEntity& GetOwningEntity() const;

			
			virtual EShapeTypes GetType() const = 0;
		protected:

			CPeRigidBody* GetRigidbody() const; //deprecated
		};
	}
}
#endif /* PEPHYSICS_CPEPRIMITIVESHAPE_H */