#pragma once

#include <atomic>

namespace engine {

	namespace core {

		class CPeSpinlock
		{
		public:

			CPeSpinlock():
				m_latch(false)
			{

			}

			void Lock()
			{
				bool unlatched = false;
				while (!m_latch.compare_exchange_weak(unlatched, true, std::memory_order_acquire)) {
					unlatched = false;
				}
			}

			void Unlock() {
				m_latch.store(false, std::memory_order_release);
			}

		protected:
		private:

		public:
		protected:
		private:

			std::atomic_bool m_latch;
		};

	}
}