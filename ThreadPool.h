#pragma once
#include <thread>
#include <queue>
#include <SDL_mutex.h>
#include <SDL_thread.h>
#include <vector>
#include <functional>
#include "JobQueue.h"

static int getWork(void* param);

class ThreadPool
{
public:
	ThreadPool();
	void AddTask(std::function<void()> newTask);
private:
	std::vector<SDL_Thread*> m_threads;
	JobQueue m_jobQueue;
};