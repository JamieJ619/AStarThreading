#include "ThreadPool.h"
#include <iostream>

int getWork(void * param)
{
	std::function<void()> job;
	JobQueue * jobQueue = (JobQueue*)param;
	while (job = jobQueue->NextTask())
	{
		job();
	}
	return 0;
}

ThreadPool::ThreadPool()
{
	int numOfCores = std::thread::hardware_concurrency() - 1;
	for (int i = 0; i < numOfCores; i++)
	{
		m_threads.push_back(SDL_CreateThread(getWork, " ", &m_jobQueue));
	}
}

void ThreadPool::AddTask(std::function<void()> newTask)
{
	m_jobQueue.AddTask(newTask);
}
