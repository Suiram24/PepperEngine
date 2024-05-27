#include "CPePrimitiveShape.h"
#include "CPeKDTree.h"

#include <algorithm>
#include <set>
#include <cmath>

namespace engine {
	namespace physics {
		CPeKDTree::CPeKDTree(EPeDimension p_dimensionAlong, std::vector<ColliderInfos*>& p_objects, int p_contentSizeMax):
			m_leftChild(nullptr),
			m_rightChild(nullptr),
			m_content(p_objects),
			m_divisionDim(p_dimensionAlong),
			m_contenSizeMax(p_contentSizeMax),
			m_value(0.0F)
		{
			divideSpace();
		}

		std::vector<std::pair<ColliderInfos*, ColliderInfos*>> CPeKDTree::GetPossibleCollisions()
		{
			std::vector<CPeKDTree*> leaves;
			std::vector<std::pair<ColliderInfos*, ColliderInfos*>> possibleCollisions;
			std::vector<std::pair<ColliderInfos*, ColliderInfos*>> currentCollisions;
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
					m_value = m_content[medianIndex]->position.GetX();
					break;
				case Y:
					m_value = m_content[medianIndex]->position.GetY();
					break;
				case Z:
					m_value = m_content[medianIndex]->position.GetZ();
					break;
				}

				auto firstLeft = m_content.begin();
				auto lastLeft = m_content.begin() + medianIndex;
				std::vector<ColliderInfos*> leftVector(firstLeft, lastLeft);

				auto firstRight = m_content.begin() + medianIndex;
				auto lastRight = m_content.end();
				std::vector<ColliderInfos*> rightVector(firstRight, lastRight);

				// FOR loop on the left list to verify if they're also in the right part.
				std::vector<ColliderInfos*> toAddRight;
				for (auto i = firstLeft; i != lastLeft; ++i) {
					if (IntersectKDPlane(*i)) {
						toAddRight.push_back(*i);
					}
				}

				// FOR loop on the right list to verify if they're also in the left part.
				std::vector<ColliderInfos*> toAddLeft;
				for (auto& i = firstRight; i != lastRight; ++i) {
					if (IntersectKDPlane(*i)) {
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
		std::vector<std::pair<ColliderInfos*, ColliderInfos*>> CPeKDTree::GetNodeCollisions()
		{
			std::set<std::pair<ColliderInfos*, ColliderInfos*>> pairs;
			for (int i = 0; i < m_content.size()-1; ++i) {
				for (int j = i+1; j < m_content.size(); ++j) {
					if (IsBroadIntersection(m_content[i], m_content[j])) {
						pairs.insert(
							std::pair<ColliderInfos*, ColliderInfos*>(m_content[i], m_content[j])
						);
					}
				}
			}
			std::vector<std::pair<ColliderInfos*, ColliderInfos*>> pairsVec(pairs.begin(), pairs.end());
			return pairsVec;
		}
		/*
		*/

		/*
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
		*/

		bool CPeKDTree::IntersectKDPlane(ColliderInfos* p_collider) const {
			double distCenterPlane = 0.0f;
			double radius = p_collider->radius;
			switch (m_divisionDim) {
			case X:
				distCenterPlane = std::abs(p_collider->position.GetX() - m_value);
				break;
			case Y:
				distCenterPlane = std::abs(p_collider->position.GetY() - m_value);
				break;
			case Z:
				distCenterPlane = std::abs(p_collider->position.GetZ() - m_value);
				break;
			}
			if (distCenterPlane <= radius) {
				return true;
			}
			return false;
		}

		bool CPeKDTree::IsBroadIntersection(ColliderInfos* p_collider1, ColliderInfos* p_collider2) const {
			double radius1 = p_collider1->radius;
			double radius2 = p_collider2->radius;

			double sqSumRadius = (radius1 + radius2) * (radius1 + radius2);

			double sqDist = (p_collider1->position - p_collider2->position).GetSquaredNorm();

			if (sqDist <= sqSumRadius) return true;
			return false;
		}


		bool ComparatorX::operator()(ColliderInfos* p_a, ColliderInfos* p_b)
		{
			return p_a->position.GetX() < p_b->position.GetX();
		}
		bool ComparatorY::operator()(ColliderInfos* p_a, ColliderInfos* p_b)
		{
			return p_a->position.GetY() < p_b->position.GetY();;
		}
		bool ComparatorZ::operator()(ColliderInfos* p_a, ColliderInfos* p_b)
		{
			return p_a->position.GetZ() < p_b->position.GetZ();;
		}
	}
}