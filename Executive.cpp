#include "Executive.h"

Executive::Executive(){}
Executive::~Executive(){}

void Executive::harnessLoader(std::string xmlFileString)
{
	//<----- After Parse put each .dll as a string in this vector with-------->
	std::vector<std::string> dll_List;
	dll_List = ParseXML(xmlFileString);
	this->testHarness.dll_Loader(dll_List);
}

void Executive::runHarness()
{
	this->testHarness.Executor();
}

void Executive::clearHarness()
{
	this->testHarness.ResetTestSuite();
}

std::string Executive::removeSub(std::string s, std::string to_remove)
{
	// Erase to_remove.lenght starting at the index where
	// find found the first occurrence of the substring
	using namespace std;
	string::size_type size = s.find(to_remove);
	if (size != string::npos)
		s.erase(size, to_remove.length());
	return s;
}

std::vector<std::string> Executive::ParseXML(std::string test_file)
{
	using namespace std;
	ifstream inFile(test_file);
	string input;
	string to_parse = "<test_name>";
	string to_remove = "</test_name>";
	std::vector<string> dlls_raw_content;
	std::vector<string> parsed_vector;

	while (inFile)
	{
		getline(inFile, input);
		dlls_raw_content.push_back(input);
	}
	inFile.close();
	for (int i = 0; i<dlls_raw_content.size(); i++)
	{
		if (dlls_raw_content[i].find(to_parse) == 0)
		{
			string Final = removeSub(dlls_raw_content[i], to_parse);
			Final = removeSub(Final, to_remove);
			parsed_vector.push_back(Final);
		}
	}
	for (int i = 0; i<parsed_vector.size(); i++)
	{
		cout << parsed_vector[i] << endl;
	}
	return parsed_vector;
}