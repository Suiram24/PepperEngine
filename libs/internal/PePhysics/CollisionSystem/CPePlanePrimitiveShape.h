#ifndef PEPHYSICS_CPEPLANEPRIMITIVESHAPE_H
#define PEPHYSICS_CPEPLANEPRIMITIVESHAPE_H

#include "CPePrimitiveShape.h"

namespace pecore = engine::core;
namespace pemaths = engine::maths;

namespace engine {
	namespace physics {

		class CPePlanePrimitiveShape : public CPePrimitiveShape {
		private:
			pemaths::CPeVector3 m_normal;
			pemaths::CPeVector3 m_offset;

		public:

			CPePlanePrimitiveShape(const pecore::CPeEntity& p_owner, pemaths::CPeVector3 p_normal, pemaths::CPeVector3 p_offset) :
				CPePrimitiveShape(p_owner),
				m_normal(p_normal),
				m_offset(p_offset)
			{
			}

			pemaths::CPeVector3 GetNormal() const;
			pemaths::CPeVector3 GetOffset() const;

			void SetNormal(pemaths::CPeVector3 p_normal);
			void SetOffset(pemaths::CPeVector3 p_offset);

		protected:
			void GotAbstracted();
		};
	}
}

#endif /* PEPHYSICS_CPEPLANEPRIMITIVESHAPE_H */