#include <functional>
#include <vector>
#include <sstream>
#include <iostream>
#include <ctime>

class TestRequest
{
    public: 
        void addTestDriver(std::string);
        std::vector<std::string>getTestDrivers();

    private:
        std::vector<std::string> testDrivers;
};
