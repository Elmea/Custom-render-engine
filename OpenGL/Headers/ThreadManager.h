#pragma once
#include<thread>
#include<vector>
#include <any>

namespace Core
{
	enum class ThreadType
	{
		LOAD,
		PHYSICS,
		CAMERA
	};

	struct Thread
	{
		ThreadType type;
		std::thread* thread;
	};

	class ThreadManager
	{
	public:

		void AddThread(ThreadType type, std::thread* thread)
		{
			Thread newOne;
			newOne.type = type;
			newOne.thread = thread;
			threads.push_back(newOne);
		}

		~ThreadManager();

	private:
		std::vector<Thread> threads;
	};

	static ThreadManager threadManager;
}