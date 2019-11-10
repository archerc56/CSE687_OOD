#pragma once
#include <thread>
#include <vector>
#include <condition_variable>
#include <queue>
#include <future>

class ThreadPool
{
public:
	//using std::function<void()> = bool(__cdecl *)();
	//typedef bool(__cdecl *std::function<void()>)();
	//using Tasks = std::function<void()>;

	//Initialize a pool of user-defined threads on creation of ThreadPool object
	ThreadPool(std::size_t num_ofThreads);

	//stop all threads when ThreadPool object goes out of scope
	~ThreadPool();

	//add a task (function object of return type void) to the queue and notify 1 thread to execute
	//template<class T>
	void enqueue(std::function<void()> task);

	//function to return a bool if the all tasks are finished executing
	bool get_isQ_Empty();

private:

	std::vector<std::thread> Threads;				//vector of threads that are created once then set to wait
	std::mutex eventMutex;							//mutex used in unique lock to create critical sections
	std::condition_variable eventVar;				//object used to lock all thread in wating state; and also waking a thread at one time
	bool stopFlag = false;								//stop flag
	std::queue<std::function<void()>> qTasks;		//queue of callable objects

	void initialize(std::size_t num_ofThreads);		//initialize function to spin up threads 

	void stop() noexcept;							//stop all threads when ThreadPool object goes out of scope.  throw no exception on thread exit
};

