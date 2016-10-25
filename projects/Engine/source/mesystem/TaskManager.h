#pragma once
#include <mutex>
#include <thread>

#define MYENGINE_MAX_THREADS 4
#define MYENGINE_MAX_TASK_COUNT 64

typedef void(*TaskFunction)(void);

struct Task
{
	Task()
	{

	}

	Task(TaskFunction _function)
	{
		m_Function = _function;
	}

	TaskFunction m_Function = nullptr;
};

class ThreadPool
{
	std::mutex m_mutex;

public:
	ThreadPool()
	{
		m_TaskQueueCount = 0;

		//Create the threads and detach
		for (int i = 0; i < MYENGINE_MAX_THREADS; ++i)
		{
			m_Threads[i] = new std::thread(DoTasks, this);
			m_Threads[i]->detach();
		}
	}

	void AddTask(Task _task)
	{
		m_mutex.lock();

		//Add the new task
		if(m_TaskQueueCount < MYENGINE_MAX_TASK_COUNT)
			m_Tasks[m_TaskQueueCount++] = _task;

		m_mutex.unlock();
	}
	
	static void DoTasks(ThreadPool* _threadpool)
	{
		printf("Thread[%d]	Created\n", std::this_thread::get_id());

		//Keep this here so we don't keep making a new one in the while loop
		Task _MyTask;

		while (true)
		{
			_threadpool->m_mutex.lock();

			if(_threadpool->m_TaskQueueCount > 0)
			{
				//Pop off Task
				_threadpool->m_TaskQueueCount--;
				_MyTask = _threadpool->m_Tasks[_threadpool->m_TaskQueueCount];

				_threadpool->m_mutex.unlock();

				//Run the function
				if(_MyTask.m_Function != nullptr)
					_MyTask.m_Function();
			}
			else
				_threadpool->m_mutex.unlock();
		}
	}

	unsigned int	m_TaskQueueCount;
	std::thread*	m_Threads[MYENGINE_MAX_THREADS];
	Task			m_Tasks[MYENGINE_MAX_TASK_COUNT];

};