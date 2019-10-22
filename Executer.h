#pragma once
#include "TestHarness.h"

class Executer
{
public:
	Executer();
	~Executer();

	void harnessLoader(std::string);	//recieves xml srting from main or from file
	void runHarness();					//calls execute from test harness.  this is a bit redundant but it allows us to no have to instantiate a testHarness object in main

private:
	TestHarness testHarness;
};

