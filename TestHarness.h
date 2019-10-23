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
#ifndef TESTHARNESS_H
#define TESTHARNESS_H
#include <functional>
#include <vector>
#include <sstream>
#include <iostream>
#include <ctime>
#include "Functor.cpp"
#include "Logger.h"

class TestHarness
{
public:

	TestHarness(); //constructor
	~TestHarness(); //destructor
	void Executor(Logger::LogLevel); //executes a callable at the set log level
	std::string ToString();	//pretty much the getter for report
	template <typename Callable>
	void AddTestToSuite(Callable&); //adds the test case to testsuite
	//void AddTestToSuite(std::function<bool()> callable);	//adds test case to testsuite
	void AddTestToSuite(std::function<void()>);	//adds test case to testsuite
	void ResetTestSuite(); //resets the test suite
private:
	std::vector<std::function<void()>> TestSuite;
	std::stringstream report; //final report of all passes and fails.  when log() is called this string is appended
};
#endif