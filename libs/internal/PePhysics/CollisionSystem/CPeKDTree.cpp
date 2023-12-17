#include "CPePrimitiveShape.h"
#include "CPeKDTree.h"

#include <algorithm>
#include <cmath>

namespace engine {
	namespace physics {
		CPeKDTree::CPeKDTree(EPeDimension p_dimensionAlong, std::vector<CPeColliderComponent*>& p_objects, int p_contentSizeMax):
			m_leftChild(nullptr),
			m_rightChild(nullptr),
			m_content(p_objects),
			m_divisionDim(p_dimensionAlong),
			m_contenSizeMax(p_contentSizeMax),
			m_value(0.0F)
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
			ComparatorX compX;
			ComparatorY compY;
			ComparatorZ compZ;
			if (m_content.size() > m_contenSizeMax) {
				switch (m_divisionDim) {
				case X:
					std::sort(
						m_content.begin(),
						m_content.end(),
						compX
					);
					break;
				case Y:
					std::sort(
						m_content.begin(),
						m_content.end(),
						compY
					);
					break;
				case Z:
					std::sort(
						m_content.begin(),
						m_content.end(),
						compZ
					);
					break;
				}
				int medianIndex = std::floor(m_content.size() / 2);

				// TODO : inspect if the objects are correctly detected even if they are really near
				//		  from each other.

				switch (m_divisionDim) {
				case X:
					m_value = m_content[medianIndex]->GetOwner().m_transform.GetPosition().GetX();
					break;
				case Y:
					m_value = m_content[medianIndex]->GetOwner().m_transform.GetPosition().GetY();
					break;
				case Z:
					m_value = m_content[medianIndex]->GetOwner().m_transform.GetPosition().GetZ();
					break;
				}

				auto firstLeft = m_content.begin();
				auto lastLeft = m_content.begin() + medianIndex;
				std::vector<CPeColliderComponent*> leftVector(firstLeft, lastLeft);

				auto firstRight = m_content.begin() + medianIndex;
				auto lastRight = m_content.end();
				std::vector<CPeColliderComponent*> rightVector(firstRight, lastRight);

				// FOR loop on the left list to verify if they're also in the right part.
				std::vector<CPeColliderComponent*> toAddRight;
				for (auto i = firstLeft; i != lastLeft; ++i) {
					if (IntersectKDPlane((*i)->GetGlobalVolume())) {
						toAddRight.push_back(*i);
					}
				}

				// FOR loop on the right list to verify if they're also in the left part.
				std::vector<CPeColliderComponent*> toAddLeft;
				for (auto& i = firstRight; i != lastRight; ++i) {
					if (IntersectKDPlane((*i)->GetGlobalVolume())) {
						toAddLeft.push_back(*i);
					}
				}
				
				if (!toAddRight.empty()) {
					rightVector.insert(rightVector.end(), toAddRight.begin(), toAddRight.end());
				}
				if (!toAddLeft.empty()) {
					leftVector.insert(leftVector.end(), toAddLeft.begin(), toAddLeft.end());
				}

				if (rightVector.size() != m_content.size() && leftVector.size() != m_content.size()) {
					EPeDimension newDim = static_cast<EPeDimension>((static_cast<int>(m_divisionDim) + 1) % 3);

					m_leftChild = new CPeKDTree(newDim, leftVector);
					m_rightChild = new CPeKDTree(newDim, rightVector);
				}
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
			for (int i = 0; i < m_content.size()-1; ++i) {
				for (int j = i+1; j < m_content.size(); ++j) {
					if (IsBroadIntersection(m_content[i]->GetGlobalVolume(), m_content[j]->GetGlobalVolume())) {
						pairs.push_back(
							std::pair<CPeColliderComponent*, CPeColliderComponent*>(m_content[i], m_content[j])
						);
					}
				}
			}
			return pairs;
		}

		bool CPeKDTree::IntersectKDPlane(const CPeSpherePrimitiveShape& p_collider) const {
			double distCenterPlane = 0.0f;
			double radius = p_collider.GetRadius();
			switch (m_divisionDim) {
			case X:
				distCenterPlane = std::abs(p_collider.GetWorldPosition().GetX() - m_value);
				break;
			case Y:
				distCenterPlane = std::abs(p_collider.GetWorldPosition().GetY() - m_value);
				break;
			case Z:
				distCenterPlane = std::abs(p_collider.GetWorldPosition().GetZ() - m_value);
				break;
			}
			if (distCenterPlane <= radius) {
				return true;
			}
			return false;
		}

		bool CPeKDTree::IsBroadIntersection(const CPeSpherePrimitiveShape& p_collider1, const CPeSpherePrimitiveShape& p_collider2) const {
			double radius1 = p_collider1.GetRadius();
			double radius2 = p_collider2.GetRadius();

			double sqSumRadius = (radius1 + radius2) * (radius1 + radius2);

			double sqDist = (p_collider1.GetWorldPosition() - p_collider2.GetWorldPosition()).GetSquaredNorm();

			if (sqDist <= sqSumRadius) return true;
			return false;
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