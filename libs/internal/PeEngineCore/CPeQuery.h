#pragma once
#include <functional>
#include <unordered_set>

#include "CPeWorld.h"
#include "PeECSDefinitions.h"

namespace engine
{
	namespace core
	{
		template<PeComponentStruct...Args>
		class CPeQuery
		{
			friend class CPeWorld;
		public:
			CPeQuery()
				: m_owner()
			{

			}

			void operator=(const CPeQuery<Args...>& other)
			{
				m_owner = other.m_owner;
			}

			void operator=(const CPeBuiltQuery<Args...> & other)
			{
				m_owner = static_cast<CPeWorld*>(other.m_world);
			}

			void ForEach(std::function<void(Args&...p_params)>& p_function) const
			{
				assert(m_owner && "The query hasn't been build before ForEach is called !");
				m_owner->ForEach(m_queryID, p_function);
			}

			
		protected:
			CPeQuery(const CPeWorld* p_owner)
				: m_owner(p_owner)
			{

			}
		private:

			static constexpr int computeHash()
			{
				return (Args::CompId()^...^0);
			}

		public:
		protected:
		private:

			static constexpr int m_queryID = computeHash();
			const CPeWorld* m_owner;

			
		};


	}
}


