#ifndef CPEENTITY_CPEENTITY_H
#define CPEENTITY_CPEENTITY_H

#include <vector>
#include "..\PeMaths\PeMaths.h"

namespace engine {
	namespace core {

		namespace consts
		{
			const int maxEntityNumber = 100;
			const int maxComponentsPerEntity = 5;
		}

		class CPeComponent;

		struct SPeComponentSlot
		{
			CPeComponent* m_component = nullptr;
			bool isValid = false;
		};


		
		namespace pemaths = engine::maths;
		/**
		 * @brief Class for all physics objects
		*/
		class CPeEntity
		{
			//flieds
		public:
			int m_uuid;//TODO create PeUUID
			pemaths::CPeTransform m_transform;
		private:
			SPeComponentSlot m_components[consts::maxComponentsPerEntity];
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

			void Initialise(const pemaths::CPeTransform& p_transform);
			bool IsActive();

			template<class T>
			T* GetComponent() const
			{
				for (size_t i =0; i < consts::maxComponentsPerEntity; i++)
				{
					T* pointer = dynamic_cast<T*>(m_components[i].m_component);
					if (pointer != nullptr)
					{
						return pointer;
					}
				}
				return nullptr;
			}


			void AddComponent(CPeComponent* p_component);


		};
	}
}
#endif /* CPEENTITY_CPEENTITY_H */