#ifndef PEENGINECORE_CPEOBJECTPOOL_H
#define PEENGINECORE_CPEOBJECTPOOL_H

#include <array>
#include <stack>
#include <cstdio>

#include "CPePointerSorter.h"
#include "CPeEntity.h"

namespace engine 
{
	namespace core 
	{


		/**
		 * @brief Template Classe for object pools. Made with CPeComponents in mind. Implement Initialise() and SetActive() to use
		*/
		template<class T, const int N>
		class CPeObjectPool
		{

		public:
			//TODO change m_uuid
			CPeObjectPool()
				: m_pool()
			{
				for (auto i = N; i--;)
				{
					m_freeStack.push(&m_pool[i]);
				}
			}

			template<typename ... Args>
			T& Create(Args ... p_params)
			{
				if (!m_freeStack.empty())
				{
					T* newObject = m_freeStack.top();
					newObject->Initialise(p_params...);
					m_freeStack.pop();
					return *newObject;
					
				}
				else
				{
					printf("Error: Object pool full");
					//assert(true, "Object pool full");
				}
			}

			void Release(T* p_ObjectPointer)
			{
				p_ObjectPointer->SetActive(false);
				m_freeStack.push(p_ObjectPointer);
			}

			int Size() const
			{
				return N;
			}

			T* First()
			{
				return &m_pool[0];
			}

		protected:
		private:

		public:
		protected:
		private:
			T m_pool[N];
			
			std::stack<T*> m_freeStack; //ALl free objects, sorted from first to last in memory order

		};
	}
}
#endif /* PEENGINECORE_CPEOBJECTPOOL_H */