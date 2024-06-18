#pragma once

#include <vector>
#include <exception>
#include <unordered_set>

namespace engine
{
	namespace core
	{
		class CPeGenericComponentDataArray
		{
			friend class CPeGenericComponentDataArray;

		public:

			/**
				* @brief Default constructor, don't forget to call Initialize() rigth after!
			*/
			CPeGenericComponentDataArray(int ElementAllocationStride = 16)
				: m_First(nullptr)
				, m_ElementSize(0)
				, m_ElementCount(0)
				, m_ComponentTypeID(0)
				, m_AllocatedSlotsCount(0)
				, m_ElementAllocationStride(ElementAllocationStride)
				, m_FreeIndexes()
			{
			}

			~CPeGenericComponentDataArray()
			{
				if (m_First)
				{
					free(m_First);
				}
				
			}

			template<typename T>
			T* Begin() const
			{
				if (T::CompId() != m_ComponentTypeID)
				{
					throw std::exception("Component Data Array error: components types do not match");
					return nullptr;
				}

				return static_cast<T*>(m_First);
			}

			template<typename T>
			T* End() const
			{
				if (T::CompId() != m_ComponentTypeID)
				{
					throw std::exception("Component Data Array error: components types do not match");
					return nullptr;
				}

				void* res = static_cast<char*>(m_First) + m_ElementCount * m_ElementSize;
				return static_cast<T*>(res);
			}

			bool IsValid(int index) const;
			int Count() const;


			template<typename T> 
			void Initialize()
			{
				m_ElementSize = sizeof(T);
				m_ComponentTypeID = T::CompId();
				Allocate(m_ElementAllocationStride);
			}

			void CopyInitialize(const CPeGenericComponentDataArray& target)
			{
				m_ElementSize = target.m_ElementSize;
				m_ComponentTypeID = target.m_ComponentTypeID;
				Allocate(m_ElementAllocationStride);
			}

			/**
			* @brief Add a a new entity to the array, copying its data
			* @return The entity index in the archetype array
			*/
			template <typename T>
			int AddEntityData(T* entityData)
			{

				if (T::CompId() != m_ComponentTypeID)
				{
					throw std::exception("Component Data Array error: components types do not match");
					return -1;
				}

				int index;
				if (m_FreeIndexes.size() != 0)
				{
					index = *m_FreeIndexes.begin();
					m_FreeIndexes.erase(index);
					memcpy(static_cast<T*>(m_First) + index, entityData, m_ElementSize);
				}
				else 
				{
					if (m_ElementCount == m_AllocatedSlotsCount)
					{
						Allocate(m_ElementAllocationStride);
					}
					index = m_ElementCount;
					++m_ElementCount;
					memcpy(static_cast<T*>(m_First) + index, entityData, m_ElementSize);
				}

				return index;
			}

			/**
			* @brief Add a a new entity to the array, copying its data
			* @return The entity index in the archetype array
			*/
			template<typename T>
			T* GetEntityData(int entityIndex) const
			{
				if (T::CompId() == m_ComponentTypeID)
				{
					if (entityIndex < m_ElementCount)
					{
						void* res = static_cast<char*>(m_First) + entityIndex * m_ElementSize;
						return static_cast<T*>(res);
					}
					else
					{
						throw std::exception("Component Data Array error: Index out of bounds");
					}
				}
				else
				{
					throw std::exception("Component Data Array error: components types do not match");
				}
			}

			/**
				* @brief Move an entity data from an array to this one
			*/
			void MoveEntityDataFrom(CPeGenericComponentDataArray& originArray, int oldIndex, int newIndex);

			void RemoveEntityData(int index);
		protected:
		private:

			/**
				* @brief Allocate memory for the number of elements specified wwith slotNumber
			*/
			bool Allocate(int slotNumber);

		public:
		protected:
		private:

			void* m_First;
			size_t m_ElementSize;
			size_t m_ElementCount;
			int m_ComponentTypeID;

			//Memory management
			int m_AllocatedSlotsCount;
			int m_ElementAllocationStride;
			std::unordered_set<int> m_FreeIndexes;



		};
	}
}


