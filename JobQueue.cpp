#include "JobQueue.h"

JobQueue::JobQueue()
	: m_cond(SDL_CreateCond())
	, m_locked(SDL_CreateMutex())
{
}

void JobQueue::AddTask(std::function<void()> newTask)
{
	if (!m_completed)
	{
		SDL_LockMutex(m_locked);		
		m_tasks.push(newTask);			
		SDL_CondSignal(m_cond);	
		SDL_UnlockMutex(m_locked);
	}
}

std::function<void()> JobQueue::NextTask()
{
	std::function<void()> nextJob = 0;
	SDL_LockMutex(m_locked);
	if (m_completed && m_tasks.size() == 0)
	{
		nextJob = 0;
	}
	else
	{
		while (m_tasks.size() == 0)
		{
			SDL_CondWait(m_cond, m_locked);
		}
		nextJob = m_tasks.front();
		m_tasks.pop();
	}
	SDL_UnlockMutex(m_locked);
	return nextJob;
}

bool JobQueue::HasWorkToDo()
{
	// IF THERE IS WORK TO DO
	return m_tasks.size() > 0;
}