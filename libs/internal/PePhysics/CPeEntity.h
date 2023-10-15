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
			CPeEntity():m_uuid(0), m_transform(CPeTransform()), m_components(std::vector<CPeComponent*>())
			{
			}

			/*template<class T>
			T* GetComponent() const;


			template<class T>
			void AddComponent(T* p_component);*/

		};
	}
}
#endif /* CPEENTITY_CPEENTITY_H */