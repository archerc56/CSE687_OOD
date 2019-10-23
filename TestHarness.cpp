#include "TestHarness.h"
#include <new>
#include <memory>
#include <typeinfo>

TestHarness::TestHarness() {}
TestHarness::~TestHarness() {}

//Converts the passed in clock ticks to milliseconds
float convertClockTicksToMilliSeconds(clock_t ticks)
{
	return (ticks / (CLOCKS_PER_SEC * 1.0)) / 1000.0;
}

void TestHarness::Executor(Logger::LogLevel logLevel)
//invoke each callable object and log its results
{
	int testNum = 1;
	std::cout << "Running Tests:" << std::endl;
	for (auto& i : this->TestSuite) //iterate through callable objects contained in TestSuite vector
	{
		float x, y;
		float startTime = convertClockTicksToMilliSeconds(clock());
		float runTime;
		try
		{
			//invoke each callable object
			i();

			//store end time
			runTime = convertClockTicksToMilliSeconds(clock() - startTime);

			//log pass
			Logger::Log(logLevel, 1, "Pass", runTime, testNum); //log pass since 1(true) is being passed in
		}
		catch (std::exception & e)
		{
			//store end time
			runTime = convertClockTicksToMilliSeconds(clock() - startTime);

			//log fail
			Logger::Log(logLevel, 0, e.what(), runTime, testNum);
		}
		catch (/*std::bad_alloc & ba*/ ...)
		{
			//store end time
			runTime = convertClockTicksToMilliSeconds(clock() - startTime);

			//log fail
			Logger::Log(logLevel, 0, "Unknown Exception Thrown!", runTime, testNum);
		}
		testNum++; //increment test number
	}
	std::cout << "\n";
}

void TestHarness::AddTestToSuite(std::function<void()> callable)
//add function pointer to TestSuite vector
{
	TestSuite.push_back(callable);
}

template <typename Callable>
void TestHarness::AddTestToSuite(Callable& co)
//overloaded AddTestToSuite function. add functor to TestSuite vector
{
	TestSuite.push_back(co);
}

void TestHarness::ResetTestSuite()
//remove all elements from TestSuite vector. TestSuite.size() == 0
{
	TestSuite.clear();
	report.str(std::string());
}

// Use for testing bad casting 
class Base { virtual void member() {} };
class Derived : Base {};

// Polymorphic struct so we can throw a bad_typeid.
// This type of exception is thrown each time a typeid is applied
// to a dereferenced null pointer value of polymorphic type. 
struct BadStruct { virtual void BadStructFuction(); };

// Functions for throwing a bad_exception
void throw_e();
void test_throw_e() throw(std::bad_exception);

bool TestBadAlloc();
bool TestBadCast();
bool TestBadException();
bool TestBadTypeID();
bool TestBadFunctionCall();
bool TestBadWeakPtr();
void TestAdd();
void TestAllocate();

int main()
{

	TestHarness th; //create instance of TestHarness class
	//pass in various test functions into TestSuite. These functions trigger various exceptions.

	std::cout << "**Running tests at high log level\n\n";
	th.AddTestToSuite(TestBadAlloc);
	th.AddTestToSuite(TestBadCast);
	th.AddTestToSuite(TestBadTypeID);
	th.AddTestToSuite(TestBadWeakPtr);
	th.AddTestToSuite(TestBadFunctionCall);
	th.AddTestToSuite(TestBadException);
	th.AddTestToSuite(TestAdd);
	th.AddTestToSuite(TestAllocate);

	Functor F;
	th.AddTestToSuite(F); //pass in Functor into TestSuite vector

	th.Executor(Logger::LogLevel::HIGH);
	std::cout << th.ToString();
	std::cout << "**Restting test suite\n\n";
	th.ResetTestSuite();
	std::cout << "**Running tests at medium log level\n\n";
	th.AddTestToSuite(TestBadAlloc);
	th.AddTestToSuite(TestBadCast);
	th.AddTestToSuite(TestBadTypeID);
	th.AddTestToSuite(TestBadWeakPtr);
	th.AddTestToSuite(TestBadFunctionCall);
	th.AddTestToSuite(TestBadException);
	th.AddTestToSuite(TestAdd);
	th.AddTestToSuite(TestAllocate);
	th.AddTestToSuite(F); //pass in Functor into TestSuite vector

	th.Executor(Logger::LogLevel::MEDIUM);
	std::cout << th.ToString();
	std::cout << "**Restting test suite\n\n";
	th.ResetTestSuite();

	std::cout << "**Running tests at low log level\n\n";
	th.AddTestToSuite(TestBadAlloc);
	th.AddTestToSuite(TestBadCast);
	th.AddTestToSuite(TestBadTypeID);
	th.AddTestToSuite(TestBadWeakPtr);
	th.AddTestToSuite(TestBadFunctionCall);
	th.AddTestToSuite(TestBadException);
	th.AddTestToSuite(TestAdd);
	th.AddTestToSuite(TestAllocate);
	th.AddTestToSuite(F); //pass in Functor into TestSuite vector

	th.Executor(Logger::LogLevel::LOW);
	std::cout << th.ToString();
	std::cout << "**Restting test suite\n\n";
	th.ResetTestSuite();

	return 0;
}

void TestAllocate()
{
	std::cout << "TestAllocate \n";
	int* foo;
	foo = new int[10];
}

void TestAdd()
{
	std::cout << "TestAdd \n";
	int i, j;
	i = 1;
	j = 2;
	j = j + i;
}

bool TestBadAlloc()
{
	std::bad_alloc x;
	std::cout << "TestBadAlloc \n";
	while (true)
	{
		new int[100000000ul];
	}
	throw x;
	return true;
}

// Test case for bad casting. A dervied class 
// should never be dynamically casted back to a base
// class.
bool TestBadCast()
{
	std::bad_cast e;
	std::cout << "TestBadCast \n";
	Base b;
	Derived& rd = dynamic_cast<Derived&>(b);
	throw e;
	return true;
}

void throw_e() { throw; }
void test_throw_e() throw(std::bad_exception)
{
	throw std::runtime_error("Error");
}

bool TestBadException()
{
	std::bad_exception e;
	std::cout << "TestBadException \n";
	std::set_unexpected(throw_e);
	test_throw_e();
	throw e;
	return true;
}

bool TestBadTypeID()
{
	std::bad_typeid e;
	std::cout << "TestBadTypeID \n";
	BadStruct* ptr = nullptr;
	std::cout << typeid(*ptr).name() << '\n';
	throw e;
	return true;
}

bool TestBadFunctionCall()
{
	std::bad_function_call e;
	std::cout << "TestBadFunctionCall \n";
	std::function<int()> TestBadFunction = nullptr;
	TestBadFunction();
	throw e;
	return true;
}

bool TestBadWeakPtr()
{
	std::bad_weak_ptr e;
	std::cout << "TestBadWeakPtr \n";
	std::shared_ptr<int> p1(new int(100));
	std::weak_ptr<int> wp(p1);
	p1.reset();
	throw e;
	return true;
}