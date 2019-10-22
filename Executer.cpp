#include "Executer.h"

Executer::Executer()
{
}

Executer::~Executer()
{
}

void Executer::harnessLoader(std::string xmlString)
{
	this->testHarness.loader(xmlString);
}

void Executer::runHarness()
{
	this->testHarness.Executor();
}