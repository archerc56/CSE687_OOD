#include "Executer.h"

Executer::Executer()
{
}

Executer::~Executer()
{
}

void Executer::harnessLoader(std::string xmlString)
{
	//<----- After Parse put each .dll as a string in this vector with-------->
	std::vector<std::string> dll_List;
	
	
	this->testHarness.dll_Loader(dll_List);
}

void Executer::runHarness()
{
	this->testHarness.Executor();
}