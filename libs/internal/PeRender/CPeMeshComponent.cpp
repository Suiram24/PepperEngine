#include "CPeMeshComponent.h"

namespace engine {
	namespace render {

		void CPeMeshComponent::UpdateTransformMatrix()
		{
			pemaths::CPeVector3 pos = m_owner->m_transform.GetPosition();
			m_modelWatcher.SetPos(pos.GetX(), pos.GetY(), pos.GetZ());
			m_modelWatcher.SetScale(m_owner->m_transform.GetSize().GetX());
			
		}


	}
}