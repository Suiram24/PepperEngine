#ifndef CPECOMPONENT_CPECOMPONENT_H
#define CPECOMPONENT_CPECOMPONENT_H

#include <string>
#include <cstdio>
#include "CPeEntity.h"

namespace engine {
	namespace core {

		/**
		 * @brief Interface for all physics objects component
		*/
		class CPeComponent
		{
			//flieds
		protected:
			CPeEntity& m_owner;
			bool m_isActive;

		public:
			//Methods
			CPeComponent(CPeEntity& p_owner)
				: m_owner(p_owner)
				, m_isActive(true)
			{
				p_owner.AddComponent(this);
			}

			void SetActive(bool p_active);

			CPeEntity& GetOwner();

		};

	}
}
#endif /* CPECOMPONENT_CPECOMPONENT_H */