#include "CPeMeshComponent.h"

namespace engine {
	namespace render {

		void CPeMeshComponent::UpdateTransformMatrix()
		{	
			pemaths::CPeMatrix4 peTMatrix = m_owner->m_transform.GetTransformMatrix();

			glm::mat4 glmTMatrix = glm::mat4(
				peTMatrix.Get(0, 0), peTMatrix.Get(1, 0), peTMatrix.Get(2, 0), 0,
				peTMatrix.Get(0, 1), peTMatrix.Get(1, 1), peTMatrix.Get(2, 1), 0,
				peTMatrix.Get(0, 2), peTMatrix.Get(1, 2), peTMatrix.Get(2, 2), 0,
				peTMatrix.Get(0, 3), peTMatrix.Get(1, 3), peTMatrix.Get(2, 3), 1
			);
			
			m_modelWatcher.SetTransformMatrix(glmTMatrix);
			
		}


	}
}