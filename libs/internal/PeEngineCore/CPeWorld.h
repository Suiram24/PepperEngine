#pragma once

#include <unordered_map>
#include <unordered_set>

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

		using ComponentDataMap = std::unordered_map< PeArchetypeID, ComponentDataArray>;


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

			PeEntity Add(const PeEntity entity, const PeComponentID component);
			PeEntity Remove(const PeEntity entity, const PeComponentID component);
			bool HasComponent(const PeEntity entity, const PeComponentID component) const;


		protected:
		private:


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
		};
	}
}