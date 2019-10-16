#include "TestHarness.h"

#include <new>
#include <typeinfo>

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
			Log(1);
		}
		catch (/*std::bad_alloc & ba*/ ...)
		{
			Log(0);
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

/**
 * Main method to run tests 
 * 
 */

// Use for testing bad casting 
class Base { virtual void member() {} };
class Derived : Base {} ;

bool TestBadAlloc();
bool TestBadCast();
void TestBadException();
void TestBadTypeID();
void TestBadFunctionCall();
void TestBadWeakPtr();

int main()
{
	
	TestHarness th;

	th.AddTestToSuite(TestBadAlloc);
	th.AddTestToSuite(TestBadCast);

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
    while (true)
    {
        new int [100000000ul];
    }
    return true;
}

/**
 * 
 */
bool TestBadCast()
{
    Base b;
    Derived & rd = dynamic_cast<Derived&>(b);
    return false;
}

/**
 * 
 */
void TestBadException()
{

}

/**
 * 
 */
void TestBadTypeID()
{

}

/**
 * 
 */
void TestBadFunctionCall()
{

}

/**
 * 
 */
void TestBadWeakPtr()
{

}