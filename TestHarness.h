/**************************************************************************************************************************

CIS 687 Object Oriented Design Monday 9 PM

Authors:

File:			TestHarness.h

Description:

Last Updated:	10/10/2019 23:19 PM (Central time), 00:19 EST


//**************************************************************************************************************************/

/**************************************************************************************************************************

Notes:



//**************************************************************************************************************************/
#include <list>
#include <functional>
#include <vector>
#include <sstream>

class TestHarness
{
public:
	TestHarness();
	~TestHarness();
	enum LogLevel { HIGH, MEDIUM, LOW };				/* LOW: just pass-fail status
														MEDIUM: application specific messages for pass and fail, along with the result
														HIGH: detailed debugging output that includes, on failure, values of application specific variables,
														 and an optional time-date stamp
														*/

	void setLogLevel(LogLevel logLevel);				//Sets the log level for the test Harness
	bool executor(std::function<void()>);		//executes a callable at the set log level

	template <typename Callable>
	bool executor(Callable&);

	bool executor(std::list<std::function<void()>> call);//Executes a sequence of callables at the set log level

	//**Don't think this is needed. If the callable(s) complete then that's considered a pass 
	void log(int);				//takes int argument, 1 or 0 for pass or fail
	std::string to_String();	//pretty much the getter for report

	///**Needed? I think the executor method that takes in a list satisfies this
	void add_Test_to_Suite();	//adds test case to testsuite
	void reset_TestSuite();
	//----Test Cases------
	//void test_ReturnValue(T value);// if value is not expected the throw
	//--------------------
private:
	LogLevel logLevel = HIGH;
	std::vector<void(*)()> TestSuite;	//group of function pointers
	std::stringstream report;			//final report of all passes and fails.  when log() is called this string is appended	
	//----Test DATA-------
	//--------------------
};
