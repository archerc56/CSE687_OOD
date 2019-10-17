#pragma once
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

class TestHarness
{
public:
	enum LogLevel { HIGH, MEDIUM, LOW };				/* LOW: just pass-fail status
														MEDIUM: application specific messages for pass and fail, along with the result
														HIGH: detailed debugging output that includes, on failure, values of application specific variables,
														and an optional time-date stamp
														*/
	TestHarness();
	~TestHarness();
	void SetLogLevel(LogLevel logLevel);				//Sets the log level for the test Harness
	void Executor();										//executes a callable at the set log level
	std::string ToString();							//pretty much the getter for report
	void Log(bool pass, std::string, float runTime, int testNum);								//logs the result
	template <typename Callable>
	void AddTestToSuite(Callable& co);					//adds the test case to testsuite
	void AddTestToSuite(std::function<bool()> callable);	//adds test case to testsuite
	void ResetTestSuite();									//resets the test suite
private:
	LogLevel logLevel = LogLevel::HIGH;
	std::vector<std::function<bool()>> TestSuite;	//vector of callable objects
	std::stringstream report;						//final report of all passes and fails.  when log() is called this string is appended
};