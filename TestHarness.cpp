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

//Converts the passed in clock ticks to milliseconds
float TestHarness::convertClockTicksToMilliSeconds(clock_t ticks) {
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
			Logger::Log(logLevel, 1, "Pass", runTime, testNum); //log pass since 1(true) is being passed in
		}
		catch (std::exception & e)
		{
			//store end time
			runTime = convertClockTicksToMilliSeconds(clock() - startTime);

			//log fail
			Logger::Log(logLevel,0, e.what(), runTime, testNum);
		}
		catch (/*std::bad_alloc & ba*/ ...)
		{
			//store end time
			runTime = convertClockTicksToMilliSeconds(clock() - startTime);

			//log fail
			Logger::Log(logLevel, 0, "Unknown Exception Thrown!", runTime, testNum);
		}

		testNum++;

	}
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
		/*loadlibrary;
		AddTestToSuite(ITestFunction);*/
	}

	
}

