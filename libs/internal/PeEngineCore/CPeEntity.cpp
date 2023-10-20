#include "CPeEntity.h"

namespace engine {
	namespace core {

		//template<class T>
		//T* CPeEntity::GetComponent<T>() const
		//{
		//	for (std::vector<CPeComponent*>::iterator it = m_components.begin(); it != m_components.end(); ++it)
		//	{
		//		if (typeid(*it) == typeid(T))
		//		{
		//			return it;
		//		}
		//	}
		//	return nullptr;
		//}
		

		void CPeEntity::AddComponent(CPeComponent* p_component)
		{
			for (size_t i = 0; i < consts::maxComponentsPerEntity; i++)
			{
				if (!m_components[i].isValid)
				{
					m_components[i].m_component = p_component;
					m_components[i].isValid = true;
					return;
				}
			}

			printf("Error: no component slot left on this entity");
			
		}
	}
}