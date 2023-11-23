#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <iostream>
#include <fstream>
#include <chrono>
#include <ctime>
#include <string>

/**
 * @brief The Logger class provides a simple logging functionality.
 */
class Logger
{
private:
    std::string logFilename; ///< The name of the log file.
    std::ofstream logFile; ///< The output file stream for writing logs.

public:
    /**
     * @brief Constructs a Logger object with the specified log file name.
     * @param filename The name of the log file. Default is "logger.log".
     */
    Logger(const std::string& filename = "logger.log") : logFilename(filename), logFile(filename, std::ios::app)
    {
    }

    /**
     * @brief Destroys the Logger object and closes the log file if it is open.
     */
    ~Logger()
    {
        if (logFile.is_open())
        {
            logFile.close();
        }
    }

    /**
     * @brief Generates the log file name based on the provided filename.
     * @param filename The base name of the log file.
     * @return The generated log file name.
     */
    static std::string getLogsFilename(std::string filename)
    {
        // Append ".log" to the file name
        std::string logFilename = "logs/" + filename + ".log";
        return logFilename;
    }

    /**
     * @brief Writes a log message to the log file.
     * @param message The log message to be written.
     */
    void log(const std::string& message)
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