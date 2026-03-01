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
			double m_offset;

		public:

			CPePlanePrimitiveShape(const pecore::CPeEntity& p_owner, pemaths::CPeVector3 p_normal, double p_offset) :
				CPePrimitiveShape(p_owner),
				m_normal(p_normal),
				m_offset(p_offset)
			{
			}

			pemaths::CPeVector3 GetNormal() const;
			double GetOffset() const;

			void SetNormal(pemaths::CPeVector3 p_normal);
			void SetOffset(double p_offset);

			EShapeTypes GetType() const;
		protected:
		};
	}
}

#endif /* PEPHYSICS_CPEPLANEPRIMITIVESHAPE_H */