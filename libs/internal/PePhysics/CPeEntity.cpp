#include "CPeEntity.h"

namespace engine {
	namespace physics {

		const CPeTransform& CPeEntity::GetTransform() const
		{
			return m_transform;
		}

		/*template<class T>
		T* CPeEntity::GetComponent() const
		{
			for (std::vector<CPeComponent*>::iterator it = m_components.begin(); it != m_components.end(); ++it)
			{
				if (typeid(*it) == typeid(T))
				{
					return it;
				}
			}
			return nullptr;
		}

		template<class T>
		void CPeEntity:: AddComponent(T* p_component)
		{
			m_components.push_back(p_component);
		}*/
	}
}