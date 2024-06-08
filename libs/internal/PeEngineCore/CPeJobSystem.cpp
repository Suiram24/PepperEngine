#include "CPeJobSystem.h"

namespace engine {
namespace core {

	void CPeJobSystem::Initialize()
	{
		m_finishedLabel.store(0);
		auto numCores = std::thread::hardware_concurrency();
		m_numThreads = std::max(1u, numCores);

		for (uint32_t threadID = 0; threadID < m_numThreads; ++threadID)
		{
			std::thread worker([this] {

				std::function<void()> job; 

				while (true)
				{
					if (m_jobPool.Pop_Front(job)) // try to grab a job from the jobPool queue
					{
							
						job(); 
						m_finishedLabel.fetch_add(1);
					}
					else
					{
						// no job, put thread to sleep
						std::unique_lock<std::mutex> lock(m_wakeMutex);
						m_wakeCondition.wait(lock);
					}
				}


			});

			worker.detach();
		}

	}

	void CPeJobSystem::Execute(const std::function<void()>& job)
	{
		++m_currentLabel;

		//Try to push a new job as long as it is not done
		while (!m_jobPool.Push_Back(job))
		{
			Poll();
		}

		m_wakeCondition.notify_one();
	}

	bool CPeJobSystem::IsBusy()
	{
		return m_finishedLabel.load() < m_currentLabel;
	}

	void CPeJobSystem::Wait()
	{
		while (IsBusy())
		{
			Poll();
		}
	}

	void CPeJobSystem::Poll()
	{
		//wake one worker thread
		m_wakeCondition.notify_one();
		std::this_thread::yield();
	}
}
}