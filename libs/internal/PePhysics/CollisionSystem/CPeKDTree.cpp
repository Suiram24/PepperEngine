#include "CPePrimitiveShape.h"
#include "CPeKDTree.h"

#include <algorithm>
#include <cmath>

namespace engine {
	namespace physics {
		CPeKDTree::CPeKDTree(EPeDimension p_dimensionAlong, std::vector<CPeParticle*> p_objects)
		{
			m_divisionDim = p_dimensionAlong;
			m_content = p_objects;
			m_leftChild = nullptr;
			m_rightChild = nullptr;
			divideSpace();
		}
		std::vector<std::pair<CPeParticle*, CPeParticle*>> CPeKDTree::GetPossibleCollisions()
		{
			return std::vector<std::pair<CPeParticle*, CPeParticle*>>();
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
			if (m_content.size() > 1) {
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

				EPeDimension newDim = static_cast<EPeDimension>((static_cast<int>(m_divisionDim) + 1) % 3);

				m_leftChild = new CPeKDTree(newDim, std::vector<CPeParticle*>(firstLeft, lastLeft));
				m_rightChild = new CPeKDTree(newDim, std::vector<CPeParticle*>(firstRight, lastRight));
			}


		}

		bool ComparatorX::operator()(CPeParticle* p_a, CPeParticle* p_b)
		{
			return p_a->GetTransform().GetPosition().GetX() < p_b->GetTransform().GetPosition().GetX();
		}
		bool ComparatorY::operator()(CPeParticle* p_a, CPeParticle* p_b)
		{
			return p_a->GetTransform().GetPosition().GetY() < p_b->GetTransform().GetPosition().GetY();;
		}
		bool ComparatorZ::operator()(CPeParticle* p_a, CPeParticle* p_b)
		{
			return p_a->GetTransform().GetPosition().GetZ() < p_b->GetTransform().GetPosition().GetZ();;
		}
	}
}