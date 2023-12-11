#ifndef PEPHYSICS_CPESPHEREPRIMITIVE_H
#define PEPHYSICS_CPESPHEREPRIMITIVE_H

#include "CPePrimitiveShape.h"

namespace pecore = engine::core;
namespace pemaths = engine::maths;

namespace engine {
	namespace physics {

		class CPeSpherePrimitiveShape : public CPePrimitiveShape {
		private:
			double m_radius;

		public:

			CPeSpherePrimitiveShape(const pecore::CPeEntity& p_owner,double p_radius):
				CPePrimitiveShape(p_owner),
				m_radius(p_radius)
			{
			}

			double GetRadius() const;
			void SetRadius(double p_radius);

		protected:
			void GotAbstracted();
		};
	}
}

#endif /* PEPHYSICS_CPESPHEREPRIMITIVE_H */