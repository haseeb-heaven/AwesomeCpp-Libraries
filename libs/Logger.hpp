// Add Header Guard
#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <iostream>
#include <fstream>
#include <chrono>
#include <ctime>
#include <string>

class Logger
{
private:
    std::string logFilename;
    std::ofstream logFile;

public:
    Logger(const std::string& filename = "logger.log") : logFilename(filename), logFile(filename, std::ios::app)
    {
    }

    ~Logger()
    {
        if (logFile.is_open())
        {
            logFile.close();
        }
    }

    static std::string getLogsFilename(std::string filename)
    {
        // Append ".log" to the file name
        std::string logFilename = "logs/" + filename + ".log";
        return logFilename;
    }

    void addLog(const std::string& message)
    {
        auto now = std::chrono::system_clock::now();
        std::time_t time = std::chrono::system_clock::to_time_t(now);

        if (logFile.is_open())
        {
            std::string timeStr = std::ctime(&time);
            timeStr.pop_back(); // Remove the newline character
            logFile << timeStr << " - " << message << std::endl;
        }
    }
};

#endif // LOGGER_HPP