#pragma once
#include <assert.h>
#include <mutex>
#include <atomic>
#include <thread>

struct Task
{
	void* m_Function;
};

#define MYENGINE_MAX_THREADS 4
#define MYENGINE_MAX_TASK_COUNT 64

class ThreadPool
{
	static std::mutex m_mutex;

public:
	static void Initialise()
	{
		for (int i = 0; i < MYENGINE_MAX_THREADS; ++i)
			m_Threads[i].detach();
	}

	static void AddTask(Task _task)
	{
		m_mutex.lock();

		assert(m_TaskQueueCount < MAX_TASK_COUNT);

		m_Tasks[m_TaskQueueCount++] = _task;
		++m_TaskCount;

		m_mutex.unlock();
	}

	void RunTasks()
	{
		while (m_TaskCount > 0)
		{

		}
	}

	static void Run()
	{

	}

	static unsigned int	m_TaskQueueCount;
	static unsigned int	m_TaskCount;
	static std::thread	m_Threads[MYENGINE_MAX_THREADS];
	static Task			m_Tasks[MYENGINE_MAX_TASK_COUNT];
};