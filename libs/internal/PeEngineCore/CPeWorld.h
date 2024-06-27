#pragma once

#include <unordered_map>
#include <unordered_set>
#include <functional>
#include <any>

#include "CPeGenericComponentDataArray.h"
#include "PeECSDefinitions.h"
#include "CPeQuery.h"

namespace engine
{
	namespace core
	{

		/**
		 * @brief ECS Class that will hold all the data of a single "world"
		*/
		class CPeWorld
		{
			template<PeComponentStruct...Args>
			friend class CPeQuery;
		public:
			CPeWorld();


			PeEntity CreateEntity();

			template<PeComponentStruct T>
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

			template<PeComponentStruct T>
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

			template<PeComponentStruct T>
			bool HasComponent(const PeEntity entity)
			{
				PeComponentID component = GetID<T>();
				const PeArchetypeID archetypeID = m_EntitiesArchetypeMap.at(entity).archetypeID; //O(1)
				const ComponentDataMap& componentData = m_ComponentArchetypeMap.at(component); //O(1)

				return componentData.count(archetypeID) != 0; // O(1)
			}

			template<PeComponentStruct ... Args>
			void ForEach(const std::function<void(Args& ... p_params)>& function)
			{
				//
				// Retrieve the components ID and Data maps of every component in Args
				std::vector<PeComponentID> componentsID;
				std::vector<const ComponentDataMap*> componentsData;
				int cnt = 0;
				([&]
					{
						componentsID.push_back(GetID<Args>());
						componentsData.push_back(&m_ComponentArchetypeMap.at(componentsID.back()));
						++cnt;
					} (), ...);//Fold Expression that will iterate over Args from first to last type
			
				for (auto& arch : *(componentsData[0])) //For every archetype of first component
				{
					//Check if the archetype is possesed by all the components
					bool result = true;
					for (int j = 0; j < componentsData.size(); ++j)
					{
						if (componentsData[j]->count(arch.first) == 0) //This component doesn't have the archetype being tested
						{
							result = false;
							break;
						}
					}

					if (!result) { continue; }
					//
					// We confirmed this archetype has all the components, now let's call the function for the components of this archetype

					//For every used slot in the Component Data Array
					for (int i = 0; i < arch.second.Count(); ++i)
					{
						if (arch.second.IsValid(i))
						{
							int j = cnt;

							//Another Fold Expression, that for some reason goes from last to first type, hence the decreasing j
							function(*(componentsData[--j]->at(arch.first).GetEntityData<Args>(i))...);
						}
					}
				}
			}


			

			template<PeComponentStruct ... Args>
			CPeQuery<Args...>&& Build()
			{


				static constexpr int hash = (Args::CompId()^...^0);
				if (m_QueriesRegistry.count(hash) == 0)
				{
					std::any internalQuery = CPeQueryInternal<Args...>();
					m_QueriesRegistry.insert(std::make_pair(hash, internalQuery));
					CPeQueryInternal<Args...> query = std::any_cast<CPeQueryInternal<Args...>>(m_QueriesRegistry.at(hash));
					query.UpdateComponentsDataMap(m_ComponentArchetypeMap);

					//
					// Build the archetype list
					std::unordered_set<PeArchetypeID> archetypelist;
					std::vector<PeComponentID> componentsID;
					std::vector<ComponentDataMap*> componentsData;

					([&]
						{
							componentsID.push_back(GetID<Args>());
							componentsData.push_back(&m_ComponentArchetypeMap.at(componentsID.back()));
						} (), ...);

					for (auto& arch : *(componentsData[0])) //For every archetype of first component
					{
						//Check if the archetype is possesed by all the components
						bool result = true;
						for (int j = 0; j < componentsData.size(); ++j)
						{
							if (componentsData[j]->count(arch.first) == 0) //This component doesn't have the archetype being tested
							{
								result = false;
								break;
							}
						}

						if (!result) { continue; }

						archetypelist.insert(arch.first); //Add the archetype to the list
					}
					query.m_archetypes = archetypelist;
					m_QueriesRegistry.at(hash) = query;

				}

				
				CPeQuery<Args...>&& queryRef = CPeQuery<Args...>(this);
				return queryRef;
				
			}

			

			template<PeComponentStruct T>
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

			template<PeComponentStruct T>
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

			template<PeComponentStruct T>
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
			//Query For each
			template<PeComponentStruct ... Args>
			void ForEach(int p_queryID, std::function<void(Args& ... p_params)>& p_function) const
			{
				const std::any& anyQuery = (m_QueriesRegistry.find(p_queryID)->second);
				CPeQueryInternal<Args...> query = std::any_cast<CPeQueryInternal<Args...>>(anyQuery);
				query.ForEach(p_function);
			}
		private:

			template<PeComponentStruct T>
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

			//Queries
			std::unordered_map<int, std::any> m_QueriesRegistry;

			PeEntity LastEntityCreated = 0;
			PeArchetypeID LastArchetypeCreated = 0;
			PeComponentID LastComponentRegistred = 0;
		};
	}
}