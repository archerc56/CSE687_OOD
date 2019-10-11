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

//using namespace std;
template <typename Callable>
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
	//void Executor(std::function<void()> callable);		//executes a callable at the set log level
	void Executor(std::function<void()>);		//executes a callable at the set log level
	void Executor(Callable& co);
	//void Executor(std::list<function<void()>> callables);//Executes a sequenece of callables at the set log level
	void Executor(std::list<function<void()>>);//Executes a sequenece of callables at the set log level
	void log(int);				//takes int arguement, 1 or 0 for pass or fail
	std::string to_String();	//pretty much the getter for report
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
