#ifndef EXECUTIVE_H
#define EXECUTIVE_H
/**************************************************************************************************************************
CIS 687 Object Oriented Design Monday 9 PM
Authors:		Cade Archer, Michael Cheng, Sameer Rizvi, Bryan Ulrich
File:			Executive.h
Last Updated:	11/2/2019 7:12 PM
//**************************************************************************************************************************/

/**************************************************************************************************************************
Notes:
//**************************************************************************************************************************/
#include "TestHarness.h"

class Executive
{
public:
	Executive();
	~Executive();

	void DLLharnessLoader(std::string testRequest);	//recieves xml srting from main or from file
	void runHarness();					//calls execute from test harness.  this is a bit redundant but it allows us to no have to instantiate a testHarness object in main
	void clearHarness_andFreeDLL();		//This function allows the user to clear the harness of all test cases and "unload" the DLLs
	void displayTestResults();			//accessor for testHarness' toString method

private:
	typedef bool(__cdecl *f)();									//f is a function pointer that returns a bool.
	TestHarness testHarness;									//TestHarness object
	std::vector<HINSTANCE> all_DLL_MemoryLocations;				//vector storing pointers to all loaded DLL memory locations
	std::string removeSub(std::string s, std::string to_remove);//Remove substring from  a string 
	std::vector<std::string> ParseXML(std::string test_file);	//function to parse an xml file, grab the DLL file names, place them in a vector and return that vector


};
#endif
