#include <utility>
#include <cstdarg>

#include "threadManager.h"

using namespace Core;

ThreadManager::~ThreadManager()
{
	for (int i = 0; i < threads.size(); i++)
		threads[i].thread->join();

	for (int i = 0; i < threads.size(); i++)
		delete threads[i].thread;
}