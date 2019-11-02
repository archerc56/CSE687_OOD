#include "Executive.h"

Executive::Executive()
{
}

Executive::~Executive()
{
}

void Executive::DLLharnessLoader(std::string xmlFileString)
{
	//<----- After Parse put each .dll as a string in this vector-------->
	std::vector<std::string> dll_List;
	dll_List = ParseXML(xmlFileString);

	//pointer to function obtained from .dll
	f importedFunctionPointer;

	for (auto &v : dll_List)
	{
		std::string temp;
		temp = v + ".dll";

		//load .dll into memory;
		HINSTANCE current_DLL_MemoryLocation = LoadLibraryA(temp.c_str());

		this->all_DLL_MemoryLocations.push_back(current_DLL_MemoryLocation);

		if (current_DLL_MemoryLocation)
		{
			// function pointer pointing to memory location of the function in the .dll
			importedFunctionPointer = reinterpret_cast<f>(GetProcAddress(current_DLL_MemoryLocation, v.c_str()));

			if (importedFunctionPointer)
			{
				//add function to suite
				//importedFunctionPointer();
				testHarness.AddTestToSuite(importedFunctionPointer);
			}
			else
				std::cout << "Could Not Load function " << v.c_str() << std::endl;
		}
		else
			std::cout << "Could Not Load DLL " << temp << std::endl;
	}
}

void Executive::runHarness()
{
	this->testHarness.Executor();
}

void Executive::clearHarness_andFreeDLL()
{
	this->testHarness.ResetTestSuite();
	for (auto &v : this->all_DLL_MemoryLocations)
	{
		FreeLibrary(v);
		std::cout << "Library at mem Location " << v << " Freed" << std::endl;
	}
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

	/*for (int i = 0; i<parsed_vector.size(); i++)
	{
		cout << parsed_vector[i] << endl;
	}*/
	return parsed_vector;
}

void Executive::displayTestResults()
{
	std::cout << this->testHarness.ToString() << std::endl;
}