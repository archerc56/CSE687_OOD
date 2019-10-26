#ifndef EXECUTIVE_H
#define EXECUTIVE_H
#include "TestHarness.h"

class Executive
{
public:
	Executive();
	~Executive();

	void harnessLoader(std::string);	//recieves xml srting from main or from file
	void runHarness();					//calls execute from test harness.  this is a bit redundant but it allows us to no have to instantiate a testHarness object in main
	void clearHarness();
private:
	TestHarness testHarness;

	std::string removeSub(std::string s, std::string to_remove);// Remove substring from  a string 
	std::vector<std::string> ParseXML(std::string test_file);


};
#endif
