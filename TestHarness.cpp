//Last Update: October 12, 2019 @ 12:42 AM Central Time

#include "TestHarness.h"

TestHarness::TestHarness() {

}

TestHarness::~TestHarness() {

}
void TestHarness::setLogLevel(LogLevel logLevel)
{

}

bool TestHarness::executor(std::function<void()> callable)
{
	return false;
}

template <typename Callable>
bool TestHarness::executor(Callable& co)
{
	return false;
}

bool TestHarness::executor(std::list<std::function<void()>> callables)
{
	return false;

}

void TestHarness::log(int)
{

}

std::string TestHarness::to_String()
{
	return "";
}

void TestHarness::add_Test_to_Suite()
{

}

void TestHarness::reset_TestSuite()
{

}
