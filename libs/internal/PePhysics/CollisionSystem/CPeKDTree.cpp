#include "CPePrimitiveShape.h"
#include "CPeKDTree.h"

#include <algorithm>
#include <cmath>

namespace engine {
	namespace physics {
		CPeKDTree::CPeKDTree(EPeDimension p_dimensionAlong, std::vector<CPeColliderComponent*> p_objects, int p_contentSizeMax):
			m_leftChild(nullptr),
			m_rightChild(nullptr),
			m_content(p_objects),
			m_divisionDim(p_dimensionAlong),
			m_contenSizeMax(p_contentSizeMax)
		{
			divideSpace();
		}

		std::vector<std::pair<CPeColliderComponent*, CPeColliderComponent*>> CPeKDTree::GetPossibleCollisions()
		{
			std::vector<CPeKDTree*> leaves;
			std::vector<std::pair<CPeColliderComponent*, CPeColliderComponent*>> possibleCollisions;
			std::vector<std::pair<CPeColliderComponent*, CPeColliderComponent*>> currentCollisions;
			GetLeaves(&leaves);

			for (int i = 0; i < leaves.size(); ++i) {
				currentCollisions = leaves[i]->GetNodeCollisions();
				possibleCollisions.insert(
					possibleCollisions.end(),
					currentCollisions.begin(),
					currentCollisions.end()
				);
			}

			return possibleCollisions;
		}
		CPeKDTree::~CPeKDTree()
		{
			if (m_leftChild != nullptr) {
				delete m_leftChild;
			}
			if (m_rightChild != nullptr) {
				delete m_rightChild;
			}
		}

		void engine::physics::CPeKDTree::divideSpace()
		{
			if (m_content.size() > m_contenSizeMax) {
				switch (m_divisionDim) {
				case X:
					std::sort(
						m_content.begin(),
						m_content.end(),
						ComparatorX::operator()
					);
					break;
				case Y:
					std::sort(
						m_content.begin(),
						m_content.end(),
						ComparatorY::operator()
					);
					break;
				case Z:
					std::sort(
						m_content.begin(),
						m_content.end(),
						ComparatorZ::operator()
					);
					break;
				}
				int medianIndex = std::floor(m_content.size() / 2);

				// TODO : inspect if the objects are correctly detected even if they are really near
				//		  from each other.

				auto firstLeft = m_content.begin();
				auto lastLeft = m_content.begin() + medianIndex;

				auto firstRight = m_content.begin() + medianIndex;
				auto lastRight = m_content.end();

				// FOR loop sur liste de gauche pour vérifier ceux qui sont aussi à droite
				// TDOD
				// FOR loop sur liste de droite pour vérifier ceuxi qui sont auss à gauche
				// TODO

				EPeDimension newDim = static_cast<EPeDimension>((static_cast<int>(m_divisionDim) + 1) % 3);

				m_leftChild = new CPeKDTree(newDim, std::vector<CPeColliderComponent*>(firstLeft, lastLeft));
				m_rightChild = new CPeKDTree(newDim, std::vector<CPeColliderComponent*>(firstRight, lastRight));
			}


		}

		void CPeKDTree::GetLeaves(std::vector<CPeKDTree*>* p_leaves)
		{
			if (this != nullptr) {
				if (m_leftChild == nullptr && m_rightChild == nullptr) {
					p_leaves->push_back(this);
				}
				else {
					this->m_leftChild->GetLeaves(p_leaves);
					this->m_rightChild->GetLeaves(p_leaves);
				}
			}
		}

		std::vector<std::pair<CPeColliderComponent*, CPeColliderComponent*>> CPeKDTree::GetNodeCollisions() {
			std::vector<std::pair<CPeColliderComponent*, CPeColliderComponent*>> pairs;
			for (int i = 0; i < m_content.size(); ++i) {
				for (int j = 0; j < m_content.size(); ++j) {
					if (i != j) {
						pairs.push_back(
							std::pair<CPeColliderComponent*, CPeColliderComponent*>(m_content[i], m_content[j])
						);
					}
				}
			}
		}


		bool ComparatorX::operator()(CPeColliderComponent* p_a, CPeColliderComponent* p_b)
		{
			return p_a->GetOwner().m_transform.GetPosition().GetX() < p_b->GetOwner().m_transform.GetPosition().GetX();
		}
		bool ComparatorY::operator()(CPeColliderComponent* p_a, CPeColliderComponent* p_b)
		{
			return p_a->GetOwner().m_transform.GetPosition().GetY() < p_b->GetOwner().m_transform.GetPosition().GetY();;
		}
		bool ComparatorZ::operator()(CPeColliderComponent* p_a, CPeColliderComponent* p_b)
		{
			return p_a->GetOwner().m_transform.GetPosition().GetZ() < p_b->GetOwner().m_transform.GetPosition().GetZ();;
		}
	}
}