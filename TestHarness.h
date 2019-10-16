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
#include "Functor.cpp"


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
	void execute();										//executes a callable at the set log level

	std::string to_String();							//pretty much the getter for report
	void log(bool pass);								//logs the result
	template <typename Callable>
	void add_Test_to_Suite(Callable& co);					//adds the test case to testsuite

	void add_Test_to_Suite(std::function<bool()> callable);	//adds test case to testsuite
	void reset_TestSuite();									//resets the test suite

private:
	LogLevel logLevel = HIGH;
	std::vector<std::function<bool()>> TestSuite;	//group of function pointers
	std::stringstream report;						//final report of all passes and fails.  when log() is called this string is appended	


};