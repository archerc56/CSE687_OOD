#ifndef TESTHARNESS_H
#define TESTHARNESS_H
/**************************************************************************************************************************
CIS 687 Object Oriented Design Monday 9 PM
Authors:
File:			TestHarness.h
Description:
Last Updated:	10/9/2019 7:08 PM
//**************************************************************************************************************************/

/**************************************************************************************************************************
Notes:
//**************************************************************************************************************************/
#include <functional>
#include <vector>
#include <sstream>
#include <iostream>
#include <ctime>
#include "Functor.cpp"
#include <new>
#include <memory>
#include <typeinfo>
#include <fstream>
#include <string>
#include "Logger.h"

class TestHarness
{
public:

	TestHarness();
	~TestHarness();
	void SetLogLevel(Logger::LogLevel logLevel);					//Sets the log level for the test Harness
	void Executor();										//executes a callable at the set log level
	std::string ToString();									//pretty much the getter for report
	
	template <typename Callable>
	void AddTestToSuite(Callable& co);						//adds the test case to testsuite
	void AddTestToSuite(std::function<bool()> callable);	//adds test case to testsuite
	void ResetTestSuite();									//resets the test suite
	void dll_Loader(std::vector<std::string>);
private:
	Logger::LogLevel logLevel = Logger::LogLevel::HIGH;
	std::vector<std::function<bool()>> TestSuite;			//vector of callable objects
	std::stringstream report;								//final report of all passes and fails.  when log() is called this string is appended
	float convertClockTicksToMilliSeconds(clock_t ticks);
};
#endif