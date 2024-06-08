#pragma once

#include <mutex>

namespace engine {

	namespace core {

		template<typename T, size_t N>
		class CPeThreadSafeQueue
		{
		public:

			CPeThreadSafeQueue()
				:data()
				,head(0)
				,tail(0)
				,locker()
			{

			}

			inline bool Push_Back(const T& item)
			{
				locker.lock();
				size_t next = (head + 1) % N;
				if (next != tail)
				{
					data[head] = item;
					head = next;
					locker.unlock();
					return true;
				}
				locker.unlock();
				return false;
			}

			inline bool Pop_Front(T& item)
			{
				locker.lock();
				if (tail != head)
				{
					item = data[tail];
					tail = (tail + 1) % N;
					locker.unlock();
					return true;
				}
				locker.unlock();
				return false;
			}

		protected:
		private:

		public:
		protected:
		private:
			T data[N];
			size_t head;
			size_t tail;
			std::mutex locker;

		};

	}
}