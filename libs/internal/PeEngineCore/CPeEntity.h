#ifndef CPEENTITY_CPEENTITY_H
#define CPEENTITY_CPEENTITY_H

#include <vector>
#include "..\PeMaths\PeMaths.h"

namespace engine {
	namespace core {
		class CPeComponent;
		namespace pemaths = engine::maths;
		/**
		 * @brief Class for all physics objects
		*/
		class CPeEntity
		{
			//flieds
		public:
			const int m_uuid;//TODO create PeUUID
			pemaths::CPeTransform m_transform;
		private:
			std::vector<CPeComponent*> m_components;
		protected:

			//Methods
		public:
			//TODO change m_uuid
			CPeEntity()
				: m_uuid(0)
				, m_transform()
				, m_components()
			{
			}

			CPeEntity(const pemaths::CPeTransform& p_transform)
				: m_uuid(0)
				, m_transform(p_transform)
				, m_components()
			{
			}

			//template<class T>
			//T* GetComponent<T>() const;


			void AddComponent(CPeComponent* p_component);

		};
	}
}
#endif /* CPEENTITY_CPEENTITY_H */