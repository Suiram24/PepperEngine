#include "CPeWorld.h"


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
			m_ArchetypesComponentList.insert(std::pair<PeArchetypeID, std::vector<PeComponentID>>(0, voidVector));
		}

		PeEntity CPeWorld::CreateEntity()
		{
			m_EntitiesArchetypeMap.insert(std::pair<PeEntity, EntityArchetype>(++LastEntityCreated, EntityArchetype{ 0 }));

			return LastEntityCreated;
		}

		
		
	}
}