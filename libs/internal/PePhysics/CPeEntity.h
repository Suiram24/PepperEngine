#ifndef CPEENTITY_CPEENTITY_H
#define CPEENTITY_CPEENTITY_H

#include <vector>

#include "CPeComponent.h"
#include "CPeTransform.h"

namespace engine {
	namespace physics {

		/**
		 * @brief Class for all physics objects
		*/
		class CPeEntity
		{
			//flieds
		public:
			const int m_uuid;//TODO create PeUUID
		private:
			std::vector<CPeComponent*> m_components;
		protected:
			CPeTransform m_transform;

			//Methods
		public:
			//TODO change m_uuid
			CPeEntity():m_uuid(0), m_transform(CPeTransform()), m_components(std::vector<CPeComponent*>())
			{
			}

			/**
			 * @brief Accessor for m_transform.
			 * @return m_transform.
			*/
			const CPeTransform& GetTransform() const;

			/*template<class T>
			T* GetComponent() const;


			template<class T>
			void AddComponent(T* p_component);*/

		};
	}
}
#endif /* CPEENTITY_CPEENTITY_H */