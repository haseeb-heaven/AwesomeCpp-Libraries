/*
This is an example of how to use the ProcessManager.
using boost library you need to download it from https://www.boost.org/
and link it to your project.
like this:
g++ -std=c++17 file.cpp -lboost_system -lboost_filesystem -o file && ./file
*/

#include "libs/ProcessManager.hpp"

int main()
{
    try
    {
        std::string processName;
        std::cout << "Process Name: ";
        std::getline(std::cin, processName);

        ProcessManager processManager;
        boost::process::pid_t pid = processManager.getProcessIdByName(processName);
        if (pid > 0)
        {
            bool success = processManager.executeProcess(pid);
            if (success)
            {
                std::cout << "Process terminated successfully." << std::endl;
            }
            else
            {
                std::cout << "Failed to terminate process." << std::endl;
            }
        }
        else
        {
            std::cout << "Process not found." << std::endl;
        }
    }
    catch (const std::exception &exception)
    {
        std::cerr << "An error occurred: " << exception.what() << std::endl;
        // Print the stack trace
        std::cerr << boost::stacktrace::stacktrace() << std::endl;
    }

    return 0;
}