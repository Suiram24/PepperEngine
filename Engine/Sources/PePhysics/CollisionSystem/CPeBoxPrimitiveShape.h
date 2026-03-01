#ifndef PEPHYSICS_CPEBOXPRIMITIVE_H
#define PEPHYSICS_CPEBOXPRIMITIVE_H

#include "CPePrimitiveShape.h"

namespace pecore = engine::core;
namespace pemaths = engine::maths;

namespace engine {
	namespace physics {

		class CPeBoxPrimitiveShape : public CPePrimitiveShape {
		private:
			pemaths::CPeVector3 m_halfsize;

		public:

			CPeBoxPrimitiveShape(const pecore::CPeEntity& p_owner, pemaths::CPeVector3 p_halfsize) :
				CPePrimitiveShape(p_owner),
				m_halfsize(p_halfsize)
			{
			}

			pemaths::CPeVector3 GetHalfSize() const;

			void SetHalfSize(pemaths::CPeVector3 p_halfsize);

			EShapeTypes GetType() const;
		protected:
		};
	}
}

#endif /* PEPHYSICS_CPEBOXPRIMITIVE_H */