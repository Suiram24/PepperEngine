#pragma once

#include <unordered_map>
#include <unordered_set>
#include <typeinfo>
#include <any>
#include "CRC32.h"

namespace engine
{
	namespace core
	{
		typedef signed long long PeEntity; //an int64 ID that identify an entity
		typedef signed long PeComponentID; //an int32 ID that identify a component
		typedef signed long PeArchetypeID; //an int32 ID that identify an archetype, a unique combinaison of components

		struct ComponentDataArray
		{
			void* first;
			size_t ComponentSize; //Size of a single component data
			size_t count; //Number of entities in the array
		};

#define PECOMPONENT(X)										\
static constexpr int compTypeID = X;						\
static int CompId()											\
{															\
	return compTypeID;										\
}


		using ComponentDataMap = std::unordered_map< PeArchetypeID, std::any>;


		struct EntityArchetype
		{
			PeArchetypeID archetypeID;
			//int EntityIndex; //index of the entity inside the archetype entities arrays
			//int archetypeIndex; //Index of the archetype in the component unordered map
		};

		struct ArchetypeChange
		{
			PeArchetypeID archetypeID; //Base archetype
			PeComponentID componentID; //Component to be added or removed

			bool operator==(const ArchetypeChange& other) const
			{
				return archetypeID == other.archetypeID && componentID == other.componentID;
			}
		};

		struct ComponentArrayHash {
			size_t operator()(const std::vector<PeComponentID>& a) const
			{
				size_t res = 0;

				for (const PeComponentID& c : a)
				{
					res = res ^ std::hash<int>()(c);
				}
				// Combine hashes of x and y using the bitwise XOR
				return res;
			}
		};

		struct ComponentIDHash {
			size_t operator()(const PeComponentID& c) const
			{
				// Combine hashes of x and y using the bitwise XOR
				return std::hash<int>()(c);
			}
		};

		struct TypeInfoHash {
			size_t operator()(const std::type_info& t) const
			{
				// Combine hashes of x and y using the bitwise XOR
				return t.hash_code();
			}
		};


		struct ArchetypChangeHash {
			size_t operator()(const ArchetypeChange& ac) const
			{
				// Combine hashes of x and y using the bitwise XOR
				return std::hash<int>()(ac.archetypeID) ^ (std::hash<int>()(ac.componentID) << 1);
			}
		};

		

		/**
		 * @brief ECS Class that will hold all the data
		*/
		class CPeWorld
		{
		public:
			CPeWorld();

			PeEntity CreateEntity();

			template<typename T>
			PeEntity Add(const PeEntity entity)
			{
				PeComponentID component = GetID<T>();
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

					if (m_ArchetypesRegistry.count(componentsArray) != 0) //The new archetype already exist
					{
						nextArchetype = m_ArchetypesRegistry.at(componentsArray);
					}
					else //The new archetype doesn't exist yet, we have to create it
					{
						nextArchetype = CreateArchetype<T>(componentsArray);
					}

					//
					//Register the next archetypeID, so we don't have to do this search again and can access it in O(1)
					m_nextArchetype.insert(std::pair<ArchetypeChange, PeArchetypeID>{pair, nextArchetype});

					//Register the reverse operation 
					pair.archetypeID = nextArchetype;
				}

				entityArchetype.archetypeID = nextArchetype;
				//TODO: move entity data from old to new archetype here

				return entity;
			}

			template<typename T>
			PeEntity Remove(const PeEntity entity)
			{
				PeComponentID component = GetID<T>();
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


					if (m_ArchetypesRegistry.count(componentsArray) != 0) //The new archetype already exist
					{
						prevArchetype = m_ArchetypesRegistry.at(componentsArray);
					}
					else //The new archetype doesn't exist yet, we have to create it
					{
						prevArchetype = CreateArchetype<T>(componentsArray);
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

			template<typename T>
			bool HasComponent(const PeEntity entity)
			{
				PeComponentID component = GetID<T>();
				const PeArchetypeID archetypeID = m_EntitiesArchetypeMap.at(entity).archetypeID; //O(1)
				const ComponentDataMap& componentData = m_ComponentArchetypeMap.at(component); //O(1)

				return componentData.count(archetypeID) != 0; // O(1)
			}

			

			template<typename T>
			PeComponentID GetID()
			{
				
				size_t compID = T::CompId();
				if (m_componentsID.count(compID) != 0) //Component already registred, return the id
				{
					return m_componentsID.at(compID);
				}
				else //Register the new component in the tables, and return the new ID
				{
					m_componentsID.insert(std::make_pair(compID, ++LastComponentRegistred));
					ComponentDataMap newEmptyMap = ComponentDataMap();
					m_ComponentArchetypeMap.insert(std::make_pair(LastComponentRegistred, newEmptyMap));
					return LastComponentRegistred;
				}

			}


		protected:
		private:

			template<typename T>
			PeArchetypeID CreateArchetype(const std::vector<PeComponentID>& componentsVector)
			{
				m_ArchetypesRegistry.insert(std::pair<std::vector<PeComponentID>, PeArchetypeID>{componentsVector, ++LastArchetypeCreated});

				//Register the new archetype in the component->archetypes map
				for (auto& c : componentsVector)
				{
					ComponentDataMap& cDataMap = m_ComponentArchetypeMap.at(c);

					cDataMap.insert(std::make_pair(LastArchetypeCreated, std::vector<T>()));
				}

				return LastArchetypeCreated;
			}


		public:
		protected:
		private:
			std::unordered_map<PeEntity, EntityArchetype> m_EntitiesArchetypeMap; //Map that store the archetype of every entity of the world
			std::unordered_map<PeComponentID, ComponentDataMap, ComponentIDHash> m_ComponentArchetypeMap; //Map that store the archetypes that use every component, and store the components data
			std::unordered_map<std::vector<PeComponentID>, PeArchetypeID, ComponentArrayHash> m_ArchetypesRegistry; //Store all the uniques combinaisons of components and the archetype ID associated with it
			std::unordered_map<PeArchetypeID, std::vector<PeComponentID>> m_ArchetypesComponentList; //Store all the componant that form an archetype


			//Archetype graph: 
			std::unordered_map<ArchetypeChange, PeArchetypeID, ArchetypChangeHash> m_nextArchetype; // Store the archetype that has all the initial archetype components and the new component
			std::unordered_map<ArchetypeChange, PeArchetypeID, ArchetypChangeHash> m_prevArchetype;// Store the archetype that has all the initial archetype components exept the new component

			std::unordered_map<size_t, PeComponentID> m_componentsID;

			PeEntity LastEntityCreated = 0;
			PeArchetypeID LastArchetypeCreated = 0;
			PeComponentID LastComponentRegistred = 0;
		};
	}
}