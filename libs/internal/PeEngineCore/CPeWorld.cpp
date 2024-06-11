#include "CPeWorld.h"

#include "algorithm"

namespace engine
{
	namespace core
	{

		CPeWorld::CPeWorld()
			:m_EntitiesArchetypeMap()
			, m_ComponentArchetypeMap()
			, m_ArchetypesRegistry()
			, m_ArchetypesComponentList()
			, m_nextArchetype()
			, m_prevArchetype()
		{
			//Initialize the void archetype
			std::vector<PeComponentID> voidVector;
			m_ArchetypesRegistry.insert(std::pair<std::vector<PeComponentID>, PeArchetypeID>(voidVector, 0));
		}

		PeEntity CPeWorld::CreateEntity()
		{
			m_EntitiesArchetypeMap.insert(std::pair<PeEntity, EntityArchetype>(++LastEntityCreated, EntityArchetype{ 0 }));

			return LastEntityCreated;
		}

		PeEntity CPeWorld::Add(const PeEntity entity, const PeComponentID component)
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
					nextArchetype = CreateArchetype(componentsArray);
				}

				//
				//Register the next archetypeID, so we don't have to do this search again and can access it in O(1)
				m_nextArchetype.insert(std::pair<ArchetypeChange, PeArchetypeID>{pair, nextArchetype});

				//Register the reverse operation 
				pair.archetypeID = nextArchetype;
				m_prevArchetype.insert(std::pair<ArchetypeChange, PeArchetypeID>{pair, entityArchetype.archetypeID});
			}

			entityArchetype.archetypeID = nextArchetype;
			//TODO: move entity data from old to new archetype here

			return entity;
		}

		PeEntity CPeWorld::Remove(const PeEntity entity, const  PeComponentID component)
		{
			EntityArchetype& entityArchetype = m_EntitiesArchetypeMap.at(entity);
			ArchetypeChange pair = { entityArchetype.archetypeID, component };
			PeArchetypeID prevArchetype;

			if (m_nextArchetype.count(pair) != 0) //Great, we have already added this component to this archetype
			{
				prevArchetype = m_prevArchetype.at(pair);
			}
			else //We have to find the destination archetype
			{
				std::vector<PeComponentID> componentsArray;
				for (auto& p : m_ArchetypesRegistry) //Retrieve current entity component (O(n))
				{
					if (p.second == entityArchetype.archetypeID)
					{
						for (auto& c : p.first)
						{
							if (c != component) //Add all the components expet the one we want to remove
							{
								componentsArray.push_back(c);
							}

						}
						break;
					}
				}

				std::sort(componentsArray.begin(), componentsArray.end()); //Make sure components are sorted so same components = same hash

				if (m_ArchetypesRegistry.count(componentsArray) != 0) //The new archetype already exist
				{
					prevArchetype = m_ArchetypesRegistry.at(componentsArray);
				}
				else //The new archetype doesn't exist yet, we have to create it
				{
					prevArchetype = CreateArchetype(componentsArray);
				}

				//
				//Register the next archetypeID, so we don't have to do this search again and can access it in O(1)
				m_prevArchetype.insert(std::pair<ArchetypeChange, PeArchetypeID>{pair, prevArchetype});

				//Register the reverse operation 
				pair.archetypeID = prevArchetype;
				m_nextArchetype.insert(std::pair<ArchetypeChange, PeArchetypeID>{pair, entityArchetype.archetypeID});
			}

			entityArchetype.archetypeID = prevArchetype;
			//TODO: move entity data from old to new archetype here

			return entity;
		}

		bool CPeWorld::HasComponent(const PeEntity entity, const  PeComponentID component) const
		{
			const PeArchetypeID archetypeID = m_EntitiesArchetypeMap.at(entity).archetypeID; //O(1)
			const ComponentDataMap& componentData = m_ComponentArchetypeMap.at(component); //O(1)

			return componentData.count(archetypeID) != 0; // O(1)
		}

		PeArchetypeID CPeWorld::CreateArchetype(const std::vector<PeComponentID>& componentsVector)
		{
			m_ArchetypesRegistry.insert(std::pair<std::vector<PeComponentID>, PeArchetypeID>{componentsVector, ++LastArchetypeCreated});

			//Register the new archetype in the component->archetypes map
			for (auto& c : componentsVector)
			{
				ComponentDataMap& cDataMap = m_ComponentArchetypeMap.at(c);
				cDataMap.insert(std::make_pair(LastArchetypeCreated, ComponentDataArray{ nullptr,0,0 }));
			}

			return LastArchetypeCreated;
		}
	}
}