#include "ThreadPool.h"

ThreadPool::ThreadPool(std::size_t num_ofThreads)
{
	// call init. on user defined number of threads
	initialize(num_ofThreads);
}

ThreadPool::~ThreadPool()
{
	//stop all threads when ThreadPool object goes out of scope
	stop();
}

//template<class T>
void ThreadPool::enqueue(std::function<void()> task)
{
	{//lock this scope so only one thread may add a task to the queue ata time
		std::unique_lock<std::mutex> lock{ eventMutex };
		qTasks.emplace(std::move(task));
	}
	//using our condtional variable object to notify one thread that is 
	//currently blocked by all calls to eventVar.wait 
	eventVar.notify_one();
}
bool ThreadPool::get_isQ_Empty()
{
	//check if the ThreadPool object has no callable function in its queue
	if (qTasks.empty())
		return true;
}
void ThreadPool::initialize(std::size_t num_ofThreads)
{
	//
	// for every user defined thread we will add a thread on the vector of threads.
	//When the thread is placed into the vector it will begin executing the code from the lambda
	//passed to it.  the  create a std:function object enter the scope of unique lock allowing only 
	//one thread at a time enter the scope.  The thread will then hit the eventVar.wait and wait until
	//notify one is call on the same condtional variable. If stopFlag and queue is empty we break from the 
	//loop and the thread will end the local callable object (task)  takes the first class on the queue and 
	//executes it, then return the a waiting state next iteration of the loop.
	//
	for (int i = 1; i <= num_ofThreads; i++)
	{
		Threads.emplace_back([=]
		{
			while (true)
			{
				std::function<void()> task;

				{
					std::unique_lock<std::mutex> lock{ eventMutex };

					eventVar.wait(lock, [=] {return stopFlag || !qTasks.empty();});

					if (stopFlag && qTasks.empty())
						break;

					task = std::move(qTasks.front());
					qTasks.pop();
				}

				task();
			}

		});
	}
}

void ThreadPool::stop() noexcept
{
	{//scope for a thread calling stop() (stop is called when thread calls the desctructor when it goes out of scope)
		std::unique_lock<std::mutex> lock{ eventMutex };
		stopFlag = true;
	}
	//notify any waiting threads to execute and break from infinite loop
	eventVar.notify_all();
	
	//join all threads back to main thread
	for (auto &t : Threads)
		t.join();
}