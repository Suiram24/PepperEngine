#ifndef PEPHYSICS_CPEKDTREE_H
#define PEPHYSICS_CPEKDTREE_H

#include "../../PeEngineCore/PeEngineCore.h"
#include "../CPeParticle.h"
#include "CPeColliderComponent.h"
#include "CPeSpherePrimitiveShape.h"
#include <utility>

namespace pecore = engine::core;
namespace pemaths = engine::maths;

namespace engine {
	namespace physics {

		enum EPeDimension{
			X = 0,
			Y = 1,
			Z = 2
		};

		/**
		 * @brief A class for objects that perform collisions.
		*/
		class CPeKDTree {
		private:
			CPeKDTree* m_leftChild;
			CPeKDTree* m_rightChild;
			std::vector<CPeColliderComponent*> m_content;
			EPeDimension m_divisionDim;
			double m_value;
			int m_contenSizeMax;
		public:
		public:
			CPeKDTree(EPeDimension p_dimensionAlong, std::vector<CPeColliderComponent*> p_objects, int p_contentSizeMax = 3);

			std::vector<std::pair<CPeColliderComponent*, CPeColliderComponent*>> GetPossibleCollisions();

			~CPeKDTree();
		private:
			void divideSpace();

			void GetLeaves(std::vector<CPeKDTree*>* p_leaves);

			std::vector<std::pair<CPeColliderComponent*, CPeColliderComponent*>> GetNodeCollisions();

			bool IntersectKDPlane(const CPeSpherePrimitiveShape& p_collider) const;
		};

		class ComparatorX {
		public:
			bool operator()(CPeColliderComponent* p_a, CPeColliderComponent* p_b);
		};

		class ComparatorY {
		public:
			bool operator()(CPeColliderComponent* p_a, CPeColliderComponent* p_b);
		};

		class ComparatorZ {
		public:
			bool operator()(CPeColliderComponent* p_a, CPeColliderComponent* p_b);
		};
	}
}

#endif /* PEPHYSICS_CPEPRIMITIVESHAPE_H */