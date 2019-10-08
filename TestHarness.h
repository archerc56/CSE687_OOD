#include <list>
#include <functional>
using namespace std;
class TestHarness
{

public:
	enum LogLevel { HIGH, MEDIUM, LOW }; /* LOW: just pass-fail status
					        MEDIUM: application specific messages for pass and fail, along with the result
						HIGH: detailed debugging output that includes, on failure, values of application specific variables, 
						      and an optional time-date stamp
					     */
	void setLogLevel(LogLevel logLevel); //Sets the log level for the test Harness
	
	void execute(function<bool()> callable); //executes a callable at the set log level

	void execute(list<function<bool()>> callables); //Executes a sequenece of callables at the set log level

private:
	LogLevel logLevel = HIGH;
};

