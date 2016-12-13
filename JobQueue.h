#pragma once
#include <thread>
#include <queue>
#include <SDL_mutex.h>
#include <SDL_thread.h>
#include <vector>
#include <functional>

class JobQueue
{
public:
	JobQueue();
	void AddTask(std::function<void()> newTask);
	std::function<void()> NextTask();
	void Completed();
	bool HasWorkToDo();
private:
	SDL_mutex* m_locked;
	SDL_cond* m_cond;
	std::queue<std::function<void()>> m_tasks;
	bool m_completed;
};
