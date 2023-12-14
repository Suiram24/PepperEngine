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
			/**
			 * @brief Construct a new CPeKDTree.
			 * 
			 * @param p_dimensionAlong EPeDimension - Dimension to start the partitioning along
			 * @param p_objects vector<CPeColliderComponent> - Colliders of objects to consider
			 * @param p_contentSizeMax int - maximal size value to stop the generation of childs
			 */
			CPeKDTree(EPeDimension p_dimensionAlong, std::vector<CPeColliderComponent*>& p_objects, int p_contentSizeMax = 3);

			/**
			 * @brief Get the Possible Collisions listed by the KD tree
			 * 
			 * @return vector<pair<CPeColliderComponent*, CPeColliderComponent*>> pair of colliders representing the possible collisions 
			 */
			std::vector<std::pair<CPeColliderComponent*, CPeColliderComponent*>> GetPossibleCollisions();

			~CPeKDTree();
		private:
			/**
			 * @brief Divide space to create the childs of a KD Tree
			 */
			void divideSpace();

			/**
			 * @brief Get the leaves of the KD-Tree
			 * 
			 * @param p_leaves vector<CPeKDTree*>* - ALl leaves of the KD Tree collected
			 */
			void GetLeaves(std::vector<CPeKDTree*>* p_leaves);

			/**
			 * @brief Get all possible collisions for a specific KD Tree node.
			 * 
			 * @return vector<pair<CPeColliderComponent*, CPeColliderComponent*>> All possible collisions for the targeted node
			 */
			std::vector<std::pair<CPeColliderComponent*, CPeColliderComponent*>> GetNodeCollisions();

			/**
			 * @brief Compute if the sphere collider intersect the KD plane
			 * 
			 * @param p_collider CPeSpherePrimitiveShape& - sphere collider to check
			 * @return true if the collider intersect the KD plane
			 * @return false otherwise
			 */
			bool IntersectKDPlane(const CPeSpherePrimitiveShape& p_collider) const;

			/**
			 * @brief Compute if two global sphere collider intersect
			 *
			 * @param p_collider1 CPeSpherePrimitiveShape & - sphere collider 1
			 * @param p_collider2 CPeSpherePrimitiveShape & - sphere collider 2
			 * @return true if the two colliders intersect
			 * @return false otherwise
			 */
				bool IsBroadIntersection(const CPeSpherePrimitiveShape & p_collider1, const CPeSpherePrimitiveShape& p_collider2) const;
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