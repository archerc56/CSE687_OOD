/**************************************************************************************************************************
CIS 687 Object Oriented Design Monday 9 PM

Authors:		Cade Archer, Micheal Cheng, Sameer Rizvi, Bryan Ulrich
File:			TestHarness.h
Contents:		Class Declaration(TestHarness)
Description:	The File TestHarness.h contains the class declaration for the TestHarness.  This class contains
				private members for storing testsuite and loglevel states. The class also provides public member 
				functions that provide functionality to the user.  Using this class the user will be able to:
					-add callable objects to a test suite vector via the void AddTestToSuite(std::function<void()>) member function
					-set the log level by calling SetLogLevel() function, 
					-execute the stores test functions  sequentially by calling the Executor() function 
					-reset the test suite by calling ResetTestSuite()
					
Last Updated:	10/18/2019 8:59 AM
//**************************************************************************************************************************/
/***************************************************************************************************************************
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

class TestHarness
{
public:
	enum LogLevel { HIGH, MEDIUM, LOW };/*LOW: just pass-fail status
										MEDIUM: application specific messages for pass and fail, along with the result
										HIGH: detailed debugging output that includes, on failure, values of application specific variables,
										and an optional time-date stamp*/
										
	TestHarness(); 								//constructor
	~TestHarness(); 							//destructor
	
	void SetLogLevel(LogLevel);					//Sets the log level for the test Harness
	void Executor(); 							//executes a callable at the set log level
	std::string ToString();						//pretty much the getter for report
	void Log(bool, std::string, float, int);	//logs the result
	
	template <typename Callable>
	void AddTestToSuite(Callable&); 			//adds the test case to testsuite
	
	//void AddTestToSuite(std::function<bool()> callable);	//adds test case to testsuite
	void AddTestToSuite(std::function<void()>);				//adds test case to testsuite
	void ResetTestSuite(); 									//resets the test suite
private:
	LogLevel logLevel = LogLevel::HIGH;
	//std::vector<std::function<bool()>> TestSuite;			//vector of callable objects
	std::vector<std::function<void()>> TestSuite;			//vector of callable objects
	std::stringstream report; 								//final report of all passes and fails.  when log() is called this string is appended
};
#endif