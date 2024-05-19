#ifndef CPEENTITY_CPEENTITY_H
#define CPEENTITY_CPEENTITY_H

#include <vector>
#include "..\PeMaths\PeMaths.h"

namespace engine {
	namespace core {

		namespace consts
		{
			const int maxEntityNumber = 200;
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
		 * @brief Class for all entities in the level. An entitie is defined by its compnents
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

			/**
			 * @brief Return the first component of class T.
			 * Usage: entity.GetComponent<T>();
			 * @return Pointer to the component if found, nullptr otherwise
			*/
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

			/**
			 * @brief Attach a component as a child of this entity.
			 * Warning: this function does not set the entity as the owner of the component. It is made to be called from the component when it is initialized.
			*/
			void AddComponent(CPeComponent* p_component);
			//TODO: Make this private/protected and add CPeComponent in friend class ?

		};
	}
}
#endif /* CPEENTITY_CPEENTITY_H */