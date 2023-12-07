// ProcessExec.cpp
#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#ifdef _WIN32
#define OS_WINDOWS
#elif __APPLE__
#define OS_MACOS
#elif __linux__
#define OS_LINUX
#else
#define OS_UNKNOWN
#endif
#include <boost/process.hpp>
#include <boost/stacktrace.hpp>
#include "libs/Logger.hpp"

/**
 * @brief A class that manages processes, including starting, terminating, and retrieving process IDs.
 */
class ProcessManager
{
private:
    Logger logger; // Logger object for logging file operations

public:
    /**
     * @brief Constructs a ProcessManager object.
     * The logger is initialized with the logs filename based on the current file's name.
     */
    ProcessManager()
        : logger([]()
                 {
            std::string currentFile = __FILE__;
            std::string::size_type pos = currentFile.find_last_of("/\\");
            std::string fileName = currentFile.substr(pos + 1, currentFile.rfind(".") - pos - 1);
            return Logger::getLogsFilename(fileName); }())
    {
        logger.log("FileManager instance created");
    }

    /**
     * @brief Safely terminates a process with the given process ID.
     * If the process is not terminated within 5 seconds, it is forcefully killed.
     * @param pid The process ID to terminate.
     * @throws std::runtime_error if failed to terminate the process.
     */
    void killProcessSafely(boost::process::pid_t pid)
    {
        try
        {
            logger.log("Terminating process with ID: " + std::to_string(pid));
            // Create a child object representing the process
            boost::process::child process_child(pid);

            // Terminate the process
            process_child.terminate();
            logger.log("Process terminated successfully.");

            // Wait for the process to exit
            std::chrono::seconds timeout(5);
            auto exit_code = process_child.exit_code();
            logger.log("Process exited with code: " + std::to_string(exit_code));
            if (!exit_code)
            {
                // If process is not terminated within 5 seconds, send SIGKILL to it
                ::kill(pid, SIGKILL);
                logger.log("Process killed successfully.");
            }
        }
        catch (const std::exception &exception)
        {
            throw std::runtime_error("Failed to terminate process: " + std::string(exception.what()));
        }
    }

    /**
     * @brief Starts a process with the given application path.
     * The behavior depends on the operating system.
     * @param application_path The path to the application to start.
     */
    void startProcess(const std::string &application_path)
    {
#ifdef OS_WINDOWS
        std::system(("start \"\" \"" + application_path + "\"").c_str());
#elif defined(OS_MACOS)
        std::system(("open -a \"" + application_path + "\"").c_str());
#elif defined(OS_LINUX)
        std::system(("xdg-open \"" + application_path + "\"").c_str());
#else
        std::cout << "Unsupported operating system" << std::endl;
#endif
    }

    /**
     * @brief Retrieves the process ID of a process with the given name.
     * The behavior depends on the operating system.
     * @param processName The name of the process.
     * @return The process ID if found, 0 otherwise.
     * @throws std::runtime_error if failed to retrieve the process ID.
     */
    boost::process::pid_t getProcessIdByName(const std::string &processName)
    {
#ifdef OS_WINDOWS
        boost::process::pid_t processId = 0;
        try
        {
            logger.log("Getting process ID by name: " + processName);
            // Windows-specific command to get process ID by name
            std::string command = "tasklist /FI \"IMAGENAME eq " + processName + "\" /NH /FO CSV";
            logger.log("Executing command: " + command);
            // Execute command and get output
            std::string output;
            boost::process::ipstream pipe;
            boost::process::child child_command(command, boost::process::std_out > pipe);
            std::getline(pipe, output);
            child_command.wait();

            // Parse output to get process ID
            size_t start = output.find_first_of(",") + 2;
            size_t end = output.find_first_of(",", start) - 1;
            std::string pid_str = output.substr(start, end - start);
            processId = std::stoi(pid_str);
            logger.log("Process ID: " + std::to_string(processId));
        }
        catch (const std::exception &exception)
        {
            throw std::runtime_error("Failed to get process ID: " + std::string(exception.what()));
        }

        return processId;

#elif defined(OS_MACOS) || defined(OS_LINUX)
        boost::process::pid_t processId = 0;
        try
        {
            logger.log("Getting process ID by name: " + processName);
            // POSIX-specific command to get process ID by name
            std::string command = "pgrep " + processName;

            // Execute command and get output
            std::string pid_str;
            boost::process::ipstream pipe;
            boost::process::child child_command(command, boost::process::std_out > pipe);
            std::getline(pipe, pid_str);
            child_command.wait();

            if (!pid_str.empty())
                processId = std::stoi(pid_str);
            else
                processId = 0;
            logger.log("Process ID: " + std::to_string(processId));
        }
        catch (const std::exception &exception)
        {
            throw std::runtime_error("Failed to get process ID: " + std::string(exception.what()));
        }

        // Convert output to integer process ID
        return processId;
#endif
    }

    /**
     * @brief Executes a process with the given process ID.
     * The process is terminated safely and its exit code is checked.
     * @param pid The process ID to execute.
     * @return true if the process was executed successfully, false otherwise.
     * @throws std::runtime_error if failed to terminate the process.
     */
    bool executeProcess(boost::process::pid_t pid)
    {
        try
        {
            logger.log("Executing process with ID: " + std::to_string(pid));
            boost::process::child process_child(pid);
            // kill the process safely and check permissions
            this->killProcessSafely(pid);
            return true;
        }
        catch (const std::exception &exception)
        {
            throw std::runtime_error("Failed to terminate process: " + std::string(exception.what()));
            return false;
        }
    }
};
