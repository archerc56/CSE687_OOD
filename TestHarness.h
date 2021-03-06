#ifndef TESTHARNESS_H
#define TESTHARNESS_H
/**************************************************************************************************************************
CIS 687 Object Oriented Design Monday 9 PM
Authors:		Cade Archer, Michael Cheng, Sameer Rizvi, Bryan Ulrich
File:			TestHarness.h
Last Updated:	11/2/2019 7:05 PM
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
#include <windows.h>

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
	void SetLogLevel(LogLevel logLevel);							//Sets the log level for the test Harness
	void Executor();												//executes a callable at the set log level
	std::string ToString();											//pretty much the getter for report
	void Log(bool pass, std::string, float runTime, int testNum);	//logs the result
	
	//template <typename Callable>
	void AddTestToSuite(bool(__cdecl * co)());						//adds the test case to testsuite
	
	void AddTestToSuite(std::function<bool()> callable);			//adds test case to testsuite
	void ResetTestSuite();											//resets the test suite

private:
	LogLevel logLevel = LogLevel::HIGH;
	std::vector<std::function<bool()>> TestSuite;					//vector of function onject
	std::vector<bool(__cdecl *)()> PointerTestSuite;				//vector of function pointers
	std::stringstream report;										//final report of all passes and fails.  when log() is called this string is appended
	float convertClockTicksToMilliSeconds(clock_t ticks);
};
#endif