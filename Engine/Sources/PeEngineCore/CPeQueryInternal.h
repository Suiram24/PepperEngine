#pragma once
#include <functional>
#include <unordered_set>

#include "PeECSDefinitions.h"


namespace engine::core
{
	template<PeComponentStruct...Args>
	class CPeBuiltQuery
	{
		template<PeComponentStruct...TArgs>
		friend class CPeQuery;
	public:
		explicit CPeBuiltQuery(void* owner)
		: m_world(owner)
		{
		}
	private:
		void *m_world;
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
				const CPeGenericComponentDataArray& dataArray = m_componentsDataMap[0]->at(archetype);
				if (dataArray.ElementCount() == 0)
				{
					continue;
				}
				for (int i = 0; i < dataArray.Count(); ++i)
				{
					if (!dataArray.IsValid(i))
					{
						continue;
					}
					int j = sizeof...(Args);
					p_function(*(m_componentsDataMap[--j]->at(archetype).template GetEntityData<Args>(i))...);
				}

			}
		}



	protected:
		void UpdateComponentsDataMap(const std::unordered_map<PeComponentID, ComponentDataMap, ComponentIDHash>& p_ComponentArchetypesMap)
		{
			int i = 0;
			([&]
				{
					m_componentsDataMap[i++] = &(p_ComponentArchetypesMap.at(Args::CompId()));
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
					compsID_table[i++] = Args::CompId();
				}
			(), ...);

			return compsID_table;
		}

	public:
	protected:
	private:

		std::unordered_set<PeArchetypeID> m_archetypes; //List of all the archetypes that match the query types
		const ComponentDataMap* m_componentsDataMap[sizeof...(Args)];
		static constexpr auto m_componentsID = gen_compsID_table();




	};
}



