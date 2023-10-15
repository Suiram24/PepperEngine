#ifndef CPEENTITY_CPEENTITY_H
#define CPEENTITY_CPEENTITY_H

#include <vector>

#include "CPeTransform.h"

namespace engine {
	namespace physics {
		class CPeComponent;

		/**
		 * @brief Class for all physics objects
		*/
		class CPeEntity
		{
			//flieds
		public:
			const int m_uuid;//TODO create PeUUID
			CPeTransform m_transform;
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

			CPeEntity(const CPeTransform& p_transform)
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