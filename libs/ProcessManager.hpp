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

class ProcessManager
{
public:
    ProcessManager() = default;
    ~ProcessManager() = default;

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

#ifdef _WIN32
    // Windows implementation
    boost::process::pid_t getProcessIdByName(const std::string &processName)
    {
        boost::process::pid_t processId = 0;
        try
        {
            // Windows-specific command to get process ID by name
            std::string command = "tasklist /FI \"IMAGENAME eq " + processName + "\" /NH /FO CSV";

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
        }
        catch (const std::exception &exception)
        {
            throw std::runtime_error("Failed to get process ID: " + std::string(exception.what()));
        }

        return processId;
    }
#else
#include <signal.h>
    // POSIX-compliant (Linux, macOS, etc.) implementation
    boost::process::pid_t getProcessIdByName(const std::string &processName)
    {
        boost::process::pid_t processId = 0;
        try
        {
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
        }
        catch (const std::exception &exception)
        {
            throw std::runtime_error("Failed to get process ID: " + std::string(exception.what()));
        }

        // Convert output to integer process ID
        return processId;
    }
#endif

    void killProcessSafely(boost::process::pid_t pid)
    {
        try
        {
            // Create a child object representing the process
            boost::process::child process_child(pid);

            // Terminate the process
            process_child.terminate();

            // Wait for the process to exit
            std::chrono::seconds timeout(5);
            auto exit_code = process_child.exit_code();
            if (!exit_code)
            {
                // If process is not terminated within 5 seconds, send SIGKILL to it
                ::kill(pid, SIGKILL);
            }
        }
        catch (const std::exception &exception)
        {
            throw std::runtime_error("Failed to terminate process: " + std::string(exception.what()));
        }
    }

    bool executeProcess(boost::process::pid_t pid)
    {
        try
        {
            std::cout << "Process ID: " << pid << " found successfully." << std::endl;
            boost::process::child process_child(pid);
            // kill the process safely and check permissions
            killProcessSafely(pid);
            return true;
        }
        catch (const std::exception &exception)
        {
            throw std::runtime_error("Failed to terminate process: " + std::string(exception.what()));
            return false;
        }
    }
};