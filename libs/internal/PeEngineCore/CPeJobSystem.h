#pragma once

#include <functional>
#include <algorithm>   
#include <atomic>   
#include <thread>    
#include <condition_variable>   

#include "CPeThreadSafeQueue.h"

 


namespace engine {

	namespace core {
		
		 
		/**
		 * @brief A class for Newton's Physics forces.
		*/
		class CPeJobSystem {
	public:

			//
			// Singleton setup
			static CPeJobSystem& GetInstance()
			{
				static CPeJobSystem instance;
				return instance;
			}

			void Initialize();

			void Execute(const std::function<void()>& job);

			/**
			 * @brief Wait for all threads to finish their work
			 */
			void Wait();

		protected:
		private:
			CPeJobSystem()
				:m_numThreads(0)
				,m_jobPool()
				,m_wakeCondition()
				,m_wakeMutex()
				,m_currentLabel(0)
				,m_finishedLabel()
			{

			}

			/**
			 * @brief Return true if at least on thread is still working
			 */
			bool IsBusy();



			/**
			 * @brief Wake on wurker thread and yield
			 */
			void Poll();

		public:
		protected:
		private:

			uint32_t m_numThreads;
			CPeThreadSafeQueue<std::function<void()>, 256> m_jobPool;
			std::condition_variable m_wakeCondition;
			std::mutex m_wakeMutex;
			uint64_t m_currentLabel;
			std::atomic<uint64_t> m_finishedLabel;




		};
	}
}

