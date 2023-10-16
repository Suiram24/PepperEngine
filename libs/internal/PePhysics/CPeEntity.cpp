#include "CPeEntity.h"

namespace engine {
	namespace physics {

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
		

		void CPeEntity:: AddComponent(CPeComponent* p_component)
		{
			m_components.push_back(p_component);
		}
	}
}