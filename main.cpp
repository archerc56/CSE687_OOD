/**************************************************************************************************************************
CIS 687 Object Oriented Design Monday 9 PM
Authors:		Cade Archer, Michael Cheng, Sameer Rizvi, Bryan Ulrich
File:			main.cpp
Last Updated:	11/2/2019 7:10 PM
//**************************************************************************************************************************/

/**************************************************************************************************************************
Notes:
//**************************************************************************************************************************/
#include "Executive.h"
#include "ThreadPool.h"

// Use for testing bad casting 
//class Base { virtual void member() {} };
//class Derived : Base {};

// Polymorphic struct so we can throw a bad_typeid.
// This type of exception is thrown each time a typeid is applied
// to a dereferenced null pointer value of polymorphic type. 
//struct BadStruct { virtual void BadStructFuction(); };

// Functions for throwing a bad_exception
//void throw_e();
//void test_throw_e() throw(std::bad_exception);

//bool TestBadAlloc();
//bool TestBadCast();
//bool TestBadException();
//bool TestBadTypeID();
//bool TestBadFunctionCall();
//bool TestBadWeakPtr();
//void TestAdd();
//void TestAllocate();

//using taskToRun = bool(__cdecl *)();
//typedef bool(__cdecl *taskToRun)();

//using taskToRun = std::function<void(std::string)>;

void testRequest(std::string);

void printThreadID();

Executive e;
int totalRequests = 3;
std::mutex mux;

int main()
{
	
	//Executive e;

	ThreadPool tp(6);

	std::string request1 = "test.xml";
	std::string request2 = "test.xml";
	std::string request3 = "test.xml";

	

	/*std::thread t1(printThreadID);
	std::thread t2(printThreadID);
	std::thread t3(printThreadID);
*/

	//taskToRun bind1 = std::bind(testRequest, request1);

	//auto t1 = std::thread(testRequest, std::ref(e), request1);
	//auto t2 = std::thread(testRequest, std::ref(e), request2);
	//auto t3 = std::thread(testRequest, std::ref(e), request3);

	//std::thread t1(testRequest, e, request1);
	//std::thread t2(testRequest, e, request2);
	//std::thread t3(testRequest, e, request3);

	//t1.join();
	//t2.join();
	//t3.join();

	//probably hitign eah other!!!! troublshooot
	tp.enqueue(std::bind(testRequest, request1));
	tp.enqueue(std::bind(testRequest, request2));
	tp.enqueue(std::bind(testRequest, request3));

	//tp.enqueue(testRequest(e, request2));
	//tp.enqueue(testRequest(e, request3));

	//if there is still a task to run the we will not dsiplay results and clear
	while (totalRequests)
	{

	}

	e.displayTestResults();
	e.clearHarness_andFreeDLL();

	return 0;
}

void testRequest(std::string request)
{
	std::unique_lock<std::mutex> lock{ mux };
	std::thread::id threadID = std::this_thread::get_id();
	std::cout << threadID << "\n\n\n";

	e.DLLharnessLoader(request);
	e.runHarness();
	//e.displayTestResults();
	e.clearHarness_andFreeDLL();
	totalRequests--;
}

void printThreadID()
{
	std::thread::id threadID = std::this_thread::get_id();
	std::cout << threadID << "\n";
}







//void TestAllocate()
//{
//	std::cout << "TestAllocate \n";
//	int* foo;
//	foo = new int[10];
//}
//
//void TestAdd()
//{
//	std::cout << "TestAdd \n";
//	int i, j;
//	i = 1;
//	j = 2;
//	j = j + i;
//}
//
//bool TestBadAlloc()
//{
//	std::bad_alloc x;
//	std::cout << "TestBadAlloc \n";
//	while (true)
//	{
//		new int[100000000ul];
//	}
//	throw x;
//	return true;
//}
//
//// Test case for bad casting. A dervied class 
//// should never be dynamically casted back to a base
//// class.
//bool TestBadCast()
//{
//	std::bad_cast e;
//	std::cout << "TestBadCast \n";
//	Base b;
//	Derived& rd = dynamic_cast<Derived&>(b);
//	throw e;
//	return true;
//}
//
//void throw_e() { throw; }
//void test_throw_e() throw(std::bad_exception)
//{
//	throw std::runtime_error("Error");
//}
//
//bool TestBadException()
//{
//	std::bad_exception e;
//	std::cout << "TestBadException \n";
//	std::set_unexpected(throw_e);
//	test_throw_e();
//	throw e;
//	return true;
//}
//
//bool TestBadTypeID()
//{
//	std::bad_typeid e;
//	std::cout << "TestBadTypeID \n";
//	BadStruct* ptr = nullptr;
//	std::cout << typeid(*ptr).name() << '\n';
//	throw e;
//	return true;
//}
//
//bool TestBadFunctionCall()
//{
//	std::bad_function_call e;
//	std::cout << "TestBadFunctionCall \n";
//	std::function<int()> TestBadFunction = nullptr;
//	TestBadFunction();
//	throw e;
//	return true;
//}
//
//bool TestBadWeakPtr()
//{
//	std::bad_weak_ptr e;
//	std::cout << "TestBadWeakPtr \n";
//	std::shared_ptr<int> p1(new int(100));
//	std::weak_ptr<int> wp(p1);
//	p1.reset();
//	throw e;
//	return true;
//}
