#include "TestHarness.h"
#include <new>
#include <memory>
#include <typeinfo>
#include <iostream>
#include <fstream>
#include <string>


// Remove substring from  a string 
std::string removeSub(std::string s, std::string to_remove) 
{
    // Erase to_remove.lenght starting at the index where
    // find found the first occurrence of the substring
    using namespace std;
    string::size_type size = s.find(to_remove);
    if (size != string::npos)
        s.erase(size, to_remove.length());

    return s;
}

// Parse and load an xml file
std::vector<std::string> ParseXML(std::string test_file)
{
    using namespace std;
    ifstream inFile(test_file);
    string input;
    string to_parse = "<test_name>";
    string to_remove = "</test_name>";
    std::vector<string> dlls_raw_content;
    std::vector<string> parsed_vector;

    while (inFile)
    {
        getline(inFile, input);
        dlls_raw_content.push_back(input);

    }

    inFile.close();

    for (int i=0; i<dlls_raw_content.size(); i++) 
    {
        if (dlls_raw_content[i].find(to_parse)==0) 
        {

            string Final = removeSub(dlls_raw_content[i], to_parse);
            Final = removeSub(Final, to_remove);
            parsed_vector.push_back(Final);

        }
    }

    for (int i=0; i<parsed_vector.size(); i++) 
    {
        cout << parsed_vector[i] << endl;
    }
    return parsed_vector;
}

TestHarness::TestHarness() {}
TestHarness::~TestHarness() {}

void TestHarness::SetLogLevel(LogLevel newLogLevel)
{
	logLevel = newLogLevel;
}

//Converts the passed in clock ticks to milliseconds
float convertClockTicksToMilliSeconds(clock_t ticks)
{
	return (ticks / (CLOCKS_PER_SEC * 1.0)) / 1000.0;
}

void TestHarness::Executor()
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
		testNum++; //increment test number
	}
	std::cout << "\n";
}

void TestHarness::Log(bool pass, std::string message, float runTime, int testNum)
//record each test. logLevel determines how much info is recorded. logLevel is defaulted to HIGH
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
	std::cout << "Test Results: " << std::endl;
	std::string returnString = this->report.str();
	return returnString;
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
    ParseXML("test.xml");

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

	th.Executor();
	std::cout << th.ToString();
	std::cout << "**Restting test suite\n\n";
	th.ResetTestSuite();


	th.SetLogLevel(TestHarness::LogLevel::MEDIUM);
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

	th.Executor();
	std::cout << th.ToString();
	std::cout << "**Restting test suite\n\n";
	th.ResetTestSuite();

	th.SetLogLevel(TestHarness::LogLevel::LOW);
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

	th.Executor();
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
