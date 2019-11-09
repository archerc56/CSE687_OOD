#pragma once
#include <thread>
#include <vector>
#include <condition_variable>
#include <queue>
#include <future>

class ThreadPool
{
public:
	//using taskToRun = bool(__cdecl *)();
	//typedef bool(__cdecl *taskToRun)();
	using taskToRun = std::function<void()>;


	ThreadPool(std::size_t num_ofThreads)
	{
		start(num_ofThreads);
	}
	~ThreadPool()
	{
		stop();
	}

	//template<class T>
	void enqueue(taskToRun task)
	{ 
		{
			std::unique_lock<std::mutex> lock{ eventMutex };
			qTasks.emplace(std::move(task));
		}

		eventVar.notify_one();
	}

	bool get_isQ_Empty()
	{
		if(qTasks.empty())
			return true;
	}

private:

	std::vector<std::thread> vThreads;
	std::mutex eventMutex;
	std::condition_variable eventVar;
	bool Stop = false;
	std::queue<taskToRun> qTasks;

	void start(std::size_t num_ofThreads)
	{
		for (int i = 1; i <=  num_ofThreads; i++)
		{
			vThreads.emplace_back([=] 
			{
				while (true)
				{
					taskToRun task;

					{
						std::unique_lock<std::mutex> lock{ eventMutex };

						eventVar.wait(lock, [=] {return Stop || !qTasks.empty();});

						if (Stop && qTasks.empty())
							break;

						task = std::move(qTasks.front());
						qTasks.pop();
					}

					task();
				}
			
			});
		}
	}

	void stop() noexcept
	{
		{
			std::unique_lock<std::mutex> lock{ eventMutex };
			Stop = true;
		}

		eventVar.notify_all();

		for (auto &t : vThreads)
			t.join();
	}
};

