#pragma once

#include <unordered_map>
#include <unordered_set>
#include <typeinfo>
#include <any>
#include <functional>
#include "CRC32.h"
#include "CPeGenericComponentDataArray.h"

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

#if PE_DEBUG
#define PECOMPONENT(NAME)									\
static constexpr int compTypeID = engine::core::crc32(NAME);\
static constexpr int CompId()								\
{															\
	return compTypeID;										\
}															\
static void PrintTypeName()									\
{															\
	printf(NAME);											\
}
#else
#define PECOMPONENT(NAME)									\
static constexpr int compTypeID = engine::core::crc32(NAME);\
static constexpr int CompId()								\
{															\
	return compTypeID;										\
}															
#endif // PE_DEBUG





		using ComponentDataMap = std::unordered_map< PeArchetypeID, CPeGenericComponentDataArray>;


		struct EntityArchetype
		{
			PeArchetypeID archetypeID;
			int EntityIndex; //index of the entity inside the archetype entities arrays
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
				if (HasComponent<T>(entity))
				{
					return entity;
				}
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

					m_prevArchetype.insert(std::pair<ArchetypeChange, PeArchetypeID>{pair, entityArchetype.archetypeID});
				}

				
				CPeGenericComponentDataArray& dataArray = m_ComponentArchetypeMap.find(component)->second.find(nextArchetype)->second;
				T emptyComponent;
				int newIndex = dataArray.AddEntityData<T>(&emptyComponent);
				std::vector<PeComponentID>& archetypeComponents = m_ArchetypesComponentList.find(nextArchetype)->second;
				for (PeComponentID componentID : archetypeComponents)
				{
					if (componentID == component)
					{
						continue;
					}
					ComponentDataMap& compDataMap = m_ComponentArchetypeMap.find(componentID)->second;
					compDataMap.find(nextArchetype)->second.MoveEntityDataFrom(compDataMap.find(entityArchetype.archetypeID)->second, entityArchetype.EntityIndex, newIndex);
				}
				//TODO: move entity data from old to new archetype here

				entityArchetype.archetypeID = nextArchetype;
				entityArchetype.EntityIndex = newIndex;

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
			void ForEach(std::function<void(T& component)> function)
			{
				PeComponentID componentID = GetID<T>();
				const ComponentDataMap& componentData = m_ComponentArchetypeMap.at(componentID);
				for (auto& arch : componentData)
				{
					for (int i = 0; i < arch.second.Count(); ++i)
					{
						if (arch.second.IsValid(i))
						{
							function(*(arch.second.GetEntityData<T>(i)));
						}
					}
				}
			}

			template<typename T, typename U>
			void ForEach(std::function<void(T& component, U& Component2)> function)
			{
				PeComponentID componentID = GetID<T>();
				PeComponentID componentID2 = GetID<U>();
				const ComponentDataMap& componentData = m_ComponentArchetypeMap.at(componentID);
				const ComponentDataMap& componentData2 = m_ComponentArchetypeMap.at(componentID2);
				for (auto& arch : componentData) //For every archetype of first component
				{
					if (componentData2.count(arch.first) != 0) //if the second component also posses the archetype
					{
						for (int i = 0; i < arch.second.Count(); ++i)
						{
							if (arch.second.IsValid(i))
							{
								T& c1 = *(arch.second.GetEntityData<T>(i));
								U& c2 = *(componentData2.at(arch.first).GetEntityData<U>(i));

								function(c1, c2);
							}
						}
					}
					
				}
			}

			

			template<typename T>
			PeComponentID GetID()
			{
				
				size_t compID = T::CompId();
				if (m_ComponentArchetypeMap.count(compID) != 0) //Component already registred, return the id
				{
					return compID;
				}
				else //Register the new component in the tables, and return the new ID
				{
					ComponentDataMap newEmptyMap = ComponentDataMap();
					m_ComponentArchetypeMap.insert(std::make_pair(compID, newEmptyMap));
					return compID;
				}

			}

			template<typename T>
			T* Get(const PeEntity entity)
			{
				PeComponentID component = GetID<T>();
				const EntityArchetype archetype = m_EntitiesArchetypeMap.at(entity); //O(1)
				const ComponentDataMap& componentData = m_ComponentArchetypeMap.at(component); //O(1)

				
				if (auto mapIterator = componentData.find(archetype.archetypeID); mapIterator != componentData.end()) // O(1)
				{
					const CPeGenericComponentDataArray& datarow = mapIterator->second;
					return datarow.GetEntityData<T>(archetype.EntityIndex);
				}

				return nullptr;
			}

			template<typename T>
			PeEntity Set(const PeEntity entity, const T& component)
			{
				if (!HasComponent<T>(entity))
				{
					Add<T>(entity);
				}

				*Get<T>(entity) = component;

				return entity;
			}


		protected:
		private:

			template<typename T>
			PeArchetypeID CreateArchetype(const std::vector<PeComponentID>& componentsVector)
			{
				m_ArchetypesRegistry.insert(std::pair<std::vector<PeComponentID>, PeArchetypeID>{componentsVector, ++LastArchetypeCreated});
				m_ArchetypesComponentList.insert(std::pair<PeArchetypeID, std::vector<PeComponentID>>{LastArchetypeCreated, componentsVector});

				//Register the new archetype in the component->archetypes map
				for (auto c : componentsVector)
				{
					if (c == GetID<T>())
					{
						ComponentDataMap& cDataMap = m_ComponentArchetypeMap.at(c);
						cDataMap.insert(std::make_pair(LastArchetypeCreated, CPeGenericComponentDataArray()));
						cDataMap.at(LastArchetypeCreated).Initialize<T>();
					}
					else
					{
						ComponentDataMap& cDataMap = m_ComponentArchetypeMap.at(c);
						cDataMap.insert(std::make_pair(LastArchetypeCreated, CPeGenericComponentDataArray()));
						cDataMap.at(LastArchetypeCreated).CopyInitialize(cDataMap.begin()->second);
					}
				
					
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

			PeEntity LastEntityCreated = 0;
			PeArchetypeID LastArchetypeCreated = 0;
			PeComponentID LastComponentRegistred = 0;
		};
	}
}