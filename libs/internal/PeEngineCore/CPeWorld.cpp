#include "CPeWorld.h"

#include "algorithm"

namespace engine
{
	namespace core
	{

		CPeWorld::CPeWorld()
		:m_EntitiesArchetypeMap()
		,m_ComponentArchetypeMap()
		,m_ArchetypesRegistry()
		,m_ArchetypesComponentList()
		,m_nextArchetype()
		,m_prevArchetype()
		{
			//Initialize the void archetype
			std::vector<PeComponentID> voidVector;
			m_ArchetypesRegistry.insert(std::pair<std::vector<PeComponentID>, PeArchetypeID>(voidVector,0));
		}

		PeEntity CPeWorld::CreateEntity()
		{
			m_EntitiesArchetypeMap.insert(std::pair<PeEntity, EntityArchetype>(++LastEntityCreated, EntityArchetype{0}));
		}

		PeEntity CPeWorld::Add(PeEntity entity, PeComponentID component)
		{
			EntityArchetype& entityArchetype = m_EntitiesArchetypeMap.at(entity);
			ArchetypeChange pair = { entityArchetype.archetypeID, component };
			PeArchetypeID nextArchetype;

			if (m_nextArchetype.count(pair) != 0) //Great, we have already added this component to this archetype
			{
				nextArchetype = m_nextArchetype.at(pair);
			}
			else //We have to find the destination archetype
			{
				std::vector<PeComponentID> componentsArray;
				for (auto& p : m_ArchetypesRegistry) //Retrieve current entity component (O(n))
				{
					if (p.second == entityArchetype.archetypeID)
					{
						componentsArray = p.first;
						break;
					}
				}

				componentsArray.push_back(component);
				std::sort(componentsArray.begin(), componentsArray.end()); //Make sure components are sorted so same components = same hash
				
				if (m_ArchetypesRegistry.count(componentsArray) != 0) //The new archetype already exist
				{
					nextArchetype = m_ArchetypesRegistry.at(componentsArray);
				}
				else //The new archetype doesn't exist yet, we have to create it
				{
					m_ArchetypesRegistry.insert(std::pair<std::vector<PeComponentID>, PeArchetypeID>{componentsArray, ++LastArchetypeCreated});
					nextArchetype = LastArchetypeCreated;
				}

				//
				//Register the next archetypeID, so we don't have to do this search again and can access it in O(1)
				m_nextArchetype.insert(std::pair<ArchetypeChange, PeArchetypeID>{pair, nextArchetype});
			}

			entityArchetype.archetypeID = nextArchetype;
			//TODO: move entity data from old to new archetype here
		}

		PeEntity CPeWorld::Remove(PeEntity, PeComponentID)
		{

		}

		bool CPeWorld::HasComponent(PeEntity, PeComponentID) const
		{

		}

	}
}