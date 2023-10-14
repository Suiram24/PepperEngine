#ifndef CPECOMPONENT_CPECOMPONENT_H
#define CPECOMPONENT_CPECOMPONENT_H

#include <string>
#include <cstdio>

namespace engine {
	namespace physics {

		class CPeEntity;

		/**
		 * @brief Interface for all physics objects component
		*/
		class CPeComponent
		{
			//flieds
		private:
			const CPeEntity* m_owner;
			bool m_isActive;

		public:
			//Methods
			CPeComponent(const CPeEntity* p_owner) : m_owner(p_owner), m_isActive(true)
			{
			}

			void SetActive(bool p_active);

			const CPeEntity* GetOwner() const;

		};

	}
}
#endif /* CPECOMPONENT_CPECOMPONENT_H */