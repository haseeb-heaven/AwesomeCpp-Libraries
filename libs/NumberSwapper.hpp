// Add Header Guard
#ifndef NUMBER_SWAPPER_HPP
#define NUMBER_SWAPPER_HPP
#include <iostream>
#include <typeinfo>
#include <fstream>
#include <chrono>
#include <ctime>
#include "Logger.hpp"

/**
 * @brief A class template for swapping two numbers.
 *
 * This class provides a method to swap two numbers of any type.
 * It also logs the swapping process to a file named "log.txt".
 */
template <typename T>
class NumberSwapper
{
    Logger logger;

public:
    NumberSwapper()
        : logger([]()
                 {
        std::string currentFile = __FILE__;
        std::string::size_type pos = currentFile.find_last_of("/");

        // Extract the file name without the extension
        std::string fileName = currentFile.substr(pos + 1, currentFile.rfind(".") - pos - 1);
        std::string logFilename = Logger::getLogsFilename(fileName);
        return logFilename; }())
    {
    }

    /**
     * @brief Swaps two numbers.
     *
     * This method swaps the values of two numbers of type T.
     * It logs the swapping process to a file named "log.txt".
     *
     * @param first The first number to be swapped.
     * @param second The second number to be swapped.
     */
    void swap(T &first, T &second)
    {
        std::string firstStr = std::to_string(first);
        std::string secondStr = std::to_string(second);

        addLog("Swapping numbers: " + firstStr + ", " + secondStr + "...");
        try
        {
            T temp = first;
            first = second;
            second = temp;
            addLog("Numbers swapped successfully: " + firstStr + " <-> " + secondStr);
        }
        catch (const std::exception &e)
        {
            addLog("Error occurred while swapping numbers: " + firstStr + ", " + secondStr + ". Error: " + std::string(e.what()));
        }
    }

private:
    /**
     * @brief Logs a message to a file.
     *
     * This method appends a log message to a file named "log.txt".
     * The log message includes the current date and time.
     *
     * @param message The message to be logged.
     */
    void addLog(const std::string &message)
    {
        logger.log(message);
    }
};
#endif // NUMBER_SWAPPER_HPP