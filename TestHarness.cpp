#include "TestHarness.h"

TestHarness::TestHarness()
{
	
}
TestHarness::~TestHarness()
{

}

void TestHarness::SetLogLevel(LogLevel logLevel)
{

}

void TestHarness::Executor()
{
	for (auto &i : this->TestSuite)
	{
		try
		{
			i();
			log(1);
		}
		catch (/*std::bad_alloc & ba*/ ...)
		{
			log(0);
		}
	}
}

//NOTE: log function might need to take in more parameters, such as start/end times, and error messages
void TestHarness::Log(bool pass)
{
	std::string logString;
	if(logLevel == LogLevel::LOW){
		if (pass)
		{
			logString = "pass";
		}
		else if (!pass)
		{
			logString = "fail";
		}

	}
	else if (logLevel == LogLevel::MEDIUM){
		//TODO: log any error messages
	}
	else{
		//TODO: log start and end time as well as error messages
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

template <typename Callable>
void TestHarness::AddTestToSuite(Callable& co)
{
	TestSuite.push_back(co);
}

void TestHarness::ResetTestSuite()
{
	this->TestSuite.clear();
}