#ifndef PEPHYSICS_CPEKDTREE_H
#define PEPHYSICS_CPEKDTREE_H

#include "../../PeEngineCore/PeEngineCore.h"
#include "../CPeParticle.h"
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
		public:
			CPeKDTree* m_leftChild;
			CPeKDTree* m_rightChild;
			std::vector<CPeParticle*> m_content;
			EPeDimension m_divisionDim;
		public:
			CPeKDTree(EPeDimension p_dimensionAlong, std::vector<CPeParticle*> p_objects);

			std::vector<std::pair<CPeParticle*, CPeParticle*>> GetPossibleCollisions();

			~CPeKDTree();
		private:
			void divideSpace();
		};

		class ComparatorX {
		public:
			bool operator()(CPeParticle* p_a, CPeParticle* p_b);
		};

		class ComparatorY {
		public:
			bool operator()(CPeParticle* p_a, CPeParticle* p_b);
		};

		class ComparatorZ {
		public:
			bool operator()(CPeParticle* p_a, CPeParticle* p_b);
		};
	}
}

#endif /* PEPHYSICS_CPEPRIMITIVESHAPE_H */