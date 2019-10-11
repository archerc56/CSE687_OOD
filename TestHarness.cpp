#include "TestHarness.h"

void TestHarness::setLogLevel(LogLevel logLevel)
{

}
				
void TestHarness::Executor(std::function<void()> callable)
{

}

template <typename Callable>
void TestHarness::Executor(Callable& co)
{
	
}
		
void TestHarness::Executor(std::list<function<void()>> callables)
{

}


void TestHarness::log(int)
{

}			

std::string TestHarness::to_String()
{

}
	
void TestHarness::add_Test_to_Suite()
{

}
	
void TestHarness::reset_TestSuite()
{

}
