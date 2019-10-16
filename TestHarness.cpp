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

// Polymorphic struct so we can throw a bad_typeid.
// This type of exception is thrown each time a typeid is applied
// to a dereferenced null pointer value of polymorphic type. 

struct BadStruct{ virtual void BadStructFuction(); };

bool TestBadAlloc();
bool TestBadCast();
void TestBadException();
bool TestBadTypeID();
void TestBadFunctionCall();
bool TestBadWeakPtr();

int main()
{
	
	TestHarness th;

	th.AddTestToSuite(TestBadAlloc);
	th.AddTestToSuite(TestBadCast);
    th.AddTestToSuite(TestBadTypeID);
    th.AddTestToSuite(TestBadWeakPtr);

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
    while (true)
    {
        new int [100000000ul];
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
    Base b;
    Derived & rd = dynamic_cast<Derived&>(b);

    throw e;

    return true;
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
bool TestBadTypeID()
{
    std::bad_typeid e;
    BadStruct * ptr = nullptr;
    std::cout << typeid(*ptr).name() << '\n';

    throw e;
    return true;
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
bool TestBadWeakPtr()
{
    std::bad_weak_ptr e;
    std::shared_ptr<int> p1(new int(100));
    std::weak_ptr<int> wp(p1);
    p1.reset();

    throw e;
    return true;
    

}
