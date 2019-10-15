#include "TestHarness.h"

TestHarness::TestHarness()
{
	
}
TestHarness::~TestHarness()
{

}

void TestHarness::setLogLevel(LogLevel logLevel)
{

}

void TestHarness::execute()
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


void TestHarness::log(bool pass)
{
	std::string logString;

	if (pass)
	{
		logString = "pass";
	}
	else if (!pass)
	{
		logString = "fail";
	}

	report << logString << std::endl;
}


std::string TestHarness::to_String()
{
	std::string returnString = this->report.str();
	return returnString;
}


void TestHarness::add_Test_to_Suite(std::function<void()> callable)
{

	TestSuite.push_back(callable);
}

void TestHarness::reset_TestSuite()
{
	this->TestSuite.clear();
}