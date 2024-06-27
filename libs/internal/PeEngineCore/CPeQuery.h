#pragma once
#include <functional>
#include <unordered_set>

#include "PeECSDefinitions.h"

namespace engine
{
	namespace core
	{
		class CPeWorld;

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

		template<PeComponentStruct...Args>
		class CPeQueryInternal
		{
			friend class CPeWorld;

		public:

			/**
				* @brief Default constructor
			*/
			CPeQueryInternal()
			{
			}

			void ForEach(std::function<void (Args&...p_params)>& p_function) const
			{
				for (auto archetype : m_archetypes)
				{

					for (int i = 0; i < m_componentsDataMap[0]->at(archetype).Count(); ++i)
					{
						int j = sizeof...(Args);
						p_function(*(m_componentsDataMap[--j]->at(archetype).GetEntityData<Args>(i))...);
					}
					
				}
			}


			
		protected:
			void UpdateComponentsDataMap(std::unordered_map<PeComponentID, ComponentDataMap, ComponentIDHash>& p_ComponentArchetypesMap)
			{
				int i = 0;
				([&]
					{
						m_componentsDataMap[i] = &(p_ComponentArchetypesMap.at(Args::CompId()));
					}(),...);
			}

			void UpdateArchetypeList(
				const std::unordered_set<PeComponentID>& p_newArchetypeComponents,
				PeArchetypeID p_oldArchetype,
				PeArchetypeID p_NewArchetype,
				bool p_changeIsRemove = false)
			{
				//
				// Look for a fast an easy solution
				if (!p_changeIsRemove) //If we are adding a commponent to an archetype
				{
					if (m_archetypes.count(p_oldArchetype) != 0) //Old archetype is in the query, so new is too
					{
						m_archetypes.insert(p_NewArchetype); //Add it
						return;
					}

				}

				//
				// check all the components of the query in the new archetype
				for (int i = 0; i < sizeof...(Args); ++i)
				{
					if (p_newArchetypeComponents.count(m_componentsID[i]) == 0)
					{
						return;//Components doesn't match with new archetypes, don't change the archetype llist
					}
				}

				//
				// All the components of the query were found in the new archetype, add it to the list
				m_archetypes.insert(p_NewArchetype);
				
			}

		private:
			static constexpr auto gen_compsID_table() {
				auto compsID_table = cexp::array<PeComponentID, sizeof...(Args)>{};
				int i = 0;
				([&]
					{
						compsID_table[i] = Args::CompId();
					}
				(), ...);

				return compsID_table;
			}

		public:
		protected:
		private:

			std::unordered_set<PeArchetypeID> m_archetypes; //List of all the archetypes that match the query types
			ComponentDataMap* m_componentsDataMap[sizeof...(Args)];
			static constexpr auto m_componentsID = gen_compsID_table();




		};
	}
}


