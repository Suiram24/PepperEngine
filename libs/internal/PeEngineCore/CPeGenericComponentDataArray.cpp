#include "CPeGenericComponentDataArray.h"
#include <cassert>

namespace engine
{
	namespace core
	{
		
		bool CPeGenericComponentDataArray::IsValid(int index) const
		{
			if (m_FreeIndexes.count(index) == 0)
			{
				return index < m_InstanciedSlotsCount;
			}
			return false;
		}

		int CPeGenericComponentDataArray::Count() const
		{
			return m_InstanciedSlotsCount;
		}

		int CPeGenericComponentDataArray::ElementCount() const
		{
			return m_InstanciedSlotsCount - m_FreeIndexes.size();
		}



		void CPeGenericComponentDataArray::MoveEntityDataFrom(CPeGenericComponentDataArray& originArray, int oldIndex, int newIndex)
		{
			if (newIndex > m_AllocatedSlotsCount)
			{
				assert(false && "Component Data Array error: new index out of bounds");
			}
			if (m_ComponentTypeID != originArray.m_ComponentTypeID)
			{
				assert(false && "Component Data Array error: components types do not match");
			}

			if (newIndex == m_AllocatedSlotsCount)
			{
				Allocate();
			}

			//
			//Copy data 
			void* oldDataPtr = static_cast<char*>(originArray.m_First) + m_ElementSize * oldIndex;
			void* newDataPtr = static_cast<char*>(m_First) + m_ElementSize * newIndex;
			memcpy(newDataPtr, oldDataPtr, m_ElementSize);

			if (m_FreeIndexes.count(newIndex) != 0) //remove from the free index if we reused a slot
			{
				m_FreeIndexes.erase(newIndex);
			}
			else if (newIndex == m_InstanciedSlotsCount)
			{
				++m_InstanciedSlotsCount;
			}
			else
			{
				assert(false && "Component Data Array error: new index cannot be found");
			}

			//Free the index in the original array
			originArray.RemoveEntityData(oldIndex);
			
			
		}

		void CPeGenericComponentDataArray::RemoveEntityData(int index)
		{
			if (index >= m_AllocatedSlotsCount)
			{
				assert(false && "Component Data Array error : Index out of bounds");
			}
			if (m_FreeIndexes.count(index) != 0)
			{
				return; //entity already removed
			}
			m_FreeIndexes.insert(index);
			
		}


		bool CPeGenericComponentDataArray::Allocate()
		{
			m_ElementAllocationStride *= 2;
			void* newPtr = realloc(m_First, (m_InstanciedSlotsCount + m_ElementAllocationStride) * m_ElementSize);
			if (newPtr != nullptr)
			{
				m_First = newPtr;
				m_AllocatedSlotsCount = m_InstanciedSlotsCount + m_ElementAllocationStride;
				return true;
			}
			else
			{
				assert(false && "Component Data Array realloc failed");
				return false;
			}
		}

	}
}

