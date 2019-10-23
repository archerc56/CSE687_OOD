#include <functional>
#include <vector>
#include <sstream>
#include <iostream>

class Logger
{
    public:
        enum LogLevel { HIGH, MEDIUM, LOW };/*LOW: just pass-fail status
                                            MEDIUM: application specific messages for pass and fail, along with the result
                                            HIGH: detailed debugging output that includes, on failure, values of application specific variables,
                                            and an optional time-date stamp*/

        static void Logger::Log(LogLevel logLevel, bool pass, std::string message, float runTime, int testNum)
        //record each test. logLevel determines how much info is recorded
        {
            std::string logString = "";

            //All log levels will at least log pass/fail
            if (pass)
            {
                logString = "Test #" + std::to_string(testNum) + " passed. ";
            }
            else
            {
                logString = "Test #" + std::to_string(testNum) + " failed. ";
            }

            //If log level is MEDIUM and the test failed, add the error message to the log string
            if ((logLevel == LogLevel::MEDIUM || logLevel == LogLevel::HIGH) && !pass)
            {
                logString += "Test failure message: " + message + ". ";
            }

            //If the log level is HIGH add the start and end times to the log string
            if (logLevel == LogLevel::HIGH)
            {
                logString += "Test run time: " + std::to_string(runTime) + "ms.";
            }
            std::cout << logString << std::endl;
        }
};