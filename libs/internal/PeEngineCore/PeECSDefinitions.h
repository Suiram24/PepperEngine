#pragma once

#include <vector>
#include <unordered_map>

#include "CRC32.h"
#include "CPeGenericComponentDataArray.h"

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


namespace engine
{
	namespace core
	{
		// If a struct does not satisfy PeComponentStruct, you likely forgot to add the macro PECOMPONENT("struct name") to it
		template<typename T>
		concept PeComponentStruct = requires(T a)
		{
			{ T::CompId() } -> std::convertible_to<int>;
		};


		typedef signed long long PeEntity; //an int64 ID that identify an entity
		typedef signed long PeComponentID; //an int32 ID that identify a component
		typedef signed long PeArchetypeID; //an int32 ID that identify an archetype, a unique combinaison of components

		using ComponentDataMap = std::unordered_map< PeArchetypeID, CPeGenericComponentDataArray>;

		struct EntityArchetype
		{
			PeArchetypeID archetypeID;
			int EntityIndex; //index of the entity inside the archetype entities arrays
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
	}
}


