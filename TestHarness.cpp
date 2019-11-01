#include "TestHarness.h"


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
float TestHarness::convertClockTicksToMilliSeconds(clock_t ticks) {
	return (ticks / (CLOCKS_PER_SEC * 1.0)) / 1000.0;
}

void TestHarness::Executor()
{
	int testNum = 1;
	for (auto& i : this->PointerTestSuite/*TestSuite*/) //iterate through TestSuite vector contents
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
{
	TestSuite.push_back(callable);
}

//template <typename Callable>
void TestHarness::AddTestToSuite(bool(__cdecl * co)())
{
	PointerTestSuite.push_back(co);
}

void TestHarness::ResetTestSuite()
//remove all elements from TestSuite vector. TestSuite.size() == 0
{
	this->TestSuite.clear();
}

