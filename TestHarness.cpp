#include "TestHarness.h"
#include <new>
#include <memory>
#include <typeinfo>

TestHarness::TestHarness()
{

}
TestHarness::~TestHarness()
{

}

void TestHarness::SetLogLevel(LogLevel newLogLevel)
{
	logLevel = newLogLevel;
}

//Converts the passed in clock ticks to milliseconds
float convertClockTicksToMilliSeconds(clock_t ticks) {
	return (ticks / (CLOCKS_PER_SEC * 1.0)) / 1000.0;
}

void TestHarness::Executor()
{
	int testNum = 1;
	for (auto& i : this->TestSuite) //iterate through TestSuite vector contents
	{
		float x, y;
		float startTime = convertClockTicksToMilliSeconds(clock());
		float runTime;

		try
			//invoke callable objects within try block
		{
			//invoke callable object
			i();

			//store end time
			runTime = convertClockTicksToMilliSeconds(clock() - startTime);

			//log pass
			Log(1, "Pass", runTime, testNum); //log pass since 1(true) is being passed in
		}
		catch (std::exception & e)
		{
			//store end time
			runTime = convertClockTicksToMilliSeconds(clock() - startTime);

			//log fail
			Log(0, e.what(), runTime, testNum);
		}
		catch (/*std::bad_alloc & ba*/ ...)
		{
			//store end time
			runTime = convertClockTicksToMilliSeconds(clock() - startTime);

			//log fail
			Log(0, "Unknown Exception Thrown!", runTime, testNum);
		}

		testNum++;

	}
}


void TestHarness::Log(bool pass, std::string message, float runTime, int testNum)
//print pass/fail based on what is passed in
{

	std::string logString = "";

	//All log levels will at least log pass/fail
	if (pass)
	{
		logString = "Test #" + std::to_string(testNum) + " passed. ";
	}

	else
	{
		logString = "Test #" + std::to_string(testNum) + " failed. ";
	}

	//If log level is MEDIUM and the test failed, add the error message to the log string
	if ((logLevel == LogLevel::MEDIUM || logLevel == LogLevel::HIGH) && !pass)
	{
		logString += "Test failure message: " + message + ". ";
	}

	//If the log level is HIGH add the start and end times to the log string
	if (logLevel == LogLevel::HIGH)
	{
		logString += "Test run time: " + std::to_string(runTime) + "ms. ";
	}

	report << logString << std::endl;
}

std::string TestHarness::ToString()
{
	std::string returnString = this->report.str();
	return returnString;
}

void TestHarness::AddTestToSuite(std::function<bool()> callable)
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
	this->TestSuite.clear();
}

void TestHarness::dll_Loader(std::vector<std::string> dll_List)
{	

	for (auto &v : dll_List)
	{
		loadlibrary;
		AddTestToSuite(ITestFunction);
	}

	
}



/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * Main method to run tests
 *
 */

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

int main()
{

	TestHarness th;

	th.AddTestToSuite(TestBadAlloc);
	th.AddTestToSuite(TestBadCast);
	th.AddTestToSuite(TestBadTypeID);
	th.AddTestToSuite(TestBadWeakPtr);
	th.AddTestToSuite(TestBadFunctionCall);
	th.AddTestToSuite(TestBadException);

	Functor F;
	//F();
	th.AddTestToSuite(F);

	th.Executor();

	std::cout << th.ToString();

	return 0;
}

/**
 *
 */
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

/**
 *
 */
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
/**
 *
 */
bool TestBadException()
{
	std::bad_exception e;
	std::cout << "TestBadException \n";
	std::set_unexpected(throw_e);
	test_throw_e();

	throw e;
	return true;

}

/**
 *
 */
bool TestBadTypeID()
{
	std::bad_typeid e;
	std::cout << "TestBadTypeID \n";
	BadStruct* ptr = nullptr;
	std::cout << typeid(*ptr).name() << '\n';

	throw e;
	return true;
}

/**
 *
 */
bool TestBadFunctionCall()
{
	std::bad_function_call e;
	std::cout << "TestBadFunctionCall \n";
	std::function<int()> TestBadFunction = nullptr;
	TestBadFunction();

	throw e;
	return true;

}

/**
 *
 */
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
